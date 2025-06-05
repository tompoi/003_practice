#define MAX_TRAUMA 10
#define MAX_QUESTIONS 5
#define MAX_RESPONSES 50
#define MAX_NICKNAME 30
#define MAX_TRAUMA_DESC 200
#define MAX_RESPONSE_LEN 100

typedef struct {
    char nickname[MAX_NICKNAME];
    int age;
    char trauma[MAX_TRAUMA_DESC];
} TraumaInfo;

typedef struct {
    int id;
    char content[150];
} CounselingQuestion;

typedef struct {
    char nickname[MAX_NICKNAME];
    char question[150];
    char response[MAX_RESPONSE_LEN];
} CounselingResponse;
TraumaInfo traumaList[MAX_TRAUMA];
int traumaCount = 0;

const CounselingQuestion questionBank[MAX_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

CounselingResponse responseList[MAX_RESPONSES];
int responseCount = 0;
void overcomeTrauma() {
    char choice;
    do {
        printf("\n[II. Training > 2. Self-Management and Teamwork > B. Trauma Management]\n");
        printf("A. Input Trauma Data\n");
        printf("B. Start Counseling Session\n");
        printf("Q. Quit to Main Menu\n");
        printf("Select: ");
        scanf(" %c", &choice);

        switch (toupper(choice)) {
            case 'A':
                inputTraumaData();
                break;
            case 'B':
                startCounselingSession();
                break;
            case 'Q':
                return;
            default:
                printf("Invalid choice.\n");
        }
    } while (1);
}
void inputTraumaData() {
    char nickname[MAX_NICKNAME];
    char trauma[MAX_TRAUMA_DESC];
    int found = 0;

    printf("Enter member nickname: ");
    scanf("%s", nickname);

    for (int i = 0; i < MAX_TRAUMA; i++) {
        found = (strcmp(traumaList[i].nickname, nickname) == 0) ? 1 : found;
        if (found) break;
    }

    found ? ({
        printf("Enter trauma description: ");
        getchar(); // flush
        fgets(trauma, sizeof(trauma), stdin);
        trauma[strcspn(trauma, "\n")] = '\0';

        for (int i = 0; i < MAX_TRAUMA; i++) {
            if (strcmp(traumaList[i].nickname, nickname) == 0) {
                strcpy(traumaList[i].trauma, trauma);
                printf("Trauma recorded.\n");
                break;
            }
        }
    }) : printf("Nickname not found. Please retry.\n");
}
void startCounselingSession() {
    char nickname[MAX_NICKNAME];
    int found = 0;

    printf("\nAvailable members with trauma:\n");
    for (int i = 0; i < traumaCount; i++) {
        if (strlen(traumaList[i].trauma) > 0) {
            printf("- %s\n", traumaList[i].nickname);
        }
    }

    printf("Select nickname: ");
    scanf("%s", nickname);

    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0 && strlen(traumaList[i].trauma) > 0) {
            found = 1;
            for (int q = 0; q < 3; q++) {
                int randIndex = rand() % MAX_QUESTIONS;
                char response[MAX_RESPONSE_LEN];
                do {
                    printf("\nQ%d: %s\nYour answer (max 100 chars): ", q + 1, questionBank[randIndex].content);
                    getchar(); // flush
                    fgets(response, sizeof(response), stdin);
                    response[strcspn(response, "\n")] = '\0';
                } while (strlen(response) == 0 || strlen(response) > 100);

                CounselingResponse resp;
                strcpy(resp.nickname, nickname);
                strcpy(resp.question, questionBank[randIndex].content);
                strcpy(resp.response, response);
                responseList[responseCount++] = resp;
            }
            printf("\nCounseling complete for %s.\n", nickname);
            break;
        }
    }

    if (!found)
        printf("Nickname not found or no trauma recorded.\n");
}
void viewCounselingResults() {
    char nickname[MAX_NICKNAME];
    printf("Enter nickname to view responses: ");
    scanf("%s", nickname);

    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            printf("\nNickname: %s\n", traumaList[i].nickname);
            printf("Trauma: %s\n", traumaList[i].trauma);

            for (int j = 0; j < responseCount; j++) {
                if (strcmp(responseList[j].nickname, nickname) == 0) {
                    printf("Q: %s\nA: %s\n", responseList[j].question, responseList[j].response);
                }
            }
            return;
        }
    }
    printf("Nickname not found.\n");
}
