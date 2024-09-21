#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

void calculate_frequency(const char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            frequency[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            frequency[c - 'a']++;
        }
    }
}

void decrypt_with_shift(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = ((c - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = ((c - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = c; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

void generate_possible_plaintexts(const char *ciphertext, char possible_plaintexts[MAX_PLAINTEXTS][256]) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    int max_frequency_index = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > frequency[max_frequency_index]) {
            max_frequency_index = i;
        }
    }

    for (int i = 0; i < MAX_PLAINTEXTS; i++) {
        int shift = (max_frequency_index - (4 + i) + ALPHABET_SIZE) % ALPHABET_SIZE; 
        decrypt_with_shift(ciphertext, shift, possible_plaintexts[i]);
    }
}

int main() {
    char ciphertext[256];
    char possible_plaintexts[MAX_PLAINTEXTS][256];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; 

    generate_possible_plaintexts(ciphertext, possible_plaintexts);

    printf("Possible plaintexts based on letter frequency:\n");
    for (int i = 0; i < MAX_PLAINTEXTS; i++) {
        printf("%d: %s\n", i + 1, possible_plaintexts[i]);
    }

    return 0;
}
