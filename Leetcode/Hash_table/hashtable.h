#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Design
 *
 *    struct map                              
 * +--------------+      +--------------+     +-------------+
 * |     bits     |      |  hlist_head  | ==> |   hash_key  |
 * +--------------+      +--------------+     +------+------+
 * |  hlist_head  |  ==> |  hlist_head  |     |  key | data |
 * +--------------+      +--------------+     +------+------+
 *                       |      ...     |     | prev | next |
 *                       +--------------+     +------+------+
 *                       |  hlist_head  |
 *                       +--------------+
 * */

struct hlist_node 
{
    struct hlist_node *next;
    struct hlist_node **pprev;
};

struct hlist_head
{
    struct hlist_node *first;
};

struct map
{
    int bits;
    struct hlist_head *ht;
};

struct hash_key
{
    void *key;
    void *data;
    struct hlist_node node;
};

#define container_of(ptr, type, member)             \
({                                                  \
    void *__mptr = (void *) (ptr);                  \
    ((type *) (__mptr - offsetof(type, member)))    \
})

#define GOLDEN_RATIO_32 0x61C88647
#define MAP_HASH_SIZE(bita) (1 << (bits))

struct map *map_init(int size);
void map_add(struct map *map, void *key);
void *map_get(struct map *map, void *key, void *data);
void map_deinit(struct map *map);

#endif
