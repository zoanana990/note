hashtable.c:8:14: warning: cast to smaller integer type 'unsigned int' from 'void *' [-Wvoid-pointer-to-int-cast]
    return (((unsigned int) key * GOLDEN_RATIO_32) >> (32 - bits));
             ^~~~~~~~~~~~~~~~~~
hashtable.c:13:33: error: use of undeclared identifier 'map'
    struct hlist_head *head = &(map->ht)[hash(key, map->bits)];
                                ^
hashtable.c:13:52: error: use of undeclared identifier 'map'
    struct hlist_head *head = &(map->ht)[hash(key, map->bits)];
                                                   ^
hashtable.c:15:64: error: call to undeclared function 'node'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
        struct hash_key *kn = container_of(p, struct hash_key, node);
                                                               ^
hashtable.c:15:31: error: use of undeclared identifier 'offsetoftype'
        struct hash_key *kn = container_of(p, struct hash_key, node);
                              ^
./hashtable.h:50:25: note: expanded from macro 'container_of'
    ((type *) (__mptr - offsetoftype, member()))    \
                        ^
hashtable.c:15:26: error: initializing 'struct hash_key *' with an expression of incompatible type 'void'
        struct hash_key *kn = container_of(p, struct hash_key, node);
                         ^    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
hashtable.c:46:5: error: void function 'map_add' should not return a value [-Wreturn-type]
    return kn ? kn->data : NULL;
    ^      ~~~~~~~~~~~~~~~~~~~~
hashtable.c:52:9: error: non-void function 'map_get' should return a value [-Wreturn-type]
        return;
        ^
hashtable.c:62:16: error: no member named 'pprev' in 'struct hlist_node'; did you mean 'prev'?
        first->pprev = &n->next;
               ^~~~~
               prev
./hashtable.h:26:25: note: 'prev' declared here
    struct hlist_node **prev;
                        ^
hashtable.c:64:8: error: no member named 'pprev' in 'struct hlist_node'; did you mean 'prev'?
    n->pprev = &h->first;
       ^~~~~
       prev
./hashtable.h:26:25: note: 'prev' declared here
    struct hlist_node **prev;
                        ^
hashtable.c:71:25: error: use of undeclared identifier 'bits'
    for (int i = 0; i < MAP_HASH_SIZE(hash_map->bits); i++) {
                        ^
./hashtable.h:54:36: note: expanded from macro 'MAP_HASH_SIZE'
#define MAP_HASH_SIZE(bita) (1 << (bits))
                                   ^
hashtable.c:75:68: error: call to undeclared function 'node'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
            struct hash_key *kn = container_of(p, struct hash_key, node);
                                                                   ^
hashtable.c:75:35: error: use of undeclared identifier 'offsetoftype'
            struct hash_key *kn = container_of(p, struct hash_key, node);
                                  ^
./hashtable.h:50:25: note: expanded from macro 'container_of'
    ((type *) (__mptr - offsetoftype, member()))    \
                        ^
hashtable.c:75:30: error: initializing 'struct hash_key *' with an expression of incompatible type 'void'
            struct hash_key *kn = container_of(p, struct hash_key, node);
                             ^    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
hashtable.c:79:20: error: no member named 'pprev' in 'struct hlist_node'; did you mean 'prev'?
            if(!n->pprev)
                   ^~~~~
                   prev
./hashtable.h:26:25: note: 'prev' declared here
    struct hlist_node **prev;
                        ^
hashtable.c:82:61: error: no member named 'pprev' in 'struct hlist_node'; did you mean 'prev'?
            struct hlist_node *next = n->next, **pprev = n->pprev;
                                                            ^~~~~
                                                            prev
./hashtable.h:26:25: note: 'prev' declared here
    struct hlist_node **prev;
                        ^
hashtable.c:86:23: error: no member named 'pprev' in 'struct hlist_node'; did you mean 'prev'?
                next->pprev = pprev;
                      ^~~~~
                      prev
./hashtable.h:26:25: note: 'prev' declared here
    struct hlist_node **prev;
                        ^
hashtable.c:95:10: error: use of undeclared identifier 'map'
    free(map);
         ^
1 warning and 17 errors generated.
main.c:3:11: error: expected ';' after top level declarator
int main()
          ^
          ;
main.c:5:28: error: initializer element is not a compile-time constant
    struct map *hash_map = map_init(10);
                           ^~~~~~~~~~~~
main.c:6:19: error: expected identifier or '('
    int key = 10, int data = 20;
                  ^
main.c:6:18: error: expected ';' after top level declarator
    int key = 10, int data = 20;
                 ^
                 ;
main.c:8:23: error: expected identifier
    map_add(hash_map, &key, &data);
                      ^
main.c:8:5: warning: type specifier missing, defaults to 'int' [-Wimplicit-int]
    map_add(hash_map, &key, &data);
    ^
main.c:8:5: warning: a function declaration without a prototype is deprecated in all versions of C and is not supported in C2x [-Wdeprecated-non-prototype]
main.c:8:5: error: conflicting types for 'map_add'
./hashtable.h:57:6: note: previous declaration is here
void map_add(struct map *map, void *key);
     ^
main.c:9:12: error: expected parameter declarator
    printf("%d\n", *map_get(hash_map, &key));
           ^
main.c:9:12: error: expected ')'
main.c:9:11: note: to match this '('
    printf("%d\n", *map_get(hash_map, &key));
          ^
main.c:9:5: warning: type specifier missing, defaults to 'int' [-Wimplicit-int]
    printf("%d\n", *map_get(hash_map, &key));
    ^
main.c:9:5: error: conflicting types for 'printf'
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/stdio.h:175:6: note: previous declaration is here
int      printf(const char * __restrict, ...) __printflike(1, 2);
         ^
main.c:12:5: error: expected identifier or '('
    return 0;
    ^
main.c:13:1: error: extraneous closing brace ('}')
}
^
3 warnings and 11 errors generated.
