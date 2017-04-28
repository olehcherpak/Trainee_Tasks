#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256

void strCopy(char target[], char source[]) {
    for (; *source != '\0'; source++, target++) {
        *target = *source;
    }
}

int main() {
    size_t bufsize = MAX_LENGTH;
    char* str1 = (char *)malloc(bufsize);
    char* str2 = (char *)malloc(bufsize);
    
    getline(&str1, &bufsize, stdin);
    
    strCopy(str2, str1);
    
    printf("%s", str2);
    
    return 0;
}