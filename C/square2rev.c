#include <stdio.h>

int main() {
    int total;
    
    scanf("%d", &total);
    
    for (int row = total; row > 0; row--) {
        int end_of_row = total * row;
        for (int value = total * (row - 1) + 1; value < end_of_row; value++) {
            printf("%d ", value);
        }
        printf("%d\n", end_of_row);
    }
    
    return 0;
}