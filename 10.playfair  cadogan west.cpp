#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char matrix[SIZE][SIZE]) {
    
    char predefinedMatrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            matrix[r][c] = predefinedMatrix[r][c];
        }
    }
}

void prepareText(char *text, char *preparedText) {
    int index = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] == ' ') continue; 
        char ch = toupper(text[i]);
        if (ch == 'J') ch = 'I'; 
        preparedText[index++] = ch;
    }
    preparedText[index] = '\0';

    for (int i = 0; i < index - 1; i++) {
        if (preparedText[i] == preparedText[i + 1]) {
            
            for (int j = index; j > i + 1; j--) {
                preparedText[j + 1] = preparedText[j];
            }
            preparedText[i + 1] = 'X';
            index++;
        }
    }

    if (index % 2 != 0) {
        preparedText[index++] = 'X';
        preparedText[index] = '\0';
    }
}

void encryptPlayfair(char *text, char matrix[SIZE][SIZE], char *result) {
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
            result[index++] = matrix[row1][(col1 + 1) % SIZE];
            result[index++] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            result[index++] = matrix[(row1 + 1) % SIZE][col1];
            result[index++] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            result[index++] = matrix[row1][col2];
            result[index++] = matrix[row2][col1];
        }
    }
    result[index] = '\0';
}

int main() {
    char matrix[SIZE][SIZE];
    char text[] = "Must see you over Cadogan West. Coming at once.";
    char preparedText[100] = {0};
    char encryptedText[100] = {0};

    createMatrix(matrix);

    prepareText(text, preparedText);

    encryptPlayfair(preparedText, matrix, encryptedText);

    printf("Prepared Text: %s\n", preparedText);
    printf("Encrypted Text: %s\n", encryptedText);

    return 0;
}
