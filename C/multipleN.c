#include <stdio.h>

int main() {
    int endvalue, divisor;
    int start;
    
    scanf("%d %d", &endvalue, &divisor);
    
    endvalue -= divisor;
    for (start = 0; start < endvalue ; start += divisor) {
	    printf("%d ", start);
    }
    printf("%d\n", start);
    
    return 0;
}