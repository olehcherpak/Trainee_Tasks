#include <stdio.h>

#define MAX_LENGTH 101

int strLen(char str[]) {
    char* runPtr = str;
    for (; *runPtr != '\0'; runPtr++) {
        ;
    }
    return runPtr - str;
}

int main() {
    char str[MAX_LENGTH];
    FILE* infile = fopen("task.in", "r");
    FILE* outfile = fopen("task.out", "w");
    
    fscanf(infile, "%s", str);
    
    fclose(infile);
    
    fprintf(outfile, "%d\n", strLen(str));
    fclose(outfile);
    
    return 0;
}
