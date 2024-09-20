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

void find_p_q(int n, int common_factor, int *p, int *q) {
    *p = common_factor;
    *q = n / common_factor;
}

int main() {
    int n = 3599;  
    int e = 31;    
    int common_factor = 59; 
    int p, q;

    find_p_q(n, common_factor, &p, &q);
    
    printf("Found factors: p = %d, q = %d\n", p, q);
    
    int phi = (p - 1) * (q - 1);
    printf("Calculated phi(n) = %d\n", phi);


    return 0;
}
