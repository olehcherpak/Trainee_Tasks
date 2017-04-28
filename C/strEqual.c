#include <stdio.h>

#define MAX_LENGTH 101

int strEqual(char str1[], char str2[]) {
    for (; *str1 != '\0' || *str2 != '\0'; str1++, str2++) {
        if (*str1 != *str2) {
            return 0;
        }
    }
    if (*str1 != *str2) {
        return 0;
    }
    
    return 1;
}

int main() {
    char str1[MAX_LENGTH];
    char str2[MAX_LENGTH];
    FILE* infile = fopen("task.in", "r");
    FILE* outfile = fopen("task.out", "w");
    
    fgets(str1, MAX_LENGTH, infile);
    fgets(str2, MAX_LENGTH, infile);
    
    fclose(infile);

    if (strEqual(str1,str2)) {
        fprintf(outfile, "yes\n");
    } else {
        fprintf(outfile, "no\n");
    }
    
    fclose(outfile);
    
}
