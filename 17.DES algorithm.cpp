#include <stdio.h>
#include <stdint.h>

#define DES_BLOCK_SIZE 8
#define NUM_KEYS 16

static const int S[8][64] = {
    /* S-Box definitions */
};


static const int IP[64] = { /* Initial Permutation */ };
static const int IP_INV[64] = { /* Inverse Initial Permutation */ };
static const int E[48] = { /* Expansion table */ };
static const int P[32] = { /* Permutation table */ };
static const int PC1[56] = { /* PC1 table */ };
static const int PC2[48] = { /* PC2 table */ };

static const int shift_schedule[NUM_KEYS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void initial_permutation(uint64_t *block);
void inverse_initial_permutation(uint64_t *block);
void generate_keys(uint64_t key, uint64_t keys[NUM_KEYS]);
void des_decrypt(uint64_t *block, uint64_t keys[NUM_KEYS]);
void feistel_function(uint32_t *half_block, uint32_t subkey);
void permute(const int *table, const uint64_t *input, uint64_t *output, int input_size, int output_size);

void des_decrypt(uint64_t *block, uint64_t keys[NUM_KEYS]) {
    initial_permutation(block);
    
    uint32_t left = (uint32_t)(*block >> 32);
    uint32_t right = (uint32_t)(*block & 0xFFFFFFFF);
    
    for (int i = NUM_KEYS - 1; i >= 0; i--) {
        feistel_function(&right, keys[i]);
        uint32_t temp = left;
        left = right;
        right = temp;
    }
    
    *block = ((uint64_t)right << 32) | left;
    inverse_initial_permutation(block);
}

void generate_keys(uint64_t key, uint64_t keys[NUM_KEYS]) {
    uint64_t key_perm = 0;

    permute(PC1, &key, &key_perm, 64, 56);
    
    uint32_t C = (uint32_t)(key_perm >> 28);
    uint32_t D = (uint32_t)(key_perm & 0x0FFFFFFF);
    
    for (int i = 0; i < NUM_KEYS; i++) {
        C = (C << shift_schedule[i]) | (C >> (28 - shift_schedule[i]));
        D = (D << shift_schedule[i]) | (D >> (28 - shift_schedule[i]));
        
        uint64_t combined_key = ((uint64_t)C << 28) | D;
        permute(PC2, &combined_key, &keys[i], 56, 48);
    }
}

void feistel_function(uint32_t *half_block, uint32_t subkey) {
    uint32_t expanded = 0; 
    permute(E, (uint64_t *)half_block, (uint64_t *)&expanded, 32, 48);
    
    expanded ^= subkey;
    
    for (int i = 0; i < 8; i++) {
        int row = ((expanded >> (6 * i)) & 0x20) | ((expanded >> (6 * i + 5)) & 0x01);
        int col = (expanded >> (6 * i + 1)) & 0x0F;
        expanded &= ~(0x3F << (6 * i)); 
        expanded |= (S[i][row * 16 + col] << (4 * i));
    }
    
    uint32_t permuted = 0; 
    permute(P, (uint64_t *)&expanded, (uint64_t *)&permuted, 32, 32);
    *half_block ^= permuted;
}

void initial_permutation(uint64_t *block) {
    uint64_t temp = 0;
    permute(IP, block, &temp, 64, 64);
    *block = temp;
}

void inverse_initial_permutation(uint64_t *block) {
    uint64_t temp = 0;
    permute(IP_INV, block, &temp, 64, 64);
    *block = temp;
}

void permute(const int *table, const uint64_t *input, uint64_t *output, int input_size, int output_size) {
    *output = 0;
    for (int i = 0; i < output_size; i++) {
        int bit = (input_size - table[i]);
        *output |= ((*input >> bit) & 1) << (output_size - 1 - i);
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1; 
    uint64_t keys[NUM_KEYS];
    generate_keys(key, keys);
    
    uint64_t ciphertext = 0x0123456789ABCDEF; 
    printf("Ciphertext: %016lX\n", ciphertext);
    
    des_decrypt(&ciphertext, keys);
    
    printf("Decrypted text: %016lX\n", ciphertext);
    return 0;
}
