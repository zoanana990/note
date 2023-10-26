#include <stdio.h>
#include <stdlib.h>
#include "strlen.h"
#include <time.h>

#define TEST_CNT 1000000

// Macro for result expectation
#define EXPECT(expr)                                \
    do {                                            \
        if (!(expr)) {                              \
            printf("Test failed\n");                \
            exit(1);                                \
        }                                           \
    } while (0)

void drawProgressBar(int progress, int total) {
    int barWidth = 50;
    float percentage = (float)progress / total;
    int numBars = percentage * barWidth;

    printf("[");
    for (int i = 0; i < numBars; i++) {
        printf("=");
    }
    for (int i = numBars; i < barWidth; i++) {
        printf(" ");
    }
    printf("] %.1f%%\r", percentage * 100);
    fflush(stdout);
}

int main() {
    FILE *log_file = fopen("strlen_perf.log", "w");
    if (!log_file) {
        perror("Failed to open log file");
        exit(1);
    }

    for (int len = 1; len <= TEST_CNT; len++) {
        char *str = (char *)malloc(len + 1);
        for (int i = 0; i < len; i++) {
            str[i] = 'A';
        }
        str[len] = '\0';

        struct timespec start_time, end_time;
        double elapsed_time;

        // Measure the performance of the C version of strlen
        clock_gettime(CLOCK_MONOTONIC, &start_time); // Get start time
        EXPECT(len == strlen_c(str));
        clock_gettime(CLOCK_MONOTONIC, &end_time); // Get end time
        elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                       (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        fprintf(log_file, "%d %llf", len, elapsed_time);

        clock_gettime(CLOCK_MONOTONIC, &start_time); // Get start time
        EXPECT(len == strlen_gcc(str));
        clock_gettime(CLOCK_MONOTONIC, &end_time); // Get end time

        elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                       (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        fprintf(log_file, " %llf\n", elapsed_time);

        free(str);
    
        drawProgressBar(len, TEST_CNT);
    }

    fclose(log_file);
    return 0;
}

