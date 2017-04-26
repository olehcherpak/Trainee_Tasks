#include <stdio.h>

int pascalRec(int row, int col) {
    if (col == 0 ) {
	return 1;
    }
    
    return pascalRec(row - 1, col - 1) + pascalRec(row - 1, col);
}

int main() {
    int lines;
    
    scanf("%d", &lines);

    for (int row = 0; row < lines; row++) {
	for (int col = 0; col < row; col++) {
	    printf("%d ", pascalRec(row, col));
	}
	printf("1\n");
    }
    
    return 0;
}