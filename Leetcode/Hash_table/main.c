#include "hashtable.h"
#include <stdio.h>

int main() {
    struct map *map = map_init(8); // 8 bits for the hashtable

    if (!map) {
        printf("Failed to initialize the map.\n");
        return 1;
    }

    // Insert some key-value pairs
    map_add(map, "key1", "value1");
    map_add(map, "key2", "value2");
    map_add(map, "key3", "value3");

    // Retrieve and print values
    printf("Value for key1: %s\n", (char *)map_get(map, "key1"));
    printf("Value for key2: %s\n", (char *)map_get(map, "key2"));
    printf("Value for key3: %s\n", (char *)map_get(map, "key3"));

    // Remove a key
    map_remove(map, "key2");

    // Attempt to retrieve the removed key
    char *result = (char *)map_get(map, "key2");
    if (result) {
        printf("Value for key2 after removal: %s\n", result);
    } else {
        printf("Key2 not found after removal.\n");
    }

    // Clean up
    map_deinit(map);

    return 0;
}

