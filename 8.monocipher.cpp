#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define ALPHABET_SIZE 100
void create_cipher_alphabet(char *keyword, char *cipher_alphabet) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;
    for (int i = 0; i < strlen(keyword); i++) {
        char c = toupper(keyword[i]);
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            cipher_alphabet[index++] = c;
            used[c - 'A'] = 1;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipher_alphabet[index++] = c;
        }
    }
    cipher_alphabet[index] = '\0'; 
}
void encrypt(char *plaintext, char *cipher_alphabet, char *ciphertext) {
    char alphabet[ALPHABET_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;
    while (plaintext[i] != '\0') {
        char c = toupper(plaintext[i]);
        if (c >= 'A' && c <= 'Z') {
            int pos = c - 'A';
            ciphertext[i] = cipher_alphabet[pos];
        } else {
            ciphertext[i] = plaintext[i];
        }
        i++;
    }
    ciphertext[i] = '\0';
}

int main() {
    char keyword[100], plaintext[1000], ciphertext[1000];
    char cipher_alphabet[ALPHABET_SIZE + 1];
    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0; 
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;
    create_cipher_alphabet(keyword, cipher_alphabet);
    encrypt(plaintext, cipher_alphabet, ciphertext);
    printf("Cipher alphabet: %s\n", cipher_alphabet);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}