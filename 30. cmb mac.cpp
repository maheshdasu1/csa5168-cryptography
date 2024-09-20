#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16 

void block_cipher(unsigned char *input, unsigned char *key, unsigned char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; 
    }
}

void cbc_mac(unsigned char *key, unsigned char *message, unsigned char *mac) {
    unsigned char iv[BLOCK_SIZE] = {0}; 
    unsigned char ciphertext[BLOCK_SIZE];

    for (int i = 0; i < strlen((char *)message); i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE] = {0};
        memcpy(block, message + i, BLOCK_SIZE);
        
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= iv[j];
        }

        block_cipher(block, key, ciphertext);
        
        memcpy(iv, ciphertext, BLOCK_SIZE);
    }

    memcpy(mac, ciphertext, BLOCK_SIZE);
}

int main() {
    unsigned char key[BLOCK_SIZE] = "secret_key12345";
    unsigned char message[BLOCK_SIZE] = "message_block_1"; 
    unsigned char mac[BLOCK_SIZE];

    cbc_mac(key, message, mac);

    printf("MAC(K, X): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    unsigned char message_xor[BLOCK_SIZE * 2];
    memcpy(message_xor, message, BLOCK_SIZE); 
    for (int i = 0; i < BLOCK_SIZE; i++) {
        message_xor[BLOCK_SIZE + i] = message[i] ^ mac[i]; 
    }

    unsigned char mac_two_block[BLOCK_SIZE];
    cbc_mac(key, message_xor, mac_two_block);

    printf("MAC(K, X || (X ? T)): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac_two_block[i]);
    }
    printf("\n");

    return 0;
}
