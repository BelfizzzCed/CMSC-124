// Created: 24/09/2020 BY: Cedric P. SIOSANA & DAVE CHRISTIAN R. ROYO

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
    
    buffer[index] = '\0';
    return buffer;
}

int is_clear_input_stream(){
    char c;
    int result = 1;
    while((c = getchar()) != '\n' && c != EOF){
        if(c != '\n'){
            result = 0; //If there are still characters in the input stream
        }
    };
    return result;
}

int main(){
    
    /*
    THIS IS REFERENCE FOR USING THE INPUT FUNCTION
    printf("Hello, please enter your string: ");
    char *str = dynamic_input();
    if(str){
        printf("Your string is: %s", str);
        free(str);
    }
    */

    //This is the main menu    
    char choice = 'A';
    while(choice != 'X'){
        printf("Welcome to this Expression Evaluator program! Please choose an action to perform… \n\n[P] Program Description\n[E] Evaluate Expression(s)\n[X] Exit\n\nChoice: ");
        choice = getchar();
        
        if(!is_clear_input_stream()){
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        switch(choice){
            case 'P':



                printf("This program evaluates a given expression. The expression can be a simple arithmetic expression or a complex one. The program will evaluate the expression and display the result.\n\n");
                break;



            case 'E':



                printf("Please enter the expression to evaluate: ");
                char *str = dynamic_input();
                if(str){
                    printf("Your expression is: %s\n", str);
                    free(str);
                }
                break;



            case 'X':



                printf("Thank you for using this program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;


                
        }
    }


    return 0;    
}

