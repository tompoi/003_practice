#define DAYS 6
#define MAX_ROUTINE 50

const char *days_of_week[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const char *exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},        // Cardio
    {"Push-ups", "Squats", NULL},                  // Full-body Strength
    {"Leg Press", "Leg Curl", NULL},               // Lower-body Strength
    {"Pull-ups", "Chin-ups", NULL},                // Upper-body Strength
    {"Plank", "Crunches", NULL}                    // Core Strength
};

char member_routine[MAX_MEMBERS][DAYS][MAX_ROUTINE]; // [member][day][routine]


void printMilliwaysMembers() {
    printf("\n--- Milliways Members ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, member_names[i], member_nicknames[i]);
    }
}
void setExerciseRoutine() {
    char input[MAX_INPUT];
    int member_index;

    printMilliwaysMembers();
    printf("\nSelect member number (1-%d): ", MAX_MEMBERS);
    fgets(input, sizeof(input), stdin);
    member_index = atoi(input) - 1;

    if (member_index < 0 || member_index >= MAX_MEMBERS) {
        printf("Invalid member.\n");
        return;
    }

    int core_used = 0;
    for (int d = 0; d < DAYS; d++) {
        printf("\n--- %s ---\n", days_of_week[d]);
        printf("Select at least 1 cardio and 1 strength/core exercise.\n");

        printf("Cardio Options:\n");
        for (int i = 0; i < 3; i++) {
            printf("C%d. %s\n", i + 1, exercise_types[0][i]);
        }

        printf("Strength/Core Options:\n");
        for (int cat = 1; cat < 5; cat++) {
            for (int ex = 0; exercise_types[cat][ex] != NULL; ex++) {
                printf("S%d%d. %s\n", cat, ex + 1, exercise_types[cat][ex]);
            }
        }

        printf("Enter cardio exercise (e.g., C1): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        int c_index = input[1] - '1';
        if (toupper(input[0]) != 'C' || c_index < 0 || c_index > 2) {
            printf("Invalid cardio.\n"); d--; continue;
        }
        char routine[MAX_ROUTINE] = "";
        snprintf(routine, sizeof(routine), "%s", exercise_types[0][c_index]);

        printf("Enter strength/core exercise (e.g., S21): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (toupper(input[0]) != 'S' || strlen(input) < 3) {
            printf("Invalid strength.\n"); d--; continue;
        }

        int cat = input[1] - '0'; // 1 to 4 (Strength), 5 = Core
        int ex = input[2] - '1';
        if (cat < 1 || cat > 4 || exercise_types[cat][ex] == NULL) {
            printf("Invalid strength/core.\n"); d--; continue;
        }

        // Core rule: only once per week
        if (cat == 4) {
            if (core_used) {
                printf("Core already used once this week.\n"); d--; continue;
            }
            core_used = 1;
        }

        snprintf(routine + strlen(routine), MAX_ROUTINE - strlen(routine), ", %s", exercise_types[cat][ex]);
        strncpy(member_routine[member_index][d], routine, MAX_ROUTINE);
    }

    printf("Routine set for %s (%s).\n", member_names[member_index], member_nicknames[member_index]);
}
void getExerciseRoutine() {
    char input[MAX_INPUT];
    printf("\nEnter member nickname: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int found = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, member_nicknames[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\n--- Routine for %s (%s) ---\n", member_names[found], member_nicknames[found]);
    for (int d = 0; d < DAYS; d++) {
        printf("%s: %s\n", days_of_week[d], member_routine[found][d]);
    }
}
printf("C. Set Basic Workout Routine\n");
printf("D. View Basic Workout Routine\n");

...

case 'C':
    setExerciseRoutine();
    break;
case 'D':
    getExerciseRoutine();
    break;

