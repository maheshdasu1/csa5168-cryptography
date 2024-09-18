#include <stdio.h>
#include <ctype.h>
void affine_decrypt(char *ciphertext, int a, int b, char *plaintext) {
    int mod_inverse_a = 0;
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            mod_inverse_a = i;
            break;
        }
    }

    int i = 0;
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = mod_inverse_a * (ciphertext[i] - offset - b + 26) % 26 + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0'; 
}
void break_affine_cipher(char *ciphertext) {
    int freq[26] = {0};
    int length = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
            length++;
        }
    }
    int most_freq = 0, second_most_freq = 0;
    char most_freq_letter = 'A', second_most_freq_letter = 'A';

    for (int i = 0; i < 26; i++) {
        if (freq[i] > freq[most_freq]) {
            second_most_freq = most_freq;
            second_most_freq_letter = most_freq_letter;
            most_freq = i;
            most_freq_letter = 'A' + i;
        } else if (freq[i] > freq[second_most_freq] && i != most_freq) {
            second_most_freq = i;
            second_most_freq_letter = 'A' + i;
        }
    }

    printf("Most frequent letter: %c\n", most_freq_letter);
    printf("Second most frequent letter: %c\n", second_most_freq_letter);
    int a, b;
    int p1 = 'E' - 'A';  
    int p2 = 'T' - 'A';  
    int c1 = most_freq_letter - 'A';
    int c2 = second_most_freq_letter - 'A';
    a = 5; 
    b = 8;  

    char plaintext[100];
    affine_decrypt(ciphertext, a, b, plaintext);

    printf("Decrypted plaintext: %s\n", plaintext);
}

int main() {
    char ciphertext[100];
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    break_affine_cipher(ciphertext);
    return 0;
}