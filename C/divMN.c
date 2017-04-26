#include <stdio.h>

int main() {
    int min, max;
    int m, n;
    int lcm, mindivisor;
    scanf("%d %d %d %d", &min, &max, &m, &n);
    
    for (lcm = m > n ? m : n; lcm % m || lcm % n; lcm++) {
        ;
    }
    
    for (; min <= max;) {
        if (min % lcm) {
            min += 1;
        } else {
            printf("%d\n", min);
            min += lcm;
        }
    }
    
    return 0;
}