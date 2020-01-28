#include <stdio.h>
#include <stdlib.h>

int zipOneFile (char* fileName);
int scanText (FILE* text);
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
    
    fwrite(&repetitions, 4, 1, stdout);
    fwrite(&character, 1, 1, stdout);

    return 0;
}