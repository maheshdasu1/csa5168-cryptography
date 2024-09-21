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

void sort_frequency(int *frequency, char *letters) {
    int indices[ALPHABET_SIZE];
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        indices[i] = i;
        letters[i] = 'A' + i; 
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = 0; j < ALPHABET_SIZE - 1 - i; j++) {
            if (frequency[indices[j]] < frequency[indices[j + 1]]) {
                // Swap indices
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letters[i] = 'A' + indices[i]; 
    }
}

void decrypt_with_substitution(const char *ciphertext, char *substitution, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = substitution[c - 'A'];
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = substitution[c - 'a'] + 32; 
        } else {
            plaintext[i] = c; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

void generate_possible_plaintexts(const char *ciphertext, char possible_plaintexts[MAX_PLAINTEXTS][256]) {
    int frequency[ALPHABET_SIZE] = {0};
    char letters[ALPHABET_SIZE];
    calculate_frequency(ciphertext, frequency);
    sort_frequency(frequency, letters);

    const char *frequency_order = "ETAOINSHRDLCUMWFGYPBVKJXQZ"; 
    char substitution[ALPHABET_SIZE];
    
    for (int i = 0; i < MAX_PLAINTEXTS; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            substitution[j] = letters[j]; 
        }

        for (int j = 0; j < ALPHABET_SIZE; j++) {
            substitution[j] = frequency_order[j];
        }

        decrypt_with_substitution(ciphertext, substitution, possible_plaintexts[i]);
    }
}

int main() {
    char ciphertext[256];
    char possible_plaintexts[MAX_PLAINTEXTS][256];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; 

    generate_possible_plaintexts(ciphertext, possible_plaintexts);

    printf("Top possible plaintexts based on letter frequency:\n");
    for (int i = 0; i < MAX_PLAINTEXTS; i++) {
        printf("%d: %s\n", i + 1, possible_plaintexts[i]);
    }

    return 0;
}
