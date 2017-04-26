#include <stdio.h>

int sum(int n) {
    return (n + 1) * n / 2;
}

int main() {
    int total;
    
    scanf("%d", &total);
    
    for (int row = total; row > 0; row--) {
        int end_of_row = sum(row);
        for (int value = sum(row -1) + 1; value < end_of_row; value++) {
            printf("%d ", value);
        }
        printf("%d\n", end_of_row);
    }
    
    return 0;
}