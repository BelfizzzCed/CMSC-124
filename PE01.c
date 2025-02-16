/*
 * Expression Evaluator Program
 * Created: 24/09/2020 BY: Cedric P. SIOSANA & DAVE CHRISTIAN R. ROYO
 *
 * This program evaluates arithmetic expressions. It supports basic operations like addition, subtraction,
 * multiplication, division, and modulo. The program first converts the infix expression to postfix notation and
 * then evaluates the postfix expression.
 *
 * Allowed symbols for each infix expression:
 * - Numbers: non-negative integers
 * - Operators: subtraction (-), division (/), multiplication (*), addition (+), and modulo (%)
 * - Parentheses: ( and )
 * - Spaces (as delimiters): for separating numbers and other symbols. There is no restriction on the number
 *   of spaces – an expression without spaces is still valid.
 *
 * Developer Information:
 * - Cedric P. SIOSANA (Student Number: 2022-09758)
 * - Dave Christian R. ROYO (Student Number: 2022-10799)
 *
 * Dates Covered for Program Development:
 * - Initial Development: Feb 9, 2025
 * - Latest Update: Feb 13, 2025
 *
 * Brief Description of Main Menu Items:
 * - [P] Program Description: Displays information about the program, including developer details, dates,
 *   description of menu items, and roles.
 * - [E] Evaluate Expression(s): Prompts the user for an infix expression, converts it to postfix, evaluates it,
 *   and displays the infix expression, the corresponding postfix expression, and the result.
 * - [X] Exit: Terminates the program.
 *
 * Who Did What:
 * - Cedric P. SIOSANA: Implemented dynamic input, input stream clearing, and postfix evaluation.
 * - Dave Christian R. ROYO: Implemented infix-to-postfix conversion and postfix evaluation too.
 *
 * Note: For each invalid infix expression, the program prints "Invalid infix expression."
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <string.h>
 
 // Function to dynamically read input from the user
 char *dynamic_input() {
     int size = 1;
     char *buffer = (char *)malloc(size * sizeof(char));
     if (!buffer) return NULL;
     
     char c;
     int index = 0;
     
     while ((c = getchar()) != '\n' && c != EOF) {
         buffer[index++] = c;
         size++;
         buffer = (char *)realloc(buffer, size * sizeof(char));
         if (!buffer) return NULL;
     }
     
     buffer[index] = '\0';
     return buffer;
 }
 
 // Function to check if the input stream is clear
 int is_clear_input_stream() {
     char c;
     int result = 1;
     while ((c = getchar()) != '\n' && c != EOF) {
         if (c != '\n') {
             result = 0; // Extra characters detected
         }
     }
     return result;
 }
 
 // Function to return the precedence of operators
 int precedence(char op) {
     switch (op) {
         case '+':
         case '-':
             return 1;
         case '*':
         case '/':
         case '%':
             return 2;
         default:
             return 0;
     }
 }
 
 // Function to convert infix expression to postfix notation
 // Returns a dynamically allocated string containing the postfix expression,
 // or NULL if an invalid character or mismatched parentheses are encountered.
 char *infix_to_postfix(char *infix) {
     int len = strlen(infix);
     // Allocate extra memory to accommodate additional spaces and operators.
     char *postfix = (char *)malloc((2 * len + 1) * sizeof(char));
     if (!postfix) {
         fprintf(stderr, "Memory allocation failed for postfix.\n");
         exit(EXIT_FAILURE);
     }
     
     char stack[len];  // Operator stack
     int top = -1;
     int j = 0;
     
     for (int i = 0; i < len; i++) {
         // Skip spaces in the infix expression
         if (isspace(infix[i])) {
             continue;
         }
         // If it's a digit, process the full number
         if (isdigit(infix[i])) {
             while (i < len && isdigit(infix[i])) {
                 postfix[j++] = infix[i++];
             }
             postfix[j++] = ' ';
             i--; // Adjust for the outer loop increment
         }
         else if (infix[i] == '(') {
             stack[++top] = infix[i];
         }
         else if (infix[i] == ')') {
             while (top != -1 && stack[top] != '(') {
                 postfix[j++] = stack[top--];
                 postfix[j++] = ' ';
             }
             if (top == -1) {  // No matching '(' found
                 free(postfix);
                 return NULL;
             }
             top--;  // Pop the '('
         }
         else if (infix[i] == '+' || infix[i] == '-' ||
                  infix[i] == '*' || infix[i] == '/' || infix[i] == '%') {
             while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                 postfix[j++] = stack[top--];
                 postfix[j++] = ' ';
             }
             stack[++top] = infix[i];
         }
         else {
             // Invalid character encountered
             free(postfix);
             return NULL;
         }
     }
     
     // Pop any remaining operators from the stack
     while (top != -1) {
         if (stack[top] == '(' || stack[top] == ')') {
             // Mismatched parentheses found
             free(postfix);
             return NULL;
         }
         postfix[j++] = stack[top--];
         postfix[j++] = ' ';
     }
     
     postfix[j] = '\0';
     return postfix;
 }
 
 // Function to evaluate the postfix expression using integer arithmetic.
 // It returns the evaluated result and sets *error to 1 if an error occurs.
 int evaluate_postfix(char *postfix, int *error) {
     int len = strlen(postfix);
     int stack[len];
     int top = -1;
     *error = 0;
     
     // strtok modifies the string, so tokenizing a copy is recommended.
     char *token = strtok(postfix, " ");
     while (token != NULL) {
         if (isdigit(token[0])) {
             stack[++top] = atoi(token);
         } else {
             // Ensure there are at least two operands available.
             if (top < 1) {
                 *error = 1;
                 return 0;
             }
             int b = stack[top--];
             int a = stack[top--];
             switch(token[0]) {
                 case '+': stack[++top] = a + b; break;
                 case '-': stack[++top] = a - b; break;
                 case '*': stack[++top] = a * b; break;
                 case '/':
                     if (b == 0) { *error = 1; return 0; }
                     stack[++top] = a / b;
                     break;
                 case '%':
                     if (b == 0) { *error = 1; return 0; }
                     stack[++top] = a % b;
                     break;
                 default:
                     *error = 1;
                     return 0;
             }
         }
         token = strtok(NULL, " ");
     }
     
     // If the stack does not contain exactly one element, the expression is invalid.
     if (top != 0) {
         *error = 1;
         return 0;
     }
     
     return stack[top];
 }
 
 int main() {
     char choice = 'A';
     
     while (choice != 'X' && choice != 'x') {
         printf("Welcome to this Expression Evaluator program! Please choose an action to perform… \n\n"
                "[P] Program Description\n"
                "[E] Evaluate Expression(s)\n"
                "[X] Exit\n\n"
                "Choice: ");
         choice = getchar();
         
         // Clear any extra characters from the input buffer.
         if (!is_clear_input_stream()) {
             printf("Invalid choice. Please try again.\n");
             choice = 'A';
             continue;
         }
         
         choice = toupper(choice);
         
         if (choice == 'P') {
             // Display program description.
             printf("\nProgram Description:\n");
             printf("This program evaluates arithmetic expressions by converting infix to postfix\n"
                    "and then evaluating the postfix expression.\n\n");
             printf("Allowed infix expression symbols:\n");
             printf("  - Numbers: non-negative integers\n");
             printf("  - Operators: +, -, *, /, %% (modulo)\n");
             printf("  - Parentheses: ( and )\n");
             printf("  - Spaces: as delimiters (an expression without spaces is still valid)\n\n");
             
             printf("Developers:\n");
             printf("  - Cedric P. SIOSANA (Student Number: 2022-09758)\n");
             printf("  - Dave Christian R. ROYO (Student Number: 2022-10799)\n\n");
             
             printf("Dates Covered for Development:\n");
             printf("  - Initial Development: Feb. 9, 2025\n");
             printf("  - Latest Update: Feb. 13, 2025\n\n");
             
             printf("Menu Options:\n");
             printf("  - [P] Program Description: Displays this information.\n");
             printf("  - [E] Evaluate Expression(s): Input an infix expression and display its corresponding\n"
                    "       postfix expression and evaluated result.\n");
             printf("  - [X] Exit: Terminates the program.\n\n");
             
             printf("Who Did What:\n");
             printf("  - Cedric P. SIOSANA: Implemented dynamic input, input stream clearing, and postfix evaluation.\n");
             printf("  - Dave Christian R. ROYO: Implemented infix-to-postfix conversion and postfix evaluation.\n");
            
             printf("\nPress Enter to return to the main menu...");
             while(getchar() != '\n');  // Wait for Enter key.
         }
         else if (choice == 'E') {
             char repeat = 'Y';
             while (repeat == 'Y' || repeat == 'y') {
                 printf("\nPlease enter the infix expression to evaluate: ");
                 char *infix = dynamic_input();
                 if (infix == NULL || strlen(infix) == 0) {
                     printf("Invalid infix expression.\n");
                     free(infix);
                 } else {
                     // Display the entered infix expression.
                     printf("\nInfix expression: %s\n", infix);
                     
                     // Convert infix to postfix.
                     char *postfix = infix_to_postfix(infix);
                     if (postfix == NULL) {
                         printf("Invalid infix expression.\n");
                         free(infix);
                     } else {
                         printf("Postfix expression: %s\n", postfix);
                         
                         // Create a copy of postfix since strtok will modify it.
                         char *postfix_copy = strdup(postfix);
                         int error = 0;
                         int result = evaluate_postfix(postfix_copy, &error);
                         free(postfix_copy);
                         
                         if (error) {
                             printf("Invalid infix expression.\n");
                         } else {
                             printf("Result: %d\n", result);
                         }
                         
                         free(postfix);
                         free(infix);
                     }
                 }
                 
                 // Ask the user if they want to evaluate another expression.
                 printf("\nDo you want to evaluate another expression? (Y/N): ");
                 scanf(" %c", &repeat);
                 while (getchar() != '\n');  // Clear input buffer.
             }
         }
         else if (choice == 'X') {
             printf("\nThank you for using this program. Goodbye!\n");
         }
         else {
             printf("\nInvalid choice. Please try again.\n");
         }
     }
     
     return 0;
 }
 