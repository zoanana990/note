#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro for result expectation
#define EXPECT(expr, message)                       \
    do {                                            \
        if (!(expr)) {                              \
            printf("Test failed: %s, test_count = %d\n", message, i);   \
            exit(1);                                \
        }                                           \
    } while (0)

int main() {
    struct map *map = map_init(20); // Adjust the number of bits as needed

    if (!map) {
        printf("Failed to initialize the map.\n");
        return 1;
    }

    // Insert 1 million elements with mixed data types
    for (int i = 1; i <= 1000000; i++) {
        if (i % 2 == 0) {
            // Insert integer as key and string as data
            char key_str[20];
            snprintf(key_str, sizeof(key_str), "key%d", i);
            char value_str[20];
            snprintf(value_str, sizeof(value_str), "value%d", i);
            map_add(map, (void *)(intptr_t)i, strdup(value_str));
        } else {
            // Insert string as key and integer as data
            char key_str[20];
            snprintf(key_str, sizeof(key_str), "key%d", i);
            map_add(map, strdup(key_str), (void *)(intptr_t)i);
        }
    }

    // Test retrieving and validating the inserted elements
    for (int i = 1; i <= 1000000; i++) {
        void *value;
        if (i % 2 == 0) {
            // Integer as key, expect a string value
            value = map_get(map, (void *)(intptr_t)i);
            char expected_value_str[20];
            snprintf(expected_value_str, sizeof(expected_value_str), "value%d", i);
            EXPECT(value && strcmp((char *)value, expected_value_str) == 0, "Value mismatch");
        } else {
            // String as key, expect an integer value
            char key_str[20];
            snprintf(key_str, sizeof(key_str), "key%d", i);
            value = map_get(map, strdup(key_str));
            EXPECT(value && (intptr_t)value == i, "Value mismatch");
        }
    }

    // Clean up
    map_deinit(map);

    printf("All tests passed!\n");

    return 0;
}

