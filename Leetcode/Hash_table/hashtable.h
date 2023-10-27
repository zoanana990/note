#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

/* [Design] This is a linux style hash table implementation
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

enum hash_type
{
    HASH_PRINT_STRING = 0,
    HASH_PRINT_INTEGER,
    HASH_PRINT_LAST
};

#define container_of(ptr, type, member)             \
({                                                  \
    void *__mptr = (void *) (ptr);                  \
    ((type *) (__mptr - offsetof(type, member)));   \
})

#define GOLDEN_RATIO_32 0x61C88647
#define MAP_HASH_SIZE(bits) (1 << (bits))
#define HASH_DATA_SIZE 1024
struct map *map_init(int size);
void map_add(struct map *hash_map, void *key, void *data);
void *map_get(struct map *hash_map, void *key);
void map_remove(struct map *hash_map,void *key);
void map_deinit(struct map *hash_map);
void map_print(struct map *hash_map, enum hash_type type);

#endif
