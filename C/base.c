#include <stdio.h>

#define BASE10 10

int main() {
    int num, base;
    int tmpNumber;
    int tmpBase = 1;
    int count = 1;
    
    scanf("%d %d",&num, &base);
    
    if (num > 0) {
	tmpNumber = num;
    } else {
	tmpNumber = -num;
	printf("-");
    }
    
    while (tmpBase * base <= tmpNumber) {
	count++;
	tmpBase *= base;
    }
    
    while (tmpNumber) {
	int res = tmpNumber / tmpBase;
	printf("%c", (res < BASE10) ? (res + '0') : (res - BASE10 + 'A'));
	tmpNumber %= tmpBase;
	tmpBase /= base;
	count--;
    }
    
    while (count--) {
	printf("0");
    }
    printf("\n");
    
    return 0;
}