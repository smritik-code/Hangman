#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Function prototypes
void playGame();
void drawHangman(int);
void drawWord(char[], char[]);
int checkGuess(char[], char[], char, int);
void printHint(char[]);
void printWelcomeMessage();
void displayVictoryMessage();
void displayLosingMessage();
int playAgain();
void loadWords(char *filename, char *words[], char *hints[], int *numWords);
int readHighScore();
void updateHighScore(int score);


// Global variable for score
#define MAX_ATTEMPTS 4
int highestScore;
int i;
int score = 0;

// Main function
int main() {
   printf("                   WELCOME TO HANGMAN           \n");

    printf("\n\n\n1. Start a New Game\n");
    printf("2. Check High Score\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Start a new game
            printf("\nStarting a new game...\n");
            playGame();
            break;
        case 2:
            // Check high score
             printf("\nHigh Score: %d\n", readHighScore());
            break;
        default:
            printf("\nInvalid choice. Please select either 1 or 2.\n");
            break;
    }
    return 0;
}

void playGame(){
 // Array of 5-letter words, each with its associated hint
    char *words[100];
    char *hints[100];
    int numWords;

   // Load words and hints from file
   loadWords("words.txt", words, hints, &numWords);

    srand(time(NULL)); // Seed the random number generator

    int randomIndex = rand() % numWords;

    char word[20];
    strcpy(word, words[randomIndex]);

    char guessedWord[20];
    int len = strlen(word);
    for (i = 0; i < len; i++)
        guessedWord[i] = '_';
    guessedWord[len] = '\0';

    char guessedLetters[26];
    int attempts = MAX_ATTEMPTS;
    int numGuessed = 0;


    // Initialize guessed letters array
    for (i = 0; i < 26; i++)
        guessedLetters[i] = 0;

        printWelcomeMessage();

    // Display hint
    printHint(hints[randomIndex]);

    // Game loop
    while (attempts > 0 && numGuessed < len) {

        // Draw hangman
        drawHangman(attempts);

        // Draw word
        drawWord(word, guessedWord);

        // Print guessed letters
        printf("\nGuessed letters: ");
        for (i = 0; i < 26; i++) {
            if (guessedLetters[i] != 0)
                printf("%c ", guessedLetters[i]);
        }

        // Input guess
        printf("\nEnter a letter: ");
        char guess;
        scanf(" %c", &guess);

        // Check if input is a valid letter
        if (!isalpha(guess)) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        // Check if the guess is correct

            if (checkGuess(word, guessedWord, guess, len)) {
                numGuessed++;
                score += 10;
                printf("Good guess!\n");
            } else {
                attempts--;
                score -= 5;
                printf("Incorrect guess!\n");
            }


        // Update guessed letters array
        guessedLetters[tolower(guess) - 'a'] = tolower(guess);    }
         highestScore= readHighScore();

    // Calculate score
    if (numGuessed == len) {
        displayVictoryMessage();
        printf("The word is: %s\n", word);
        printf("Your score: %d\n", score);
        highestScore= readHighScore();
        if (score > highestScore) {
            highestScore = score;
            printf("Congratulations! You've achieved a new highest score!\n");
            updateHighScore(highestScore);}
    } else {
        displayLosingMessage();
        drawHangman(attempts);
        printf("The word was: %s\n", word);
        printf("Your score: %d\n", score);
    }

       printf("Highest Score: %d\n", highestScore);

    // Play again
    if (playAgain()) {
        playGame();
    }

}

// Function to draw hangman based on attempts left
void drawHangman(int attempts) {
    switch (attempts) {
        case 0:
            printf("  _______\n");
            printf(" |/     |\n");
            printf(" |     (_) \n");
            printf(" |     \\|/\n");
            printf(" |      |\n");
            printf(" |     / \\\n");
            printf("_|_\n");
            break;
        case 1:
            printf("  _______\n");
            printf(" |/     |\n");
            printf(" |     (_) \n");
            printf(" |     \\|/\n");
            printf(" |      |\n");
            printf(" |       \n");
            printf("_|_\n");
            break;
        case 2:
            printf("  _______\n");
            printf(" |/     |\n");
            printf(" |     (_) \n");
            printf(" |     \\|/\n");
            printf(" |       \n");
            printf(" |\n");
            printf("_|_\n");
            break;
        case 3:
            printf("  _______\n");
            printf(" |/     |\n");
            printf(" |     (_) \n");
            printf(" |      | \n");
            printf(" |        \n");
            printf(" |\n");
            printf("_|_\n");
            break;
        case 4:
            printf("  _______\n");
            printf(" |/     |\n");
            printf(" |       \n");
            printf(" |        \n");
            printf(" |        \n");
            printf(" |\n");
            printf("_|_\n");
            break;
    }
}


// Function to draw the word with underscores for missing letters
void drawWord(char word[], char guessedWord[]) {
    printf("\n\n");
    for (i = 0; i < strlen(word); i++) {
        printf("%c ", guessedWord[i]);
    }
    printf("\n\n");
}

// Function to check if the guessed letter is correct
int checkGuess(char word[], char guessedWord[], char guess, int len) {
    int found = 0;
    for (i = 0; i < len; i++) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
            found = 1;
        }
    }
    return found;
}

void printWelcomeMessage() {
    printf("Try to guess the word by entering one letter at a time.\n");
    printf("You have %d attempts. Good luck!\n", MAX_ATTEMPTS);
}

// Function to print hint for the word
void printHint(char hint[]) {
    printf("\nHint: %s\n", hint);
}

// Function to display victory message
void displayVictoryMessage() {
    printf("\nCongratulations! You guessed the word!\n");
}

// Function to display losing message
void displayLosingMessage() {
    printf("\nGame over! You failed to guess the word.\n");
}

// Function to ask if player wants to play again
int playAgain() {
    highestScore= readHighScore();
    char choice;
    printf("\nDo you want to play again? (Y/N): ");
    scanf(" %c", &choice);
    if (tolower(choice) == 'y') {
        system("cls");
        return 1;
    } else {
         int currentScore= score;
        if (currentScore > highestScore) {
            highestScore = currentScore;
            updateHighScore(highestScore);
        }
        return 0;
    }
}


// Function to load words and hints from file
void loadWords(char *filename, char *words[], char *hints[], int *numWords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    *numWords = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Split line into word and hint
        char *token = strtok(line, ",");
        words[*numWords] = strdup(token);
        token = strtok(NULL, ",");
        hints[*numWords] = strdup(token);

        (*numWords)++;
    }

    fclose(file);
}


// Function to read the high score from the file
int readHighScore() {
    FILE *file = fopen("highscore.txt", "r");
    if (file == NULL) {
        printf("Error opening high score file.\n");
        return 0;
    }
    int highScore;
    fscanf(file, "%d", &highScore);
    fclose(file);
    return highScore;
}

// Function to update the high score in the file
void updateHighScore(int score) {
    FILE *file = fopen("highscore.txt", "w");
    if (file == NULL) {
        printf("Error opening high score file for writing.\n");
        return;
    }
    fprintf(file, "%d", score);
    fclose(file);
}
