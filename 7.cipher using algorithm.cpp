#include <stdio.h>
#include <ctype.h>
#define CHAR_COUNT 128
void count_frequency(char *text, int freq[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i]) || isdigit(text[i]) || ispunct(text[i])) {
            freq[(unsigned char)text[i]]++;
        }
    }
}
void print_frequency(int freq[]) {
    for (int i = 0; i < CHAR_COUNT; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}
void decrypt(char *ciphertext, char *substitute_map, char *plaintext) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i]) || isdigit(ciphertext[i]) || ispunct(ciphertext[i])) {
            plaintext[i] = substitute_map[(unsigned char)ciphertext[i]];
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0'; 
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡8†83 (88)5†;46(;88*96*?;8)‡(;485);5†2:‡(;4956*2(5—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    int freq[CHAR_COUNT] = {0};
    char substitute_map[CHAR_COUNT];
    char plaintext[1000];
    for (int i = 0; i < CHAR_COUNT; i++) {
        substitute_map[i] = i;
    }
    count_frequency(ciphertext, freq);
    printf("Character frequencies:\n");
    print_frequency(freq);
    substitute_map['‡'] = 'e'; 
    substitute_map['†'] = 't'; 
    substitute_map['8'] = 'h';
    decrypt(ciphertext, substitute_map, plaintext);
    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}