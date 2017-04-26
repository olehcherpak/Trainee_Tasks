#include <stdio.h>

#define DIVISOR 2
int main() {
    int start, finish;
    
    scanf("%d %d", &start, &finish);
    
    if (start % DIVISOR) {
	start += 1;
    }
    if (finish % DIVISOR) {
	finish -= 1;
    }
    
    for (; start < finish; start += DIVISOR) {
	printf("%d ", start);
    }
    printf("%d\n", finish);
    
    return 0;
}