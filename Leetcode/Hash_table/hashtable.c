#include "hashtable.h"

/**************************************
 * private functions
 **************************************/
static inline unsigned int hash(void *key, unsigned int bits)
{
    /* hash function for 32-bit */
    return (unsigned int)(((unsigned int) key * GOLDEN_RATIO_32) >> (32 - bits));
}

static inline struct hash_key *find_key (struct map *hash_map, void *key)
{
    /* get the linked list */
    struct hlist_head *head = &(hash_map->ht)[hash(key, hash_map->bits)];
    for (struct hlist_node *p = head->first; p; p = p->next) {
        struct hash_key *kn = container_of(p, struct hash_key, node);
        if (kn->key == key)
            return kn;
    }
    return NULL;
}


/**************************************
 * APIs
 **************************************/
void map_print(struct map *hash_map, enum hash_type type)
{
    /* print all hash table element */
    if (!hash_map) {
        printf("Map is not initialized.\n");
        return;
    }

    for (int i = 0; i < MAP_HASH_SIZE(hash_map->bits); i++) {
        struct hlist_head *head = &hash_map->ht[i];

        struct hlist_node *p = head->first;
        while (p) {
            struct hash_key *kn = container_of(p, struct hash_key, node);

            if (kn->key) {
                if (type == HASH_PRINT_INTEGER) {
                    printf("Key-Value (int): %d - %d\n", (int *)kn->key, (int *)kn->data);
                } else {
                    printf("Key-Value (string): %s - %s\n", (char *)kn->key, (char *)kn->data);
                }
            }

            p = p->next;
        }
    }
}

struct map *map_init(int bits)
{
    struct map *hash_map = malloc(sizeof(struct map));
    if (!hash_map)
        return NULL;

    hash_map->bits = bits;
    hash_map->ht = malloc(sizeof(struct hlist_head) * MAP_HASH_SIZE(hash_map->bits));
    if (hash_map->ht) {
        for (int i = 0; i < MAP_HASH_SIZE(hash_map->bits); i++)
            (hash_map->ht)[i].first = NULL;
    } else {
        free(hash_map);
        hash_map = NULL;
    }
    return hash_map;
}

void map_add(struct map *hash_map, void *key, void *data)
{
    struct hash_key *kn = find_key(hash_map, key);

    /* check whether the key is repeated */
    if(kn)
        return;
    
    kn = malloc(sizeof(struct hash_key));

    /* initialize kn */
    kn->key = key;
    kn->data = data;
    struct hlist_node *n = &kn->node;
    
    /* add hash node to hash table */
    struct hlist_head *h = &hash_map->ht[hash(key, hash_map->bits)];
    struct hlist_node *first = h->first;

    n->next = first;
    if(first)
        first->pprev = &n->next;
    
    h->first = n;
    n->pprev = &h->first;
}

void *map_get(struct map *hash_map, void *key)
{
    struct hash_key *kn = find_key(hash_map, key);
    return kn ? kn->data : NULL;
}

void map_remove(struct map *hash_map, void *key)
{
    if (!hash_map || !key) {
        return;
    }

    int hash_val = hash(key, hash_map->bits);
    struct hlist_head *head = &hash_map->ht[hash_val];

    struct hlist_node *p = head->first, **pprev = &head->first;

    while (p) {
        struct hash_key *kn = container_of(p, struct hash_key, node);

        if (kn->key == key) {
            *pprev = p->next;
            if (p->next) {
                p->next->pprev = pprev;
            }
            p->next = NULL;
            p->pprev = NULL;

            //free(kn->data);
            free(kn);
            return;
        }

        pprev = &p->next;
        p = p->next;
    }
}

void map_deinit(struct map *hash_map)
{
    if (!hash_map)
        return;

    for (int i = 0; i < MAP_HASH_SIZE(hash_map->bits); i++) {
        struct hlist_head *head = &hash_map->ht[i];
        for (struct hlist_node *p = head->first; p;) {
            struct hash_key *kn = container_of(p, struct hash_key, node);
            struct hlist_node *n = p;
            p = p->next;

            if (!n->pprev) /* unhashed */
                goto bail;

            struct hlist_node *next = n->next, **pprev = n->pprev;
            *pprev = next;
            if (next)
                next->pprev = pprev;
            n->next = NULL, n->pprev = NULL;

        bail:
            //free(kn->data);
            free(kn);
        }
    }
    free(hash_map);
}
