#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 100
#define MAX_MEMBERS 5
#define TESTS 7

// Milliways member names and nicknames
const char *member_names[MAX_MEMBERS] = {
    "Zaphod Beeblebrox", "Ford Prefect", "Trillian Astra", "Marvin", "Arthur Dent"
};
const char *member_nicknames[MAX_MEMBERS] = {
    "Zaphod", "Ford", "Trillian", "Marvin", "Arthur"
};

// Fitness test categories
const char *fitness_tests[TESTS] = {
    "1-Mile Running Test", "Speed Sprint", "Push-ups",
    "Squats", "Arm Strength", "Swimming", "Weightlifting"
};

// Health scores: row = member, col 0 = nickname, 1-7 = scores
char health_scores[MAX_MEMBERS][MAX_INPUT];

// --- Helper Functions ---

// Parse comma-separated input into target array
void parse_fitness_data(const char *input, char *target) {
    strncpy(target, input, MAX_INPUT - 1);
    target[MAX_INPUT - 1] = '\0';
}

// --- Fitness Data Functions ---

void setHealth() {
    char input[MAX_INPUT];
    printf("\n-- Enter Fitness Data --\n");

    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Member: %s (%s)\n", member_names[i], member_nicknames[i]);
        printf("Enter data (comma-separated for the 7 tests):\n");
        printf("[1-Mile, Speed, Push-ups, Squats, Arm Strength, Swimming, Weightlifting]\n");
        printf("Input: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        // Store nickname + parsed values
        char formatted[MAX_INPUT] = "";
        snprintf(formatted, sizeof(formatted), "%s,%s", member_nicknames[i], input);
        parse_fitness_data(formatted, health_scores[i]);
    }
    printf("All data saved.\n");
}

void getHealth() {
    char input[MAX_INPUT];
    int option;

    printf("\n-- View Fitness Data --\n");
    printf("1. View all data\n");
    printf("2. View a specific member’s data\n");
    printf("3. View a specific fitness test result for a member\n");
    printf("Select option: ");
    fgets(input, sizeof(input), stdin);
    option = atoi(input);

    if (option == 1) {
        printf("\n%-10s", "Nickname");
        for (int i = 0; i < TESTS; i++)
            printf("| %-20s", fitness_tests[i]);
        printf("\n");

        for (int i = 0; i < MAX_MEMBERS; i++) {
            char *token;
            char data_copy[MAX_INPUT];
            strncpy(data_copy, health_scores[i], MAX_INPUT);
            token = strtok(data_copy, ",");

            int col = 0;
            while (token != NULL) {
                printf("%-20s", token);
                token = strtok(NULL, ",");
                col++;
            }
            printf("\n");
        }

    } else if (option == 2) {
        printf("Enter nickname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(input, member_nicknames[i]) == 0) {
                char *token;
                char data_copy[MAX_INPUT];
                strncpy(data_copy, health_scores[i], MAX_INPUT);
                token = strtok(data_copy, ",");

                printf("Nickname: %s\n", token);
                for (int j = 0; j < TESTS && (token = strtok(NULL, ",")) != NULL; j++) {
                    printf("%s: %s\n", fitness_tests[j], token);
                }
                return;
            }
        }
        printf("Member not found.\n");

    } else if (option == 3) {
        printf("Enter nickname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        int member_index = -1;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(input, member_nicknames[i]) == 0) {
                member_index = i;
                break;
            }
        }
        if (member_index == -1) {
            printf("Member not found.\n");
            return;
        }

        printf("Select test (1-7):\n");
        for (int i = 0; i < TESTS; i++)
            printf("%d. %s\n", i + 1, fitness_tests[i]);

        fgets(input, sizeof(input), stdin);
        int test_index = atoi(input) - 1;

        if (test_index < 0 || test_index >= TESTS) {
            printf("Invalid test.\n");
            return;
        }

        char *token;
        char data_copy[MAX_INPUT];
        strncpy(data_copy, health_scores[member_index], MAX_INPUT);
        token = strtok(data_copy, ","); // nickname

        for (int i = 0; i <= test_index; i++) {
            token = strtok(NULL, ",");
        }

        if (token)
            printf("%s's result in %s: %s\n", member_nicknames[member_index], fitness_tests[test_index], token);
    }
}

// --- Extend Physical Strength & Knowledge ---

void physical_training_menu() {
    char input[MAX_INPUT];
    while (1) {
        printf("\n--- Physical Strength & Knowledge ---\n");
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("Q. Back to Training Menu\n");
        printf("Choice: ");
        fgets(input, sizeof(input), stdin);

        switch (toupper(input[0])) {
            case 'A':
                setHealth();
                break;
            case 'B':
                getHealth();
                break;
            case 'Q':
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}
