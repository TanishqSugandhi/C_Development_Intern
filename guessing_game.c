// guessing_game.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret, guess, attempts=0;
    srand((unsigned)time(NULL));
    secret = rand() % 100 + 1; // 1..100
    printf("Guess the number (1-100). Enter 0 to quit.\n");
    while (1) {
        printf("Your guess: ");
        if (scanf("%d", &guess) != 1) break;
        if (guess == 0) { printf("You quit. Secret was %d\n", secret); break; }
        attempts++;
        if (guess == secret) {
            printf("Correct! Attempts: %d\n", attempts);
            break;
        } else if (guess < secret) {
            printf("Too low.\n");
        } else {
            printf("Too high.\n");
        }
    }
    return 0;
}
