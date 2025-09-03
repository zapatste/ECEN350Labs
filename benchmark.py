SIZE = 50000
EXPECTED_CHECKSUM = 41667916675000

# Initialize arrays
A = [i for i in range(SIZE)]
B = [SIZE - i for i in range(SIZE)]

# Precompute prefix sums of B
prefix_sum = [0] * (SIZE + 1)
for i in range(SIZE):
    prefix_sum[i + 1] = prefix_sum[i] + B[i]

# Compute C[i] using prefix sums
C = [prefix_sum[A[i] + 1] for i in range(SIZE)]

# Compute checksum
checksum = sum(C)

print(f"Computed checksum: {checksum}")

if checksum != EXPECTED_CHECKSUM:
    print(f"Error: checksum does not match expected value {EXPECTED_CHECKSUM}")
    exit(1)

print("Checksum is correct!")