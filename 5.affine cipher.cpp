#include <stdio.h>
#include <ctype.h>
void affine_encrypt(char *plaintext, int a, int b, char *ciphertext) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (a * (plaintext[i] - offset) + b) % 26 + offset;
        } else {
            ciphertext[i] = plaintext[i];
        }
        i++;
    }
    ciphertext[i] = '\0'; 
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter key a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter key b: ");
    scanf("%d", &b);
    affine_encrypt(plaintext, a, b, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}