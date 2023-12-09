#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [source_file] [target_file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *source_file, *target_file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    source_file = fopen(argv[1], "rb");
    if (source_file == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    target_file = fopen(argv[2], "wb");
    if (target_file == NULL) {
        perror("Error opening target file");
        fclose(source_file);
        return EXIT_FAILURE;
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, target_file);
    }

    fclose(source_file);
    fclose(target_file);

    printf("File copied successfully.\n");

    return EXIT_SUCCESS;
}

