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

int main() {
    char ciphertext[256];
    int frequency[ALPHABET_SIZE] = {0};
    char letters[ALPHABET_SIZE];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; 

    calculate_frequency(ciphertext, frequency);

    sort_frequency(frequency, letters);

    printf("Possible plaintexts based on letter frequency:\n");
    for (int i = 0; i < MAX_PLAINTEXTS && i < ALPHABET_SIZE; i++) {
        printf("%d: %c\n", i + 1, letters[i]);
    }

    return 0;
}
