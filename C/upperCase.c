#include <stdio.h>

#define FIRST_LETTER 'a'
#define LAST_LETTER 'z'
#define SHIFT ('A' - 'a')

int main() {
    char symbol;
    char shift = SHIFT;
    FILE* infile = fopen("task.in", "r");
    FILE* outfile = fopen("task.out", "w");
    
    for (; !feof(infile);) {
        fscanf(infile, "%c", &symbol);
        if (symbol >= FIRST_LETTER && symbol <= LAST_LETTER) {
            symbol += shift;
        }
        fprintf(outfile, "%c", symbol);
    }
    
    fclose(infile);
    fclose(outfile);
    
    return 0;
}
