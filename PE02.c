#include <stdio.h>
#include <string.h>

void displayProgramDescription() {
    printf("\n=== Program Description ===\n");
    printf("Developers: Dave Christian R. Royo (2022-10799) and Cedric P. Siosana (2022-)\n");
    printf("Dates: October 1, 2023 - October 5, 2023\n");
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

int isValidExpansionInput(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i]) && !isalpha(input[i])) {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid input
}

/ Function to perform string expansion
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

// Function to validate the input string for compression
int isValidCompressionInput(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isalpha(input[i])) {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid input
}






