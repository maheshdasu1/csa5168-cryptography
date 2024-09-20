#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define P_SIZE 20 
#define Q_SIZE 20 
#define G_SIZE 20 
#define HASH_SIZE 20 

typedef struct {
    unsigned char p[P_SIZE]; /
    unsigned char q[Q_SIZE]; 
    unsigned char g[G_SIZE]; 
    unsigned char x[P_SIZE]; 
    unsigned char y[P_SIZE]; 
} DSA_Key;

void hash(const unsigned char *input, size_t len, unsigned char *output) {
    
    for (size_t i = 0; i < HASH_SIZE; i++) {
        output[i] = (i < len) ? (input[i] % 256) : 0;
    }
}

unsigned char generate_k() {
    return rand() % 256; 
}

void dsa_sign(const unsigned char *message, unsigned char *signature) {
    unsigned char k = generate_k(); 
    unsigned char hash_value[HASH_SIZE];
    
    hash(message, strlen((char *)message), hash_value);
    
    signature[0] = k; 
    memcpy(signature + 1, hash_value, HASH_SIZE); 

}

int dsa_verify(const unsigned char *message, const unsigned char *signature) {
    unsigned char hash_value[HASH_SIZE];
    
    hash(message, strlen((char *)message), hash_value);
    
 
    return memcmp(hash_value, signature + 1, HASH_SIZE) == 0; 
}

int main() {
    srand(time(NULL)); 

    const unsigned char message1[] = "Hello, World!";
    const unsigned char message2[] = "Hello, World!";

    unsigned char signature1[HASH_SIZE + 1]; 
    unsigned char signature2[HASH_SIZE + 1]; 

    dsa_sign(message1, signature1);
    dsa_sign(message2, signature2);

    printf("Signature 1: ");
    for (int i = 0; i < HASH_SIZE + 1; i++) {
        printf("%02x", signature1[i]);
    }
    printf("\n");

    printf("Signature 2: ");
    for (int i = 0; i < HASH_SIZE + 1; i++) {
        printf("%02x", signature2[i]);
    }
    printf("\n");

    if (dsa_verify(message1, signature1)) {
        printf("Signature 1 verified successfully.\n");
    } else {
        printf("Signature 1 verification failed.\n");
    }

    if (dsa_verify(message2, signature2)) {
        printf("Signature 2 verified successfully.\n");
    } else {
        printf("Signature 2 verification failed.\n");
    }

    return 0;
}
