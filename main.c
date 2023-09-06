#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void outputInfo() {
    printf("-----------------------------\n          Mastermind\n-----------------------------\nHow to play:\n1)Enter a lenght\n2)Guess the number\n3)Win the game!\nLegend:\n*=Correct position\n~=Position Incorrect (Number exists)\n_=Number does not exist\n\n");
}
//Explizite Funktionsaufrufe
int inputLengthOfMN();
void endGame(int win, int tries);
int arrayContainsNumber(int num,int* mn,int len);
void gameAlgorithm(int len,int* mysteryNum);
void genNumber(int* mysteryNumber,int len);
void startGame();
int printStatus(int* mysteryNumber,int* guessedNumber,int len);
void guessNumber(int* guessedNumber,int len);

//Main-Funktion
int main(void) {
    startGame();
    return 0;
}
/*//-------------------------------------------------------------------------------
//Parameter:        -
//Return Value:     -
//Function:         Controlls the game
*///-------------------------------------------------------------------------------
void startGame() {
    outputInfo();
    int len=inputLengthOfMN();
    int mysteryNumber[len];
    genNumber(mysteryNumber,len);
    gameAlgorithm(len, mysteryNumber);
}
/*//-------------------------------------------------------------------------------
//Parameter:        -
//Return Value:     -
//Function:         Requests a length of the mystery number
*///-------------------------------------------------------------------------------
int inputLengthOfMN() {
    int erg=0,error=0;
    do {
        printf("Length of the mystery number:");
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
//Parameter:        -
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
//Parameter:        -
//Return Value:     -
//Function:         Length of the Mystery number, Pointer to the mystery number
*///-------------------------------------------------------------------------------
void gameAlgorithm(int len,int* mysteryNum) {
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
//Parameter:        -
//Return Value:     -
//Function:         Controlls the game
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
void guessNumber(int* guessedNumber,int len) {
    int guess=0;
    int begin=len-1;
    char stringGuess[20];
    int contains2Numbers=0;
start:
        printf("Guess:\n");
        scanf("%d",&guess);
        sprintf(stringGuess,"%d",guess);

        if(len!=strlen(stringGuess)) {
            printf("Guess needs to be as long as the mystery number!\n");
            goto start;
        }

        for(int i=0; i<strlen(stringGuess); i++) {
            contains2Numbers=0;
            for(int x=0; x<strlen(stringGuess); x++) {
                if(stringGuess[i]==stringGuess[x]) {
                    contains2Numbers++;
                }
                if(contains2Numbers==2) {
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
void endGame(int win,int tries) {
    if(win) {
        printf("Tries left: %d\nYou have won!",tries);

    } else {
        printf("You have lost.\nGood luck next time!");
    }
}
