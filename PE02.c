#include <stdio.h>
#include <string.h>

void displayProgramDescription() {
    printf("\n=== Program Description ===\n");
    printf("Developers: Dave Christian R. Royo (2022-10799) and Cedric P. Siosana (2022-)\n");
    printf("Dates: February 1, 2025 - February 10, 2025\n");
    printf("This program allows users to compress or expand strings.\n");
    printf("String Expansion: Converts a compressed string (e.g., 2a3b) into its expanded form (e.g., aabbb).\n");
    printf("String Compression: Converts an expanded string (e.g., aabbb) into its compressed form (e.g., 2a3b).\n");
    printf("Dave Christian Royo: Lead the string Expansion Function, main menu and did error handlings.\n");
    printf("Cedric Siosana: Lead the string Compression Function, Program description function and also did some error handlings.\n");
    printf("Exit: Terminates the program.\n");
    printf("===========================\n");
    printf("Press any key to return to the main menu...\n");
    getchar(); // Wait for user input
    getchar(); // Clear the newline character
}

int isValidExpansionInput(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i]) && !isalpha(input[i])) {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid input
}

// Function to perform string expansion
void stringExpansion() {
    char input[1000];
    printf("\n=== String Expansion ===\n");
    printf("Enter the compressed string (e.g., 2a3b): ");
    scanf("%s", input);

    if (!isValidExpansionInput(input)) {
        printf("Invalid input! The string should only contain digits and letters.\n");
        return;
    }

    printf("Expanded Form: ");
    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) {
            int count = 0;
            while (isdigit(input[i])) {
                count = count * 10 +
            }
            for (int j = 0; j < count; j++) {
                printf("%c", input[i]);
            }
        } else {
            printf("%c", input[i]);
        }
    }
    printf("\n");

// Function to validate the input string for compression
int isValidCompressionInput(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isalpha(input[i])) {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid input
}

void stringCompresssion(){
    chat input[1000];
    printf("===String Compression===\n");
    printf("Enter the expanded string (e.g, aabbb): ");
    scanf("%s", input);

    if (!isValidCompressionInput(input)) {
        printf("Invalid input! The string should ony contain letters.\n");
        return;
    }

    printf("Commpressed Form: ");
    for (int i = 0; )
    // continuation to be done tommrorw ayaw q na

}

// Main Function
int main() {
    char choice;
    do {
        printf("\n===Main Menu ===\n");
        printf("Welcome to this String Expansion/Compression program!\n");
        printf("[P] Program Description\n");
        printf("[E] String Expansion\n");
        printf("[C] String Compression\n");
        printf("[X] Exit\n");
        printf("Choice: ");
        scanf(" %c", choice);
        choice = toupper(choice);

        switch (choice) {
            case 'P':
                displayProgramDescription();
                break;
            case 'E':
                stringExpansion();
                break;
            case 'X':
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("invalid choice! Please try again.\n");
                
        }
    } while (choice !='X');

    return 0;
}






