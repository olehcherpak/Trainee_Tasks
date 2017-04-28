#include <stdio.h>
#include <stdlib.h>

void strCopy(char target[], char source[]) {
    for (; *source != '\0'; source++, target++) {
        *target = *source;
    }
    
    *target = *source;
}

int main() {
    char str1[] = "WoW";
    char str2[] = "Wrong message";
    
    strCopy(str2, str1);
    
    printf("%s\n", str2);
    
    return 0;
}
