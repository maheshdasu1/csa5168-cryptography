#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MOD 26

void matrixMultiply(int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE][1], int result[MATRIX_SIZE][1]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i][0] = 0;
        for (int k = 0; k < MATRIX_SIZE; k++) {
            result[i][0] += a[i][k] * b[k][0];
        }
        result[i][0] %= MOD;
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

void textToNumeric(char *text, int *numericText, int *length) {
    int index = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            numericText[index++] = toupper(text[i]) - 'A';
        }
    }
    *length = index;
    if (*length % 2 != 0) {
        numericText[(*length)++] = 'X' - 'A'; 
    }
}

void numericToText(int *numericText, char *text, int length) {
    for (int i = 0; i < length; i++) {
        text[i] = numericText[i] + 'A';
    }
    text[length] = '\0';
}

void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {9, 4},
        {5, 7}
    };
    int inverseMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int numericText[100], encryptedText[100], decryptedText[100];
    int numLength, encLength, decLength;

    textToNumeric(plaintext, numericText, &numLength);

    for (int i = 0; i < numLength; i += 2) {
        int block[MATRIX_SIZE][1] = { {numericText[i]}, {numericText[i + 1]} };
        int result[MATRIX_SIZE][1];
        matrixMultiply(keyMatrix, block, result);
        encryptedText[i] = result[0][0];
        encryptedText[i + 1] = result[1][0];
    }

    numericToText(encryptedText, plaintext, numLength);
    printf("Encrypted Text: %s\n", plaintext);

    matrixInverse(keyMatrix, inverseMatrix);

    for (int i = 0; i < numLength; i += 2) {
        int block[MATRIX_SIZE][1] = { {encryptedText[i]}, {encryptedText[i + 1]} };
        int result[MATRIX_SIZE][1];
        matrixMultiply(inverseMatrix, block, result);
        decryptedText[i] = result[0][0];
        decryptedText[i + 1] = result[1][0];
    }

    numericToText(decryptedText, plaintext, numLength);
    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}
