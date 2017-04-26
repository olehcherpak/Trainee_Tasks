#include <stdio.h>

int main() {
    int start, end;
    int devisor;
    
    scanf("%d %d %d", &start, &end, &devisor);
    
    while (start <= end) {
	if (start % devisor == 0) {
	    printf("%d\n", start);
	    start += devisor;
	} else {
	    start += 1;
	}
    }
    
    return 0;
}
