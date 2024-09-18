#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LENGTH 1000
#define TOP_N 10

const double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.317, 9.056,
    2.758, 0.978, 2.560, 0.150, 1.929, 0.074
};

int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    int topN;

    printf("Enter ciphertext: ");
    fgets(ciphertext, MAX_CIPHERTEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    char plaintext[MAX_CIPHERTEXT_LENGTH];
    double frequency[ALPHABET_SIZE];
    double scores[ALPHABET_SIZE];
    int shifts[ALPHABET_SIZE];

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
    
        for (int i = 0; ciphertext[i]; i++) {
            if (isalpha(ciphertext[i])) {
                char base = isupper(ciphertext[i]) ? 'A' : 'a';
                plaintext[i] = (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
            } else {
                plaintext[i] = ciphertext[i];
            }
        }
        plaintext[strlen(ciphertext)] = '\0'; 

        int letterCount[ALPHABET_SIZE] = {0};
        int totalLetters = 0;
        for (int i = 0; plaintext[i]; i++) {
            if (isalpha(plaintext[i])) {
                int index = toupper(plaintext[i]) - 'A';
                letterCount[index]++;
                totalLetters++;
            }
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            frequency[i] = (totalLetters > 0) ? (100.0 * letterCount[i] / totalLetters) : 0.0;
        }

        double score = 0.0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            score += (frequency[i] - englishFrequencies[i]) * (frequency[i] - englishFrequencies[i]);
        }
        scores[shift] = score;
        shifts[shift] = shift;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[j] < scores[i]) {
               
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                int tempShift = shifts[i];
                shifts[i] = shifts[j];
                shifts[j] = tempShift;
            }
        }
    }

    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        int bestShift = shifts[i];
        
        for (int j = 0; ciphertext[j]; j++) {
            if (isalpha(ciphertext[j])) {
                char base = isupper(ciphertext[j]) ? 'A' : 'a';
                plaintext[j] = (ciphertext[j] - base - bestShift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
            } else {
                plaintext[j] = ciphertext[j];
            }
        }
        plaintext[strlen(ciphertext)] = '\0'; /

        printf("Shift %d: %s\n", bestShift, plaintext);
    }

    return 0;
}
