#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int extended_euclidean(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = extended_euclidean(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int mod_inverse(int e, int phi) {
    int x, y;
    int g = extended_euclidean(e, phi, &x, &y);
    if (g != 1) {
        printf("Inverse doesn't exist\n");
        return -1; 
    } else {
        return (x % phi + phi) % phi; 
    }
}

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

void find_p_q(int n, int *p, int *q) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            int j = n / i;
        
            if (is_prime(i) && is_prime(j)) {
                *p = i;
                *q = j;
                return;
            }
        }
    }
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q;

    find_p_q(n, &p, &q);
    printf("Found primes: p = %d, q = %d\n", p, q);
    
    int phi = (p - 1) * (q - 1);
    printf("Calculated phi(n) = %d\n", phi);
    
    int d = mod_inverse(e, phi);
    if (d != -1) {
        printf("Private key d = %d\n", d);
    }

    return 0;
}
