#include <stdio.h>

#define MAX_HEAPS 4096

typedef long Align;

struct header {
    struct header *ptr;
    unsigned int size;
};

void *my_malloc(unsigned int nbytes);
void my_free(void *ap);

typedef struct header Header;

static unsigned char heaps[MAX_HEAPS];
static unsigned char *program_break = heaps;

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */

static void *sbrk(unsigned int nbytes)
{
    if (program_break + nbytes >= heaps
        && program_break + nbytes < heaps + MAX_HEAPS) {
        unsigned char *previous_pb = program_break;
        program_break += nbytes;
        return (void *) previous_pb;
    }
    return (void *) -1;
}

void *my_malloc(unsigned int nbytes)
{
    Header *p, *prevp;
    unsigned int nunits;
    void *cp;

    /* Calculate the lowest size, including sizeof(Header) + real_malloc_size + padding
     * In this program, there are 16 bytes per unit.
     * */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    /* initialize the pointers, freep, prevp, base.ptr */
    if ((prevp = freep) == NULL) {
        base.ptr = freep = prevp = &base;
        base.size = 0;
    }


    for (p = prevp->ptr; ; prevp = p, p = p->ptr) {
        if (p->size >= nunits) {
            if (p->size == nunits) {
                prevp->ptr = p->ptr;
            } else {
                p->size -= nunits;
                p += p->size;
                p->size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep) {

            /* Break the boundary of heap */
            cp = sbrk(nunits * sizeof(Header));
            if (cp == (void *) -1) {
                return NULL;
            } else {
                /* if breaking successfully,
                 * then we update the unit to the structure */
                p = (Header *) cp;
                p->size = nunits;
                my_free((void *) (p + 1));
                p = freep;
            }
        }
    }
}

void my_free(void *ap)
{
    Header *bp, *p;
    bp = (Header *) ap - 1;

    for (p = freep; !(bp > p && bp < p->ptr); p = p->ptr) {
        if (p >= p->ptr && (bp > p || bp < p->ptr))
            break;
    }

    /* Merge two blocks */
    if (bp + bp->size == p->ptr) {
        bp->size += p->ptr->size;
        bp->ptr = p->ptr->ptr;
    } else {
        bp->ptr = p->ptr;
    }

    /* Merge previous block */
    if (p + p->size == bp) {
        p->size += bp->size;
        p->ptr = bp->ptr;
    } else {
        p->ptr = bp;
    }

    /* update the p->ptr in freep */
    freep = p;
}

int main() {
    printf("Malloc test start\n");
    int *segment1 = my_malloc(sizeof(int) * 10);
    printf("segment 1 = %p\n", segment1);
    int *segment2 = my_malloc(sizeof(int) * 10);
    printf("segment 2 = %p\n", segment2);
    int *segment3 = my_malloc(sizeof(int) * 10);
    printf("segment 3 = %p\n", segment3);
    my_free(segment2);
    my_free(segment1);
    my_free(segment3);
    int *segment4 = my_malloc(sizeof(int) * 20);
    printf("segment 4 = %p\n", segment4);
    int *segment5 = my_malloc(sizeof(int) * 10);
    printf("segment 5 = %p\n", segment5);
    int *segment6 = my_malloc(sizeof(int) * 20);
    printf("segment 6 = %p\n", segment6);
    my_free(segment4);
    my_free(segment5);
    int *segment7 = my_malloc(sizeof(int) * 20);
    printf("segment 7 = %p\n", segment7);
    my_free(segment6);
    my_free(segment7);
    printf("Malloc test complete\n");
    printf("-----------------------------------------------------------\n");
    printf("base.ptr = %p, base.size = %d\n", base.ptr, base.size);
    printf("freep->ptr = %p, freep->size = %d\n", freep->ptr, freep->size);
    printf("program_break = %p\n", program_break);
    printf("sizeof(struct header) = %lu\n", sizeof(struct header));
    return 0;
}