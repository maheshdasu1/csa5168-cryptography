#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ALPHABET_SIZE 26

void encrypt_vigenere(char *plaintext, int *key, int key_length, char *ciphertext) {
    int i, shift;
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            shift = key[i % key_length];
            ciphertext[i] = 'A' + (plaintext[i] - 'A' + shift) % ALPHABET_SIZE;
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            shift = key[i % key_length];
            ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[i] = '\0'; 
}

int main() {
    char plaintext[256];
    int key[256];
    char ciphertext[256];

    printf("Enter the plaintext (uppercase or lowercase letters): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 

    srand(time(NULL)); 
    int key_length = strlen(plaintext);
    for (int i = 0; i < key_length; i++) {
        key[i] = rand() % ALPHABET_SIZE; 
    }

    encrypt_vigenere(plaintext, key, key_length, ciphertext);

    printf("Generated Key: ");
    for (int i = 0; i < key_length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
