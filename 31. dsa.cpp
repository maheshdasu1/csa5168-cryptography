#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16 
#define CONSTANT_128 0x87
#define CONSTANT_64 0x1B

void block_cipher(const unsigned char *input, unsigned char *output) {
    
    memset(output, 0, BLOCK_SIZE); 
    output[BLOCK_SIZE - 1] = 0xFF; 
}

void generate_subkey(const unsigned char *input, unsigned char *subkey, int block_size) {
    unsigned char block[BLOCK_SIZE];
    unsigned char temp[BLOCK_SIZE];
    
    block_cipher(input, block);

    int carry = (block[0] & 0x80) ? 1 : 0; 
    for (int i = 0; i < BLOCK_SIZE - 1; i++) {
        subkey[i] = (block[i] << 1) | (block[i + 1] >> 7); 
    }
    subkey[BLOCK_SIZE - 1] = block[BLOCK_SIZE - 1] << 1; 

    if (carry) {
        if (block_size == 128) {
            subkey[BLOCK_SIZE - 1] ^= CONSTANT_128; 
        } else if (block_size == 64) {
            subkey[BLOCK_SIZE - 1] ^= CONSTANT_64; 
        }
    }
}

int main() {
    unsigned char zero_block[BLOCK_SIZE] = {0}; 
    unsigned char K1[BLOCK_SIZE];
    unsigned char K2[BLOCK_SIZE];

    generate_subkey(zero_block, K1, 128);
    printf("K1: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", K1[i]);
    }
    printf("\n");

    generate_subkey(K1, K2, 128);
    printf("K2: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", K2[i]);
    }
    printf("\n");

    return 0;
}
