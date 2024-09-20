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

int decrypt(int ciphertext, int d, int n) {
    return (int)pow(ciphertext, d) % n; 
}

int main() {
  
    int p = 61; 
    int q = 53; 
    int n = p * q; 
    int phi = (p - 1) * (q - 1); 
    int e = 17; 
    int d = mod_inverse(e, phi); 

    printf("Public Key: (e: %d, n: %d)\n", e, n);
    printf("Private Key: (d: %d)\n", d);

    int plaintext = 65; 
    int ciphertext = encrypt(plaintext, e, n);
    printf("Ciphertext: %d\n", ciphertext);

    int decrypted = decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %d\n", decrypted);

    return 0;
}
