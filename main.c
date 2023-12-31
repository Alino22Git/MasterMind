#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void outputInfo() {
    printf("-----------------------------\n          Mastermind\n-----------------------------\nHow to play:\n1)Enter a lenght\n2)Guess the number\n3)Win the game!\nLegend:\n*=Correct position\n~=Position Incorrect (Number exists)\n_=Number does not exist\n\n");
}
//Explicit Function-Calls
int inputLengthOfMN();
void endGame(int win, int tries);
int arrayContainsNumber(int num,int* mn,int len);
void gameAlgorithm(int* mysteryNum,int len);
void genNumber(int* mysteryNumber,int len);
void startGame();
int printStatus(int* mysteryNumber,int* guessedNumber,int len);
void guessNumber(int* guessedNumber,int len);

//Main-Function
int main(void) {
    startGame();
    return 0;
}
/*//-------------------------------------------------------------------------------
//Parameter:        -
//Return Value:     -
//Function:         Controls the game
*///-------------------------------------------------------------------------------
void startGame() {
    outputInfo();
    int len=inputLengthOfMN();
    int mysteryNumber[len];
    genNumber(mysteryNumber,len);
    gameAlgorithm(mysteryNumber,len);
}
/*//-------------------------------------------------------------------------------
//Parameter:        -
//Return Value:     Length of the mystery number
//Function:         Requests a length of the mystery number
*///-------------------------------------------------------------------------------
int inputLengthOfMN() {
    int erg=0,error=0;
    do {
        printf("Length of the mystery number:");
        fflush(stdin); //Flush buffer (ex. letters)
        scanf("%d",&erg);
        error=1;
        if(erg>9||erg<1) {
            printf("The number needs to be between 1-9!\n");
            error=0;
        }
    } while(error==0);
    printf("Tries: %d\n",erg*2);
    return erg;
}
/*//-------------------------------------------------------------------------------
//Parameter:        Pointer to the mystery number, length of the mystery number
//Return Value:     -
//Function:         Generates a random mystery number
*///-------------------------------------------------------------------------------
void genNumber(int* mysteryNumber,int len) {
    srand(time(NULL));
    int flag = 0;
    for (int i = 0; i < len ; i++) {
        mysteryNumber[i] = 10;
    }
    int x=0;
    do {
        flag=0;
        int generatedNumber=rand()%9+1;
        flag=arrayContainsNumber(generatedNumber,mysteryNumber,x);
        if(flag) {
            mysteryNumber[x]=generatedNumber;
            x++;
        }
    } while(x!=len);
}
/*//-------------------------------------------------------------------------------
//Parameter:        Pointer to the mystery number, length of the mystery number
//Return Value:     -
//Function:         Controls the gameloop
*///-------------------------------------------------------------------------------
void gameAlgorithm(int* mysteryNum,int len) {
    int correct=0;
    int guessedNumber[len];
    for (int i = 0; i < len ; i++) {
        guessedNumber[i] = 10;
    }
    int tries=len*2;
    do {
        guessNumber(guessedNumber,len);
        correct=printStatus(mysteryNum,guessedNumber,len);
        tries--;
    } while(correct==0&&tries!=0);
    endGame(correct,tries);
}
/*//-------------------------------------------------------------------------------
//Parameter:        Pointer to the mystery number, pointer to the guessed number, length of the mystery number
//Return Value:     Returns 1 if the player guessed the number (else 0)
//Function:         Prints the progress of the guesses
*///-------------------------------------------------------------------------------
int printStatus(int* mn,int* gn,int len) {
    int x=0;
    int exist=0;
    int correct=0;
    do {
        exist=0;
        if(mn[x]==gn[x]) {
            printf("*");
            correct++;
        } else {
            for(int i=0; i<len; i++) {
                if(mn[i]==gn[x]) {
                    exist++;
                }
            }
            if(exist!=0) {
                printf("~");
            } else {
                printf("_");
            }
        }
        x++;
    } while(x!=len);
    printf("\n");
    if(correct==len) {
        return 1;
    }
    return 0;
}
/*//-------------------------------------------------------------------------------
//Parameter:        Pointer to the guessed number, length of the mystery number
//Return Value:     -
//Function:         Requests a guess from the player
*///-------------------------------------------------------------------------------
void guessNumber(int* guessedNumber,int len) {
    int guess=0;
    int begin=len-1;
    char stringGuess[20];
    int contains2Numbers=0;
start:
    printf("Guess:\n");
    fflush(stdin); //flush buffer (ex. letters)
    scanf("%d",&guess);
    sprintf(stringGuess,"%d",guess); //int -> String

    if(len!=strlen(stringGuess)) {
        printf("Guess needs to be as long as the mystery number!\n");
        goto start; //goes back to start 142
    }

    for(int i=0; i<strlen(stringGuess); i++) {
        contains2Numbers=0;
        for(int x=0; x<strlen(stringGuess); x++) {
            if(stringGuess[i]==stringGuess[x]) {
                contains2Numbers++;
            }
            if(contains2Numbers==2) { //if a number appears more than one time in the array
                printf("Guess needs to contain distinct numbers!\n");
                goto start;
            }
        }
    }

    for(int i=0; i<strlen(stringGuess); i++) {
        if(stringGuess[i]=='0') { //f�hrende Null standardm��ig ignoriert. Dies liegt daran, dass in C f�hrende Nullen in Integer-Literalen als Pr�fix verwendet werden, um Zahlen als Oktalzahlen (Basis 8) zu interpretieren.
            printf("Guess is not allowed to contain 0!\n");
            goto start;
        }
    }


    for(int i=0; i<len; i++) {
        guessedNumber[i]=(int)(guess/pow(10,begin)) % 10;
        begin--;
    }

}
/*//-------------------------------------------------------------------------------
//Parameter:        Generated number, pointer to the guessed number, length of the mystery number
//Return Value:     1 for true else 0
//Function:         Tests the generated number of distinct numbers
*///-------------------------------------------------------------------------------
int arrayContainsNumber(int num,int* mn,int len) {
    int exist=0;
    for(int i=0; i<len; i++) {
        if(num==mn[i]) {
            exist=1;
        }
    }
    if(exist==0) {
        return 1;
    }
    return 0;
}
/*//-------------------------------------------------------------------------------
//Parameter:        Integer decide the outcome (win/lose), number of tries
//Return Value:     -
//Function:         Prints the outcome of the game
*///-------------------------------------------------------------------------------
void endGame(int win,int tries) {
    if(win) {
        printf("Tries left: %d\nYou have won!",tries);

    } else {
        printf("You have lost.\nGood luck next time!");
    }
}
