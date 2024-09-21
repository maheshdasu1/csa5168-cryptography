#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10  

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

int determinant(int key[MAX_SIZE][MAX_SIZE], int size) {
    int det = 0;
    if (size == 1) {
        return key[0][0];
    }
    if (size == 2) {
        return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);
    }
   
    return det;
}

void encrypt_hill(int key[MAX_SIZE][MAX_SIZE], int size, char *plaintext, char *ciphertext) {
    int length = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < length; i += size) {
        int temp[MAX_SIZE] = {0};
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if (i + k < length) {
                    temp[j] += key[j][k] * (plaintext[i + k] - 'A');
                }
            }
            temp[j] = (temp[j] % 26 + 26) % 26; 
            ciphertext[index++] = temp[j] + 'A';
        }
    }
    ciphertext[index] = '\0'; 
}

void decrypt_hill(int key[MAX_SIZE][MAX_SIZE], int size, char *ciphertext, char *plaintext) {
    int det = determinant(key, size);
    int inv_det = mod_inverse(det, 26);
    
    if (inv_det == -1) {
        printf("Key is not invertible; cannot decrypt.\n");
        return;
    }

    int adj[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            adj[j][i] = key[(i + 1) % size][(j + 1) % size] * inv_det % 26; 
        }
    }

    int length = strlen(ciphertext);
    int index = 0;

    for (int i = 0; i < length; i += size) {
        int temp[MAX_SIZE] = {0};
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if (i + k < length) {
                    temp[j] += adj[j][k] * (ciphertext[i + k] - 'A');
                }
            }
            temp[j] = (temp[j] % 26 + 26) % 26; 
            plaintext[index++] = temp[j] + 'A';
        }
    }
    plaintext[index] = '\0'; 
}

int main() {
    int key[MAX_SIZE][MAX_SIZE] = { {6, 24}, {1, 13} }; 
    char plaintext[256], ciphertext[256];

    printf("Enter the plaintext (uppercase letters only): ");
    scanf(" %[^\n]s", plaintext); 

    encrypt_hill(key, 2, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    char decrypted[256];
    decrypt_hill(key, 2, ciphertext, decrypted);
    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}
