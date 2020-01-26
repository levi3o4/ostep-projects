#include <stdio.h>
#include <stdlib.h>

int unzipOneFile (char* fileName);
int scanText (FILE* file);
int printContents (char* repetitions, char* character);
int binaryToDecimal (char* binaryNum, int size);

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

    char repetitions[32];
    char byte[8];
    
    while ((fscanf(text, "%s", byte)) != EOF) {
        
        for(int i = 0; i < 4; i++) {
            
            for (int j = 0; j < 8; j++) {
                
                *(repetitions + (i * 8) + j) = *(byte + j);
                
            }
            
            if ((fscanf(text, "%s", byte)) == EOF) {
                exit(2);
            }
        }
        *(repetitions + 32) = '\0';
        
        printContents(repetitions, byte);
    }
    
    puts("");
}

int printContents (char* repetitions, char* character) {

    char intRepetitions = binaryToDecimal(repetitions, 32);
    char intCharacter = binaryToDecimal(character, 8);
    
    for (int i = 0; i < intRepetitions; i++) {
        printf("%c", intCharacter);
    }
    
    return 0;
}

int binaryToDecimal (char* binaryNum, int size) {

    int numArray[size];

    int decimal = 0;
    
    for (int i = 0; i < size; i++) {
    
        decimal *= 2;
        decimal += (binaryNum[i] % 2);
    }
    
    return decimal;
}
