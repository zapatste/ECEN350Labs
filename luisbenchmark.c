#include <stdio.h>
#include <stdint.h>


#define N 50000u
#define EXPECTED_CHECKSUM 41667916675000ull


// Statically allocated (no malloc)
static int32_t  A[N];
static int32_t  B[N];
static uint64_t C[N];   // 64-bit to be safe for intermediate sums


int main(void) {
   // 1) Initialize arrays
   for (uint32_t i = 0; i < N; ++i) {
       A[i] = (int32_t)i;
       B[i] = (int32_t)(N - i);
       C[i] = 0u;
   }


   // 2) Compute: C[i] = sum_{j=0}^{A[i]} B[j]
#ifndef OPT_FAST
   // Direct definition (O(N^2)), good for measuring CPI under heavy arithmetic.
   for (uint32_t i = 0; i < N; ++i) {
       uint64_t s = 0u;
       for (uint32_t j = 0; j <= (uint32_t)A[i]; ++j) {
           s += (uint64_t)B[j];
       }
       C[i] = s;
   }
#else
   // Optimized but mathematically identical (O(N)):
   // Since A[i] = i, C[i] is simply the prefix sum of B up to i.
   uint64_t acc = 0u;
   for (uint32_t i = 0; i < N; ++i) {
       acc += (uint64_t)B[i];
       C[i]  = acc;
   }
#endif


   // 3) Compute checksum = sum_i C[i]
   uint64_t checksum = 0u;
   for (uint32_t i = 0; i < N; ++i) {
       checksum += C[i];
   }


   // 4) Report and validate
   printf("Checksum: %llu\n", (unsigned long long)checksum);
   if (checksum != EXPECTED_CHECKSUM) {
       fprintf(stderr, "ERROR: expected %llu but got %llu\n",
               (unsigned long long)EXPECTED_CHECKSUM,
               (unsigned long long)checksum);
       return 1; // non-zero on mismatch
   }


   return 0; // success
}
