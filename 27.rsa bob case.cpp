#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int e, int phi) {
    int x0 = 0, x1 = 1, a = e, b = phi;
    if (phi == 1) return 0;

    while (a > 1) {
        int q = a / b;
        int t = b;
        b = a % b; 
        a = t;
        t = x0; 
        x0 = x1 - q * x0; 
        x1 = t;
    }

    if (x1 < 0) x1 += phi; 
    return x1;
}

int encrypt(int plaintext, int e, int n) {
    return (int)pow(plaintext, e) % n; 
}

int main() {
   
    int p = 61; 
    int q = 53;
    int n = p * q; 
    int phi = (p - 1) * (q - 1); 
    int e = 17; 

    char message[] = "HELLO";
    int encrypted[sizeof(message)]; 

    for (int i = 0; message[i] != '\0'; i++) {
        int plaintext = message[i] - 'A'; 
        encrypted[i] = encrypt(plaintext, e, n);
        printf("Encrypted %c -> %d\n", message[i], encrypted[i]);
    }


    return 0;
}
