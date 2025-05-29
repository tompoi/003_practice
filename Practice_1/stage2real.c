#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 8
#define MAX_NAME_LEN 50
#define MAX_MENTORS 8

typedef struct {
    char name[MAX_NAME_LEN];
    int asciiSum;
    int ability;
} Trainee;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int menteeIndex;  // index of the trainee
} Mentor;

Trainee trainees[MAX_TRAINEES];
Mentor mentors[MAX_MENTORS];
int traineeCount = 0;
int mentorCount = 0;
int matched[MAX_MENTORS] = {0};  // flag for bonus 1:1 match

// Convert name to ASCII sum
int parseIntMember(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += (int)name[i];
    }
    return sum;
}

// Generate random ability value [100-1000]
int getRandomAbility() {
    return (rand() % 901) + 100;
}

// Initialize trainees
void initTrainees() {
    char *names[MAX_TRAINEES] = {
        "Nova", "Quark", "Zeta", "Lyra", "Orion", "Vega", "Sirius", "Altair"
    };
    for (int i = 0; i < MAX_TRAINEES; i++) {
        strncpy(trainees[i].name, names[i], MAX_NAME_LEN);
        trainees[i].asciiSum = parseIntMember(trainees[i].name);
        trainees[i].ability = getRandomAbility();
    }
    traineeCount = MAX_TRAINEES;
}

// Input mentor data
void inputMentors() {
    printf("Enter up to 8 mentors:\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        printf("Mentor #%d Name: ", mentors[i].id);
        fgets(mentors[i].name, MAX_NAME_LEN, stdin);
        mentors[i].name[strcspn(mentors[i].name, "\n")] = '\0'; // remove newline
        mentors[i].menteeIndex = -1;
    }
    mentorCount = MAX_MENTORS;
}

// Matching logic (bonus: ensure 1:1)
void matchMentoring() {
    for (int i = 0; i < traineeCount; i++) {
        int mentorIndex = i % MAX_MENTORS;

        // ensure each mentor only has one mentee
        while (matched[mentorIndex]) {
            mentorIndex = (mentorIndex + 1) % MAX_MENTORS;
        }

        mentors[mentorIndex].menteeIndex = i;
        matched[mentorIndex] = 1;
    }

    printf("\n=== Mentoring Match Results ===\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        if (mentors[i].menteeIndex != -1) {
            printf("Trainee #%d (%s) -> Mentor ID %d: %s\n",
                   mentors[i].menteeIndex + 1,
                   trainees[mentors[i].menteeIndex].name,
                   mentors[i].id,
                   mentors[i].name);
        }
    }
}

// Debug: print trainee info
void printTrainees() {
    printf("\n=== Trainee Info ===\n");
    for (int i = 0; i < traineeCount; i++) {
        printf("Trainee #%d: Name = %s, ASCII Sum = %d, Ability = %d\n",
               i + 1, trainees[i].name, trainees[i].asciiSum, trainees[i].ability);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    initTrainees();
    printTrainees();
    inputMentors();
    matchMentoring();

    return 0;
}
