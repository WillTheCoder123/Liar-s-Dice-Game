#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICE_FACES 6

void roll(int* hand, int size);
void adjustDiceHand(int** hand, int* size);
void printHand(const char* player, int* hand, int size);
int getTotalDice(int* hand, int size, int value);
void findNumbers(int* hand, int size, int target);
int randNum();

int userDiceAmount = 5, oppDiceAmount = 5;
int userInput;
int count = 0;

int main() {
    srand(time(NULL));

    int* userHand = (int*)malloc(userDiceAmount * sizeof(int)); 
    int* oppHand = (int*)malloc(oppDiceAmount * sizeof(int));

    roll(userHand, userDiceAmount);
    roll(oppHand, oppDiceAmount);

    while (userDiceAmount > 0 && oppDiceAmount > 0) {
        printf("\nGame State:\nOpponent hand size is: %d\nYour hand size is: %d\n", oppDiceAmount, userDiceAmount);
        printHand("Dice you rolled:", userHand, userDiceAmount);

        int amount = randNum(), target = randNum(); 
        printf("\nOpponent Bet: %d %d's\n", amount, target);
        printf("\nMake your play:\n0 - Raise\n1 - Call Bluff\n");
        scanf("%d", &userInput);

        if (userInput == 1) {
            count = 0;
            findNumbers(userHand, userDiceAmount, target);
            findNumbers(oppHand, oppDiceAmount, target);
            printf("\nPlayer chose to call bluff\n");

            if (count < amount) {
                printf("They were %d %d's\nPlayer successfully called the bluff, opponent loses a dice.\n\nNew Round!\n", count, target);
                adjustDiceHand(&oppHand, &oppDiceAmount);
            } 
            else {
                printf("They were %d %d's\nBluff was unsuccessful. Player lose one dice.\n\nNew Round!\n", count, target);
                adjustDiceHand(&userHand, &userDiceAmount);
            }
        } 
        else {
            int a, b;
            printf("\nPlayer chose to raise\n");
            printf("(Format bet: # #) Enter your bet: ");
            scanf("%d %d", &a, &b);

            amount = a;
            target = b;

            if(randNum()%2 == 0){
            printf("\nOpponent chose to raise.\nOppenent makes new bet.\n");
            }
            else {
                count = 0;
                
                printf("\nOpponent calls bluff\n");
                findNumbers(userHand, userDiceAmount, target);
                findNumbers(oppHand, oppDiceAmount, target);

                 if (count < amount) {
                printf("They were %d %d's\nOppenent successfully called the bluff, you lose a dice.\n\nNew Round!\n", count, target);
                adjustDiceHand(&userHand, &userDiceAmount);                
            } 
            else {
                printf("They were %d %d's\nOppenents bluff was unsuccessful. They lose one dice.\n\nNew Round!\n", count, target);
                adjustDiceHand(&oppHand, &oppDiceAmount);
            }


            }
        }
       

        // Re-roll dice for next round
        roll(userHand, userDiceAmount);
        roll(oppHand, oppDiceAmount);
    }

    if (userDiceAmount == 0) {
        printf("Opponent wins! Player has no dice left.\n\n\n");
    } 
    else {
        printf("Player wins! Opponent has no dice left.\n\n\n");
    }

    free(userHand);
    free(oppHand);
    return 0;
}

int getTotalDice(int* hand, int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (hand[i] == value) {
            count++;
        }
    }
    return count;
}

void printHand(const char* player, int* hand, int size) {
    printf("%s dice: ", player);
    for (int i = 0; i < size; i++) {
        printf("%d, ", hand[i]);
    }
    printf("\n");
}

void adjustDiceHand(int** hand, int* size) {
    if (*size > 0) {
        (*size)--;
        *hand = (int*)realloc(*hand, (*size) * sizeof(int));
    }
}

int randNum() {
    return rand() % DICE_FACES + 1;
}

void roll(int* hand, int size) {
    for (int i = 0; i < size; i++) {
        hand[i] = randNum();
    }
}

void findNumbers(int* hand, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (hand[i] == target) {
            count++;
        }
    }
}
