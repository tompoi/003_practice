#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_LEN 512

// Function to trim leading/trailing spaces
void trim(char *str) {
    int i;
    // Trim leading
    while (*str == ' ') {
        memmove(str, str + 1, strlen(str));
    }

    // Trim trailing
    for (i = strlen(str) - 1; i >= 0 && str[i] == ' '; i--) {
        str[i] = '\0';
    }
}

// Function to parse and print judge info
void display_judge_data(char *json_data, int index) {
    char *tokens[7];
    int i = 0;
    char *token = strtok(json_data, ",");

    while (token != NULL && i < 7) {
        trim(token);
        tokens[i++] = token;
        token = strtok(NULL, ",");
    }

    if (i != 7) {
        printf("Judge %d has incorrect data format.\n", index + 1);
        return;
    }

    printf("[Judge %d]\n", index + 1);
    printf("Name: %s\n", tokens[0]);
    printf("Gender: %s\n", tokens[1]);
    printf("Affiliation: %s\n", tokens[2]);
    printf("Title: %s\n", tokens[3]);
    printf("Expertise: %s\n", tokens[4]);
    printf("Email: %s\n", tokens[5]);
    printf("Phone: %s\n", tokens[6]);
    printf("-----------------------------------\n");
}

int main(void) {
    char judges_array[MAX_JUDGES][MAX_LEN];
    int total_judges;
    int selected_members;
    char project[MAX_LEN];
    int i = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project, MAX_LEN, stdin);
    project[strcspn(project, "\n")] = '\0';  // Remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar();  // Clear newline

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar();  // Clear newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (i < total_judges) {
        printf("Judge %d (enter 7 fields separated by commas):\n", i + 1);
        fgets(judges_array[i], MAX_LEN, stdin);

        // Make a copy to check field count
        char temp[MAX_LEN];
        strcpy(temp, judges_array[i]);

        int count = 1;
        for (int j = 0; temp[j] != '\0'; j++) {
            if (temp[j] == ',') {
                count++;
            }
        }

        if (count != 7) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        i++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    printf("\"%s\" Should we check the judge information? (Y/N): ", project);
    char confirm;
    scanf(" %c", &confirm);

    if (confirm == 'Y') {
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (i = 0; i < total_judges; i++) {
            char json_copy[MAX_LEN];
            strcpy(json_copy, judges_array[i]);  // Make a modifiable copy
            display_judge_data(json_copy, i);
        }
    } else {
        printf("Program terminated. Goodbye.\n");
    }

    return 0;
}
