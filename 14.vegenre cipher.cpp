#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

void findKeyStream(char *ciphertext, char *plaintext, int *keyStream, int keyLength) {
    int textLength = strlen(ciphertext);
    for (int i = 0; i < textLength; i++) {
        if (isalpha(ciphertext[i])) {
            int cipherVal = toupper(ciphertext[i]) - 'A';
            int plainVal = toupper(plaintext[i]) - 'A';
            keyStream[i % keyLength] = (cipherVal - plainVal + MOD) % MOD;
        }
    }
}

int main() {
    char ciphertext[] = "your_ciphertext_here"; // Replace with actual ciphertext from part (a)
    char plaintext[] = "cash not needed";
    int keyStream[100]; // Adjust size as needed
    int keyLength = sizeof(keyStream) / sizeof(keyStream[0]);
    
    findKeyStream(ciphertext, plaintext, keyStream, keyLength);

    printf("Key Stream:\n");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%d ", keyStream[i % keyLength]);
    }
    printf("\n");

    return 0;
}
