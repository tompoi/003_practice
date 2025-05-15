#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CANDIDATES 6
#define NUM_CATEGORIES 5
#define SHEET_SIZE 7
#define MAX_JUDGES 10

char *candidate_names[NUM_CANDIDATES] = {
    "Jiyeon Park",
    "Ethan Smith",
    "Helena Silva",
    "Liam Wilson",
    "Mina Choi",
    "Carlos Reyes"
};

int candidate_ids[NUM_CANDIDATES];
int scores[MAX_JUDGES][NUM_CANDIDATES][SHEET_SIZE];
int judge_count = 0;

// Generate unique 6-digit IDs
void generate_ids() {
    srand(time(NULL));
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int unique;
        do {
            unique = 1;
            candidate_ids[i] = 100000 + rand() % 900000;
            for (int j = 0; j < i; j++) {
                if (candidate_ids[i] == candidate_ids[j]) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
    }
}

// Prompt for a valid score between 10 and 100
int get_valid_score() {
    int score;
    while (1) {
        scanf("%d", &score);
        if (score >= 10 && score <= 100)
            return score;
        printf("Invalid input. Please enter a value between 10 and 100: ");
    }
}

// Input scores from one judge
void input_scores(int judge_index) {
    char judge_name[50];
    char expertise[30];
    printf("####################################\n");
    printf("#     Audition Evaluation Entry    #\n");
    printf("####################################\n");
    printf("> Judge Name: ");
    scanf(" %[^\n]", judge_name);
    printf("> Expertise: ");
    scanf(" %[^\n]", expertise);

    printf("++++++++++++++++++++++
