#include <stdio.h>
#include <stdlib.h>

int catOneFile (char* fileName);
int traverseText (FILE* file);

int main (int argc, char *argv[]) {
    
    for (int i = 1; i < argc; i++) {
        
        catOneFile(argv[i]);
    }
    
    return 0;
}

int catOneFile (char* fileName) {

    FILE *file = fopen(fileName, "r"); 
    
    if (file == NULL) {
        printf("cannot open file\n");
        exit(1); 
    }
    
    traverseText(file);
    
    fclose(file);
}

int traverseText (FILE* text) {
    
    char* line = NULL;
    size_t length = 0;
    
    while (getline(&line, &length, text) != -1) {
        printf("%s", line);
    }
    
    free(line);
}