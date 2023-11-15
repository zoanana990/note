#include <stdio.h>

#define MAX_HEAPS 4096

typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned int size;
	} s;
	Align x;
};

struct mm_list {
    struct mm_list *ptr;
    unsigned int size;
    unsigned int blocks_unit;
};

void *my_malloc(unsigned int nbytes);
void my_free(void *ap);

typedef union header Header;

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

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits) {
				prevp->s.ptr = p->s.ptr;
			} else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}

		if (p == freep) {
			cp = sbrk(nunits * sizeof(Header));
			if (cp == (void *) -1) {
				return NULL;
			} else {
				p = (Header *) cp;
				p->s.size = nunits;
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

	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	}

	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else {
		bp->s.ptr = p->s.ptr;
	}

	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else {
		p->s.ptr = bp;
	}

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
    int *segment4 = my_malloc(sizeof(int) * 20);
    printf("segment 4 = %p\n", segment4);
    int *segment5 = my_malloc(sizeof(int) * 10);
    printf("segment 5 = %p\n", segment5);
    my_free(segment1);
    my_free(segment3);
    my_free(segment4);
    my_free(segment5);
    printf("Malloc test complete\n");
    printf("-----------------------------------------------------------\n");
    printf("base.s.ptr = %p, base.s.size = %d\n", base.s.ptr, base.s.size);
    printf("freep->s.ptr = %p, freep->s.size = %d\n", freep->s.ptr, freep->s.size);
    printf("program_break = %p\n", program_break);
    printf("sizeof(struct mm_list) = %lu\n", sizeof(struct mm_list));
    printf("sizeof(union header) = %lu\n", sizeof(union header));
    return 0;
}