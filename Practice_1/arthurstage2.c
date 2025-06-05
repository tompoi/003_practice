typedef struct {
    char keyword[10];  // "specter"
    char message[400]; // Confession message
} ArthurEasterEgg;

ArthurEasterEgg arthurEgg = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};
void printReversedBinary(const char *str) {
    int len = strlen(str);
    unsigned char binaries[7][9]; // 7 letters, 8 bits + null terminator

    for (int i = 0; i < len; i++) {
        unsigned char c = str[i];
        for (int j = 7; j >= 0; j--) {
            binaries[i][7 - j] = (c & (1 << j)) ? '1' : '0';
        }
        binaries[i][8] = '\0';
    }

    // Print in reverse order
    for (int i = len - 1; i >= 0; i--) {
        printf("Binary %d: %s\n", len - i, binaries[i]);
    }
}
int isRightChar(const char *expected, const char *input) {
    return strcmp(expected, input) == 0;
}

int isEasterEgg(const char *input) {
    return strcmp(input, arthurEgg.keyword) == 0;
}
void find_easter_egg() {
    printf("<<Arthur's Easter Egg>>\n");

    // Step 1: Binary and Reversed
    printReversedBinary(arthurEgg.keyword);

    char inputs[7];
    printf("\nEnter the 7 characters corresponding to the reversed binary order:\n");
    for (int i = 0; i < 7; i++) {
        printf("Character %d: ", i + 1);
        scanf(" %c", &inputs[i]);
    }

    inputs[7] = '\0';

    if (isRightChar(arthurEgg.keyword, inputs)) {
        char keywordGuess[10];
        printf("\nCorrect! Now combine and enter the full word: ");
        scanf("%s", keywordGuess);

        if (isEasterEgg(keywordGuess)) {
            printf("\n##Easter Egg Discovered!$$\n%s\n", arthurEgg.message);
        } else {
            printf("Incorrect word. Returning to menu...\n");
        }
    } else {
        printf("Incorrect characters. Please try again.\n");
    }
}
void selfManagementAndTeamworkMenu() {
    char input[20];
    printf("\n[2. Self-Management and Teamwork]\n");
    printf("Enter choice (or type 'Arthur'): ");
    scanf("%s", input);

    if (strcmp(input, "Arthur") == 0) {
        find_easter_egg();
    } else {
        // handle normal submenu logic
    }
}
void shuffleAndConvertKeyword() {
    char word[] = "specter";
    int len = strlen(word);

    // Shuffle (simple swap shuffle)
    for (int i = 0; i < len; i++) {
        int j = rand() % len;
        char temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }

    printf("Shuffled Keyword: %s\n", word);

    printf("8-bit Binary (Reversed):\n");
    for (int i = len - 1; i >= 0; i--) {
        unsigned char c = word[i];
        for (int j = 7; j >= 0; j--) {
            printf("%c", (c & (1 << j)) ? '1' : '0');
        }
        printf("\n");
    }

    printf("Rearranged Order:\nOdd-indexed: ");
    for (int i = 1; i < len; i += 2) printf("%c", word[i]);
    printf("\nEven-indexed: ");
    for (int i = 0; i < len; i += 2) printf("%c", word[i]);
    printf("\n");
}
