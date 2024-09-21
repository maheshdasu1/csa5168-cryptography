#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 

void simple_encrypt(uint8_t *data, uint8_t *key, uint8_t *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = data[i] ^ key[i]; 
    }
}

int main() {
   
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t plaintext[BLOCK_SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}; 
    uint8_t ciphertext[BLOCK_SIZE];
    uint8_t decrypted[BLOCK_SIZE];

    printf("Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%c", plaintext[i]);
    }
    printf("\n");

    simple_encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    simple_encrypt(ciphertext, key, decrypted); 
    printf("Decrypted: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    return 0;
}
