#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 10
#define STAGES 8

// Global training status: ' ' (not done), 'P' (pass), 'F' (fail)
char training_results[STAGES] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Menu labels
const char *main_menu[] = {
    "1. Audition Management",
    "2. Training",
    "3. Debut",
    "Select a menu (0, Q/q to quit): "
};

const char *training_menu[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication",
    "Select a training stage (0, Q/q to go back): "
};

void print_main_menu() {
    printf("\n=== Magrathea System Main Menu ===\n");
    for (int i = 0; i < 3; ++i)
        printf("%s\n", main_menu[i]);
}

void print_training_menu() {
    printf("\n--- Training Menu ---\n");
    for (int i = 0; i < STAGES; ++i) {
        printf("%d. %s [%c]\n", i + 1, training_menu[i], training_results[i]);
    }
    printf("%s", training_menu[STAGES]);
}

int get_input_index(const char *prompt, int max) {
    char input[MAX_INPUT];
