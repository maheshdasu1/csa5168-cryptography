#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

double powerOf2(double exponent) {
    return pow(2, exponent);
}

int main() {
   
    int n = 25;
    unsigned long long totalPossibleKeys = factorial(n);
    double totalKeysPower2 = log2(totalPossibleKeys);
    
    double symmetries = 8.0; 
    double effectivelyUniqueKeys = totalPossibleKeys / symmetries;
    double uniqueKeysPower2 = log2(effectivelyUniqueKeys);


    printf("Total number of possible keys: %llu\n", totalPossibleKeys);
    printf("Approximate power of 2 for total keys: %.2f\n", totalKeysPower2);
    printf("Estimated number of effectively unique keys: %.0f\n", effectivelyUniqueKeys);
    printf("Approximate power of 2 for effectively unique keys: %.2f\n", uniqueKeysPower2);

    return 0;
}
