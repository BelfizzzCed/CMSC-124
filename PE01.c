/*
 * Expression Evaluator Program
 * Created: 24/09/2020 BY: Cedric P. SIOSANA & DAVE CHRISTIAN R. ROYO
 * Updated: [Current Date] BY: [Your Name]
 *
 * This program evaluates arithmetic expressions. It supports basic operations like addition, subtraction,
 * multiplication, division, and modulo. The program first converts the infix expression to postfix notation and
 * then evaluates the postfix expression.
 *
 * Allowed symbols for each infix expression:
 * - Numbers: non-negative integers
 * - Operators: subtraction (-), division (/), multiplication (*), addition (+), and modulo (%)
 * - Parentheses: ( and )
 * - Spaces (as delimiters): for separating numbers and other symbols. There is no restriction on the number of spaces.
 *
 * Developer Information:
 * - Cedric P. SIOSANA (Student Number: 2022-09758)
 * - Dave Christian R. ROYO (Student Number: [Insert Student Number])
 *
 * Dates Covered for Program Development:
 * - Initial Development: 24/09/2020
 * - Latest Update: [Current Date]
 *
 * Brief Description of Main Menu Items:
 * - [P] Program Description: Displays information about the program and its developers.
 * - [E] Evaluate Expression(s): Allows the user to input an arithmetic expression, evaluates it, and displays the result.
 * - [X] Exit: Exits the program.
 *
 * Who Did What:
 * - Cedric P. SIOSANA: Implemented the dynamic input function, input stream clearing, and postfix evaluation.
 * - Dave Christian R. ROYO: Implemented the infix-to-postfix conversion and postfix evaluation.
 * - [Your Name]: Updated the program to include the modulo operator, developer information, handle lowercase inputs,
 *                and repeat evaluation processes.
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
 char *infix_to_postfix(char *infix) {
     int len = strlen(infix);
     
     // Allocate extra memory to accommodate added spaces and operators.
     char *postfix = (char *)malloc((2 * len + 1) * sizeof(char));
     if (!postfix) {
         fprintf(stderr, "Memory allocation failed for postfix.\n");
         exit(EXIT_FAILURE);
     }
     
     char stack[len];  // Operator stack
     int top = -1;
     int j = 0;
     
     for (int i = 0; i < len; i++) {
         // Skip any spaces in the infix expression
         if (isspace(infix[i])) {
             continue;
         }
         // If it's a digit, process the full number
         if (isdigit(infix[i])) {
             while (i < len && isdigit(infix[i])) {
                 postfix[j++] = infix[i++];
             }
             postfix[j++] = ' ';
             i--; 
         }
         else if (infix[i] == '(') {
             stack[++top] = infix[i];
         }
         else if (infix[i] == ')') {
             while (top != -1 && stack[top] != '(') {
                 postfix[j++] = stack[top--];
                 postfix[j++] = ' ';
             }
             if (top != -1) top--;  // Pop '('
         }
         else if (infix[i] == '+' || infix[i] == '-' ||
                  infix[i] == '*' || infix[i] == '/' || infix[i] == '%') {
             while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                 postfix[j++] = stack[top--];
                 postfix[j++] = ' ';
             }
             stack[++top] = infix[i];
         }
         // Ignore any invalid characters.
     }
     
     // Pop any remaining operators
     while (top != -1) {
         postfix[j++] = stack[top--];
         postfix[j++] = ' ';
     }
     
     postfix[j] = '\0';
     return postfix;
 }
 
 // Function to evaluate the postfix expression using integer arithmetic
 int evaluate_postfix(char *postfix) {
     int stack[strlen(postfix)];
     int top = -1;
     char *token = strtok(postfix, " ");
     
     while (token != NULL) {
         // If token is a number, push it onto the stack
         if (isdigit(token[0])) {
             stack[++top] = atoi(token);
         } else {
             int b = stack[top--];
             int a = stack[top--];
             switch (token[0]) {
                 case '+': stack[++top] = a + b; break;
                 case '-': stack[++top] = a - b; break;
                 case '*': stack[++top] = a * b; break;
                 case '/': stack[++top] = a / b; break;
                 case '%': stack[++top] = a % b; break;
                 default:
                     // Could add error handling for invalid operators here.
                     break;
             }
         }
         token = strtok(NULL, " ");
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
         
         // Clear the input stream after reading the main menu choice
         if (!is_clear_input_stream()) {
             printf("Invalid choice. Please try again.\n");
             continue;
         }
         
         // Convert choice to uppercase for uniform handling
         choice = toupper(choice);
         
         switch (choice) {
             case 'P':
                 printf("\nProgram Description:\n");
                 printf("This program evaluates arithmetic expressions by converting infix to postfix,\n");
                 printf("and then evaluating the postfix. It supports the operators +, -, *, /, %% (modulo),\n");
                 printf("and parentheses ().\n\n");
                 
                 printf("Developers:\n");
                 printf("- Cedric P. SIOSANA (Student Number: 2022-09758)\n");
                 printf("- Dave Christian R. ROYO (Student Number: [Insert Student Number])\n\n");
                 
                 printf("Dates Covered for Development:\n");
                 printf("- Initial Development: 24/09/2020\n");
                 printf("- Latest Update: [Current Date]\n\n");
                 
                 printf("Who Did What:\n");
                 printf("- Cedric P. SIOSANA: Implemented the dynamic input function, input stream clearing, and postfix evaluation.\n");
                 printf("- Dave Christian R. ROYO: Implemented the infix-to-postfix conversion and postfix evaluation.\n");
                 break;
                 
             case 'E': {
                 char repeat = 'Y';
                 while (repeat == 'Y' || repeat == 'y') {
                     printf("\nPlease enter the expression to evaluate: ");
                     char *infix = dynamic_input();
                     if (infix) {
                         // Convert infix to postfix
                         char *postfix = infix_to_postfix(infix);
                         printf("Postfix expression: %s\n", postfix);
                         
                         // Evaluate the postfix expression
                         int result = evaluate_postfix(postfix);
                         printf("Result: %d\n", result);
                         
                         // Free allocated memory
                         free(infix);
                         free(postfix);
                     }
                     
                     // Ask if the user wants to evaluate another expression
                     printf("\nDo you want to evaluate another expression? (Y/N): ");
                     scanf(" %c", &repeat);
                     while (getchar() != '\n');  // Clear the input buffer
                 }
                 break;
             }
                 
             case 'X':
                 printf("\nThank you for using this program. Goodbye!\n");
                 break;
                 
             default:
                 printf("\nInvalid choice. Please try again.\n");
                 break;
         }
     }
     
     return 0;
 }
 