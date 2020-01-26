#include <stdio.h>
#include <stdlib.h>

int zipOneFile (char* fileName);
int scanText (FILE* file);
int printEntry (int repetitions, char character);

int main (int argc, char *argv[]) {
    
    if (argc == 1) {
        
        puts("wzip: file1 [file2 ...]");
        exit(1);
        
    }
    
    for (int i = 1; i < argc; i++) {
        
        zipOneFile(argv[i]);
    }
    
    return 0;
}

int zipOneFile (char* fileName) {

    FILE *file = fopen(fileName, "r"); 
    
    if (file == NULL) {
        printf("wzip: cannot open file\n");
        exit(1); 
    }
    
    scanText(file);
    
    fclose(file);
}

int scanText (FILE* text) {

    char oldChar;
    
    if ((oldChar = (char) fgetc(text)) == EOF) {
        return 0;
    }
    
    char newChar;
    int counter = 1;

    while ((newChar = (char) fgetc(text)) != EOF) {

        if(newChar == oldChar) {
            counter++;
            
        } else {
            printEntry(counter, oldChar);
            oldChar = newChar;
            counter = 1; 
        }
    }

    printEntry(counter, oldChar);
    
    puts("");
}

int printEntry (int repetitions, char character) {
    
    int repBin[32];
    
    for (int i = 31; i >= 0; i--) {
        repBin[i] = (repetitions % 2);
        repetitions >>= 1;
    }
    
    for (int i = 0; i < 32; i++) {
        
        printf("%d", *(repBin + i));
        
        if (i % 8 == 7) {
            printf("%s", " ");
        }
    }
    
    int charBin[8];    
    
    for (int i = 7; i >= 0; i--) {
        charBin[i] = (character % 2);
        character >>= 1;
    }
    
    for (int i = 0; i < 8; i++) {
        
        printf("%d", *(charBin + i));
    }
    
    puts("");
    
    return 0;
}