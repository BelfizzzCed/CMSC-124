#include <stdio.h>
#include <stdlib.h>

char *dynamic_input(){
    int size = 1;
    char *buffer = (char *)malloc(size * sizeof(char));
    if(!buffer) return NULL;
    
    char c;
    int index = 0;
    
    while((c = getchar()) != '\n'){
        buffer[index++] = c;
        size++;
        
        buffer = (char *)realloc(buffer, size * sizeof(char));
        if(!buffer) return NULL;
    }
    
    buffer[index] = '\n';
    return buffer;
}

int main(){
    
    printf("Hello, please enter your string: ");
    char *str = dynamic_input();
    if(str){
        printf("Your string is: %s", str);
        free(str);
    }
    
    return 0;    
}

