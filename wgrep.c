#include <stdio.h>
#include <stdlib.h>

int getLength (char* string);
int grepOneFile (char* searchTerm, size_t searchTermLength, char* fileName);
int traverseText (char* searchTerm, size_t searchTermLength, FILE* file);
int search (char* searchTerm, size_t searchTermLength, char* line);
int compare (char* searchTerm, char* line, size_t offset);

int main (int argc, char *argv[]) {
    
    if (argc == 1) {
        
        puts("wgrep: searchterm [file ...]");
        exit(1);
        
    } else {
        
        size_t searchTermLength = getLength(argv[1]);
        
        if (argc == 2) {
            
            puts("Please enter some text to search through.");
            traverseText(argv[1], searchTermLength, stdin);
            
        } else {
            
            for (int i = 2; i < argc; i++) {
                
                grepOneFile(argv[1], searchTermLength, argv[i]);
            }
        }
    }
    
    return 0;
}

int getLength (char* string) {
    
    size_t length = 0;
    
    for (; *(string + length) != '\0'; length++) {
        ;
    }
    
    return length;
}

int grepOneFile (char* searchTerm, size_t searchTermLength, char* fileName) {

    FILE *file = fopen(fileName, "r"); 
    
    if (file == NULL) {
        printf("wcat: cannot open file\n");
        exit(1); 
    }
    
    traverseText(searchTerm, searchTermLength, file);
    
    fclose(file);
}

int traverseText (char* searchTerm, size_t searchTermLength, FILE* text) {
    
    char* line = NULL;
    size_t length = 0;
    
    while (getline(&line, &length, text) != -1) {
        
        if (search(searchTerm, searchTermLength, line)) {
            printf("%s", line);
        }
    }
    
    puts("");
    
    free(line);
}

int search (char* searchTerm, size_t searchTermLength, char* line) {
    
    size_t lineLength = getLength(line);
    
    for (size_t offset = 0; searchTermLength + offset <= lineLength; offset++) {
        
        if (compare(searchTerm, line, offset)) {
            return 1;
        }
    }
    
    return 0;
}

int compare (char* searchTerm, char* line, size_t offset) {
    
    for (int i = 0; *(searchTerm + i) != '\0'; i++) {
       
        if (*(searchTerm + i) != *(line + offset + i)) {
            return 0;
        }
    }
    
    return 1;
}