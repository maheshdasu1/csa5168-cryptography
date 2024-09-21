#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

char encrypt_affine(int a, int b, char p) {
    if (p >= 'A' && p <= 'Z') {
        return 'A' + (a * (p - 'A') + b) % ALPHABET_SIZE;
    } else if (p >= 'a' && p <= 'z') {
        return 'a' + (a * (p - 'a') + b) % ALPHABET_SIZE;
    }
    return p; 
}

int is_coprime(int a) {
    int gcd = 1;
    for (int i = 1; i <= a && i <= ALPHABET_SIZE; i++) {
        if (a % i == 0 && ALPHABET_SIZE % i == 0) {
            gcd = i;
        }
    }
    return gcd == 1;
}

int main() {
    char plaintext[256];
    int a, b;

    printf("Enter value for a (must be coprime with 26): ");
    scanf("%d", &a);
    if (!is_coprime(a)) {
        printf("Error: %d is not coprime with %d. Please choose a different value.\n", a, ALPHABET_SIZE);
        return 1;
    }

    printf("Enter value for b: ");
    scanf("%d", &b);

    printf("Enter the plaintext (uppercase or lowercase letters): ");
    scanf(" %[^\n]s", plaintext); 

    char ciphertext[256];
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = encrypt_affine(a, b, plaintext[i]);
    }
    ciphertext[strlen(plaintext)] = '\0'; 

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
