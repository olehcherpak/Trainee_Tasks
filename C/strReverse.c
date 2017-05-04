#include <stdio.h>

#define MAX_LENGTH 101

int strLen(char str[]) {
    char* runPtr = str;
    for (; *runPtr != '\0'; runPtr++) {}
    return runPtr - str;
}

void strReverse(char str[], int size) {
    char *forwardPtr = str;
    char *reversePtr = str + size;
    
    reversePtr -= 1;
    for (char tmp; reversePtr > forwardPtr; forwardPtr++, reversePtr--) {
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
    strReverse(str, strLen(str));
    fprintf(outfile, "%s\n", str);
    fclose(outfile);
    
    return 0;

}
