#include <stdio.h>
#include <math.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % mod;
        exp = exp >> 1; 
        base = (base * base) % mod; 
    }
    return result;
}

int main() {
  
    long long q = 23; 
    long long a = 5;  

    long long x = 6; 
    long long A = mod_exp(a, x, q); 

    long long y = 15; 
    long long B = mod_exp(a, y, q);

    long long K_Alice = mod_exp(B, x, q); 
    long long K_Bob = mod_exp(A, y, q);   

    printf("Alice's Public Value: %lld\n", A);
    printf("Bob's Public Value: %lld\n", B);
    printf("Shared Secret (Alice): %lld\n", K_Alice);
    printf("Shared Secret (Bob): %lld\n", K_Bob);

    return 0;
}
