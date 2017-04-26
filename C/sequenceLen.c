#include <stdio.h>

int main() {
    int sequence[100];
    int* buffer;
    FILE* infile;
    FILE* outfile;
    
    infile = fopen("task.in", "r");
    for (buffer = sequence; fscanf(infile, "%d", buffer) == 1; buffer++) {
        ;
    }
    fclose(infile);
    
    outfile = fopen("task.out", "w");
    fprintf(outfile, "%ld\n", buffer - sequence);
    fclose(outfile);
}