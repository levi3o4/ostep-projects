#include <stdio.h>
#include <stdlib.h>

int unzipOneFile (char* fileName);
int scanText (FILE* file);
int printContents (char repetitions, char character);

int main (int argc, char *argv[]) {
    
    if (argc == 1) {
        
        puts("wunzip: file1 [file2 ...]");
        exit(1);
        
    }
    
    for (int i = 1; i < argc; i++) {
        
        unzipOneFile(argv[i]);
    }
    
    return 0;
}

int unzipOneFile (char* fileName) {

    FILE *file = fopen(fileName, "r"); 
    
    if (file == NULL) {
        printf("wunzip: cannot open file\n");
        exit(1); 
    }
    
    scanText(file);
    
    fclose(file);
}

int scanText (FILE* text) {

    int repetitions;
    char character;
    
    while ((fread(&repetitions, 4, 1, text)) == 1) {
        
        if ((fread(&character, 1, 1, text)) != 1) {
                exit(2);
        }
        
        printContents(repetitions, character);
    }
    
    puts("");
}

int printContents (char repetitions, char character) {
    
    for (int i = 0; i < repetitions; i++) {
        printf("%c", character);
    }
    
    return 0;
}