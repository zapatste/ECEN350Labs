// benchmark.c
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50000
#define EXPECTED_CHECKSUM 41667916675000LL

// Declare statically allocated arrays (not dynamically with malloc)
int A[SIZE];
int B[SIZE];
long long C[SIZE];  // Needs 64-bit since sums grow large

int main(void) {
    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        A[i] = i;            // A[i] = i
        B[i] = SIZE - i;    // B[i] = 50000 - i
        C[i] = 0;            // Initialize C[i] = 0
    }

    // Compute C[i] = sum_{j=0}^{A[i]} B[j]
    for (int i = 0; i < SIZE; i++) {
        long long sum = 0; // Local sum for each C[i]
        for (int j = 0; j <= A[i]; j++) {
            sum += B[j];
        }
        C[i] = sum;
    }

    // Compute checksum = sum of all C[i]
    long long checksum = 0;
    for (int i = 0; i < SIZE; i++) {
        checksum += C[i];
    }

    // Print and check checksum
    printf("Computed checksum: %lld\n", checksum);

    if (checksum != EXPECTED_CHECKSUM) {
        fprintf(stderr, "Error: checksum does not match expected value %lld\n", EXPECTED_CHECKSUM);
        return 1; // Non-zero return indicates error
    }

    printf("Checksum is correct!\n");
    return 0; // Success
}
