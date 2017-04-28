#include <stdio.h>

#define MAX_LENGTH 101

void strReverse(char str[]) {
    char *forwardPtr = str;
    char *reversePtr = str;
    
    for (; *reversePtr != '\0'; reversePtr++) {
        ;
    }
    reversePtr -= 1;
    for (char tmp; reversePtr - forwardPtr >= 1; forwardPtr++, reversePtr--) {
        tmp = *reversePtr;
        *reversePtr = *forwardPtr;
        *forwardPtr = tmp;
    }
}

int main() {
    char str[MAX_LENGTH];
    FILE* infile = fopen("task.in", "r");
    FILE* outfile = fopen("task.out", "w");
    
    fscanf(infile, "%100s", str);
    fclose(infile);
    strReverse(str);
    fprintf(outfile, "%s\n", str);
    fclose(outfile);
    
    return 0;

}
