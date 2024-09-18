#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MOD 26

void textToNumeric(char *text, int *numericText) {
    int index = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            numericText[index++] = toupper(text[i]) - 'A';
        }
    }
}

void numericToText(int *numericText, char *text, int length) {
    for (int i = 0; i < length; i++) {
        text[i] = numericText[i] + 'A';
    }
    text[length] = '\0';
}

void matrixMultiply(int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
                result[i][j] %= MOD;
            }
        }
    }
}

void matrixInverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    int determinant = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] + MOD) % MOD;
    int invDet = 0;
    
    for (int i = 1; i < MOD; i++) {
        if ((determinant * i) % MOD == 1) {
            invDet = i;
            break;
        }
    }

    result[0][0] = (matrix[1][1] * invDet) % MOD;
    result[0][1] = (-matrix[0][1] * invDet + MOD) % MOD;
    result[1][0] = (-matrix[1][0] * invDet + MOD) % MOD;
    result[1][1] = (matrix[0][0] * invDet) % MOD;
}

void computeKeyMatrix(int plainText[MATRIX_SIZE][MATRIX_SIZE], int cipherText[MATRIX_SIZE][MATRIX_SIZE], int keyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int plainTextInverse[MATRIX_SIZE][MATRIX_SIZE];
    int cipherMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];
    
    matrixInverse(plainText, plainTextInverse);
    matrixMultiply(plainTextInverse, cipherText, resultMatrix);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            keyMatrix[i][j] = resultMatrix[i][j];
        }
    }
}

int main() {
    char plainText[] = "MEET"; 
    char cipherText[] = "XYYN"; 
    int plainTextMatrix[MATRIX_SIZE][MATRIX_SIZE] = {0};
    int cipherTextMatrix[MATRIX_SIZE][MATRIX_SIZE] = {0};
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {0};

    int numericPlainText[4], numericCipherText[4];
    textToNumeric(plainText, numericPlainText);
    textToNumeric(cipherText, numericCipherText);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            plainTextMatrix[i][j] = numericPlainText[i * MATRIX_SIZE + j];
            cipherTextMatrix[i][j] = numericCipherText[i * MATRIX_SIZE + j];
        }
    }

    computeKeyMatrix(plainTextMatrix, cipherTextMatrix, keyMatrix);

    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
