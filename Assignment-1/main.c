//Name: Haris Hanif
//Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIDES 6
char* output[8][8];


int rollDie() //Copied from Professor Long
{
    return rand() % SIDES + 1;
}
int main(int argc, const char * argv[]) {
    int balance = 1000;
    int bet;
    srand(time(0));
    output[1][1] = "Snake Eyes";
    output[1][2] = "Ace Deuce";
    output[1][3] = "Easy Four";
    output[1][4] = "Fever Five";
    output[1][5] = "Easy Six";
    output[1][6] = "Natural";
    
    output[2][1] = "Ace Deuce";
    output[2][2] = "Hard Four";
    output[2][3] = "Fever Five";
    output[2][4] = "Easy Six";
    output[2][5] = "Natural";
    output[2][6] = "Easy Eight";
    
    output[3][1] = "Easy Four";
    output[3][2] = "Fever Five";
    output[3][3] = "Hard Six";
    output[3][4] = "Natural";
    output[3][5] = "Easy Eight";
    output[3][6] = "Nine";
    
    output[4][1] = "Fever Five";
    output[4][2] = "Easy Six";
    output[4][3] = "Natural";
    output[4][4] = "Easy Eight";
    output[4][5] = "Nine";
    output[4][6] = "Easy Ten";
    
    output[5][1] = "Easy Six";
    output[5][2] = "Natural";
    output[5][3] = "Easy Eight";
    output[5][4] = "Nine";
    output[5][5] = "Hard Ten";
    output[5][6] = "Yo-leven";
    
    output[6][1] = "Natural";
    output[6][2] = "Easy Eight";
    output[6][3] = "Nine";
    output[6][4] = "Easy Ten";
    output[6][5] = "Yo-leven";
    output[6][6] = "Midnight";

    
    printf("Hello, and welcome to Craps!\n");
    printf("You will be starting with $1000 in the bank\n");
    
    while(balance != 0) {
    printf("How much would you like to bet?\n");
    scanf("%d", &bet);
    if(bet > balance) {
        printf("You do not have that much money left in the bank, please enter an amount equal to or less than $%d\n", balance);
    }
    else if(bet == 0 || balance == 0) {
        printf("Thanks for playing, Goodbye!\n");
        break;
    }
    else{
        int die1 = rollDie();
        int die2 = rollDie();
        printf("You rolled a %d %d\n", die1, die2);
        //printf(output[die1][die2]);
        printf("%s\n", output[die1][die2]);
        if (die1 + die2 == 7 || die1 + die2 == 11) {
            balance = balance + bet;
            printf("Congrats you got a %s and won $%d\n",output[die1][die2], bet);
            printf("You now have $%d in the bank!\n", balance);
        }
        else if(die1 + die2 == 2 || die1 + die2 == 3 || die1 + die2 == 12) {
            balance = balance - bet;
            printf("Sorry you got a %s and lost $%d\n",output[die1][die2], bet);
            printf("You now have $%d in the bank\n", balance);
        }
        else {
            printf("You received a %s so a point will be set!\n\n", output[die1][die2]);
            int die3;
            int die4;
            do {
            die3 = rollDie();
            die4 = rollDie();
            printf("You rolled a %d %d\n", die3, die4);
            if(die1 + die2 == die3 + die4) {
                balance = balance + bet;
                printf("Congrats you got a %s before rolling a 7 so you won $%d\n",output[die3][die4], bet);
                printf("You now have $%d in the bank!\n", balance);
            }
            else if(die3 + die4 == 7) {
                balance = balance - bet;
                printf("Sorry you got a %s before rolling a %s and lost $%d\n",output[die3][die4],output[die1][die2], bet);
                printf("You now have $%d in the bank\n", balance);
            }
            else {
                printf("You got a %s, roll again!\n",output[die3][die4]);
            }
            }while ((die1 + die2) != (die3 + die4) && (die3 + die4) != 7); //TA Dustin helped me with this
        }
    }
    }
    return 0;
}
