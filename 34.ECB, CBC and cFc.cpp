#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 
void xor_operation(uint8_t *data, uint8_t *key, uint8_t *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = data[i] ^ key[i];
    }
}

void ecb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, size_t blocks) {
    for (size_t i = 0; i < blocks; i++) {
        xor_operation(plaintext + (i * BLOCK_SIZE), key, ciphertext + (i * BLOCK_SIZE));
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, uint8_t *iv, size_t blocks) {
    uint8_t previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE);
    
    for (size_t i = 0; i < blocks; i++) {
        uint8_t temp[BLOCK_SIZE];
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = plaintext[i * BLOCK_SIZE + j] ^ previous_block[j];
        }
        xor_operation(temp, key, ciphertext + (i * BLOCK_SIZE));
        memcpy(previous_block, ciphertext + (i * BLOCK_SIZE), BLOCK_SIZE);
    }
}

void cfb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, uint8_t *iv, size_t blocks) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);
    
    for (size_t i = 0; i < blocks; i++) {
        uint8_t temp[BLOCK_SIZE];
        xor_operation(feedback, key, temp);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i * BLOCK_SIZE + j] = plaintext[i * BLOCK_SIZE + j] ^ temp[j];
        }
        memcpy(feedback, ciphertext + (i * BLOCK_SIZE), BLOCK_SIZE);
    }
}

void pad_plaintext(uint8_t *data, size_t *length) {
    size_t original_length = *length;
    size_t padding_length = BLOCK_SIZE - (original_length % BLOCK_SIZE);
    *length += padding_length;

    data[original_length] = 0x80; 
    for (size_t i = original_length + 1; i < *length; i++) {
        data[i] = 0x00; 
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}; 
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t plaintext[BLOCK_SIZE * 3] = "HELLO WORLD!"; 
    size_t length = strlen((char *)plaintext);
    pad_plaintext(plaintext, &length); 

    size_t blocks = length / BLOCK_SIZE; 

    uint8_t ciphertext[BLOCK_SIZE * 3];
    uint8_t decrypted[BLOCK_SIZE * 3];

    printf("Plaintext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%c", plaintext[i]);
    }
    printf("\n");

    ecb_encrypt(plaintext, key, ciphertext, blocks);
    printf("ECB Ciphertext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    memset(ciphertext, 0, sizeof(ciphertext)); 
    cbc_encrypt(plaintext, key, ciphertext, iv, blocks);
    printf("CBC Ciphertext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    memset(ciphertext, 0, sizeof(ciphertext)); 
    cfb_encrypt(plaintext, key, ciphertext, iv, blocks);
    printf("CFB Ciphertext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
