#include <stdio.h>
#include <stdint.h>

#define NUM_KEYS 16

// Placeholder for the initial key (64 bits)
uint64_t initial_key = 0x133457799BBCDFF1;

// Example PC1 and PC2 tables (fill with actual values)
const int PC1[56] = { /* ... PC1 values ... */ };
const int PC2_1[24] = { /* ... First 24 bits from PC2 ... */ };
const int PC2_2[24] = { /* ... Second 24 bits from PC2 ... */ };

// Function prototypes
void generate_keys(uint64_t key, uint64_t keys[NUM_KEYS]);
void permute(const int *table, const uint64_t *input, uint64_t *output, int input_size, int output_size);
void print_keys(uint64_t keys[NUM_KEYS]);

void generate_keys(uint64_t key, uint64_t keys[NUM_KEYS]) {
    uint64_t key_perm = 0;

    // Step 1: Permute the key using PC1
    permute(PC1, &key, &key_perm, 64, 56);

    // Step 2: Split the key into two halves
    uint32_t C = (uint32_t)(key_perm >> 28); // Left 28 bits
    uint32_t D = (uint32_t)(key_perm & 0x0FFFFFFF); // Right 28 bits

    // Step 3: Generate 16 subkeys
    for (int i = 0; i < NUM_KEYS; i++) {
        // Apply shifts (not shown; implement shifts as needed)
        // C and D shifts based on your desired logic

        // Combine C and D to create the full key for the subkey
        uint64_t combined_key = ((uint64_t)C << 28) | D;

        // Generate the subkey from disjoint subsets
        keys[i] = ((combined_key >> 32) & 0xFFFFFF) | ((combined_key & 0xFFFFFF) << 24);
    }
}

void permute(const int *table, const uint64_t *input, uint64_t *output, int input_size, int output_size) {
    *output = 0;
    for (int i = 0; i < output_size; i++) {
        int bit = (input_size - table[i]);
        *output |= ((*input >> bit) & 1) << (output_size - 1 - i);
    }
}

void print_keys(uint64_t keys[NUM_KEYS]) {
    for (int i = 0; i < NUM_KEYS; i++) {
        printf("K%d: %06lX\n", i + 1, keys[i]);
    }
}

int main() {
    uint64_t keys[NUM_KEYS];
    generate_keys(initial_key, keys);
    print_keys(keys);
    return 0;
}
