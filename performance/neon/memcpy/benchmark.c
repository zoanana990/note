#include <arm_neon.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

// NEON memcpy function
void *neon_memcpy(void *dest, const void *src, size_t n) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;

    // Copy in 128-bit (16-byte) chunks
    while (n >= 16) {
        vst1q_u8(d, vld1q_u8(s));
        s += 16;
        d += 16;
        n -= 16;
    }

    // Copy remaining bytes
    while (n > 0) {
        *d++ = *s++;
        n--;
    }

    return dest;
}

// NEON memset function
void *neon_memset(void *s, int c, size_t n) {
    uint8_t *dst = (uint8_t *)s;
    uint8x16_t value = vdupq_n_u8((uint8_t)c);

    // Set in 128-bit (16-byte) chunks
    while (n >= 16) {
        vst1q_u8(dst, value);
        dst += 16;
        n -= 16;
    }

    // Set remaining bytes
    while (n > 0) {
        *dst++ = (uint8_t)c;
        n--;
    }

    return s;
}

// Test program to compare performance
void benchmark(void *(*memcpy_func)(void *, const void *, size_t), void *(*memset_func)(void *, int, size_t)) {
    const unsigned long long size = 1024ULL * 1024ULL * 1024ULL * 1024ULL; // 100 MB
    uint8_t *src = malloc(size);
    uint8_t *dst = malloc(size);

    // Initialize src with some data
    memset(src, 0xAA, size);

    // Benchmark memcpy
    clock_t start = clock();
    memcpy_func(dst, src, size);
    clock_t end = clock();
    printf("memcpy took %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Benchmark memset
    start = clock();
    memset_func(dst, 0x55, size);
    end = clock();
    printf("memset took %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(src);
    free(dst);
}

int main() {
    printf("Benchmarking standard functions...\n");
    benchmark(memcpy, memset);

    printf("\nBenchmarking NEON functions...\n");
    benchmark(neon_memcpy, neon_memset);

    return 0;
}
