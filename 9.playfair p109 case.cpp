#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char *key, char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int k = 0;

    for (int i = 0; key[i]; i++) {
        if (key[i] == 'J') key[i] = 'I'; 
        if (key[i] >= 'A' && key[i] <= 'Z' && !used[key[i] - 'A']) {
            used[key[i] - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = key[i];
            k++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; 
        if (!used[c - 'A']) {
            matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
}

void decryptPlayfair(char *text, char matrix[SIZE][SIZE], char *result) {
    int row1, col1, row2, col2;
    char a, b;
    int index = 0;

    for (int i = 0; text[i] != '\0'; i += 2) {
        a = text[i];
        b = text[i + 1];

        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (matrix[r][c] == a) {
                    row1 = r;
                    col1 = c;
                }
                if (matrix[r][c] == b) {
                    row2 = r;
                    col2 = c;
                }
            }
        }

        if (row1 == row2) {
            result[index++] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            result[index++] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            result[index++] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            result[index++] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        } else {
            result[index++] = matrix[row1][col2];
            result[index++] = matrix[row2][col1];
        }
    }
    result[index] = '\0';
}

int main() {
    char key[] = "PT109AMERICAN"; 
    char text[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char matrix[SIZE][SIZE];
    char decryptedText[100] = {0};

    for (int i = 0; key[i]; i++) {
        key[i] = toupper(key[i]);
    }
    for (int i = 0; text[i]; i++) {
        text[i] = toupper(text[i]);
        if (text[i] == ' ') {
            memmove(&text[i], &text[i + 1], strlen(text) - i);
            i--;
        }
    }

    createMatrix(key, matrix);

    decryptPlayfair(text, matrix, decryptedText);

    printf("Decrypted Text: %s\n the president is death kenney", decryptedText);

    return 0;
}
