// Created: 24/09/2020 BY: Cedric P. SIOSANA & DAVE CHRISTIAN R. ROYO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// This function reads a string that's virtually unlimited until '\0' is used
char *dynamic_input() {
    int size = 1;
    char *buffer = (char *)malloc(size * sizeof(char));
    if (!buffer) return NULL;

    char c;
    int index = 0;

    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[index++] = c;
        size++;
        
        char *temp = (char *)realloc(buffer, size * sizeof(char));
        if (!temp) {
            free(buffer);
            return NULL;
        }
        buffer = temp;
    }

    buffer[index] = '\0';
    return buffer;
}

// This function checks if the user has entered an extra character and returns 1 if the input stream is clear and 0 if not
int is_clear_input_stream() {
    char c;
    int result = 1;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c != '\n') {
            result = 0; // If there are still characters in the input stream
        }
    }
    return result;
}

// This function converts an infix expression to postfix
char *infix_to_postfix(char *str) {
    int len = strlen(str);
    char *postfix = (char *)malloc(len + 1);  // Allocate for postfix expression
    if (!postfix) return NULL;

    // Stack (Array-Based) - LOCAL TO FUNCTION
    char stack[len];  
    int top = -1, j = 0;  

    // Function for precedence check
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;  // Right-associative
        return 0;
    }

    // Function to check left associativity
    int is_left_associative(char op) {
        return (op != '^');  // Exponentiation is right-associative
    }

    // Process input expression
    for (int i = 0; i < len; i++) {
        char c = str[i];

        if (isalnum(c)) {  
            postfix[j++] = c;  // Operand goes to postfix directly
        } 
        else if (c == '(') {  
            stack[++top] = c;  // Push '(' onto stack
        } 
        else if (c == ')') {  
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];  
            }
            if (top != -1) top--;  // Pop '('
        } 
        else {  
            while (top != -1 && precedence(stack[top]) >= precedence(c) && is_left_associative(c)) {
                postfix[j++] = stack[top--];  
            }
            stack[++top] = c;  
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[j++] = stack[top--];  
    }

    postfix[j] = '\0';  // Null-terminate the postfix expression
    return postfix;
}

int main() {
    // This is the main menu    
    char choice = 'A';
    while (choice != 'X') {
        printf("Welcome to this Expression Evaluator program! Please choose an action to perform… \n\n[P] Program Description\n[E] Evaluate Expression(s)\n[X] Exit\n\nChoice: ");
        choice = getchar();
        
        if (!is_clear_input_stream()) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        switch (choice) {
            case 'P':
                printf("This program evaluates a given expression. The expression can be a simple arithmetic expression or a complex one. The program will evaluate the expression and display the result.\n\n");
                break;

            case 'E':
                char choice2 = 'A';
                while(1) {

                    //This is for POSTFIX
                    printf("Please enter the expression to evaluate: ");
                    char *str = dynamic_input();
                    if (str) {
                        char *postfix = infix_to_postfix(str);  // Store result separately

                        if (postfix) {
                            printf("Postfix expression: %s\n", postfix);
                            free(postfix);
                        } else {
                            printf("Error: Memory allocation failed.\n");
                        }

                        free(str);  // Free the original infix expression
                    }


                    // This is for EVALUATING the POSTFIX
                    // ================================SPACE FOR DAVE================================  



                    printf("Do you want to evaluate an expression? [Y] Yes [N] No\nChoice: ");
                    choice2 = getchar();
                    if (!is_clear_input_stream() || (choice2 != 'Y' && choice2 != 'N')) {
                        printf("Invalid choice. Please try again.\n");
                        continue;
                    }
                    if(choice2 == 'N') {
                        break;
                    }   
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
