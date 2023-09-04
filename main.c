#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void outputInfo() {
    printf("-----------------------------\n          Mastermind\n-----------------------------\nHow to play:\n1)Enter a lenght\n2)Guess the number\n3)Win the game!\nLegend:\n*=Correct position\n~=Position Incorrect (Number exists)\n_=Number does not exist\n\n");
}
int inputLengthOfMN();
void gameAlgorithm(int len,int* mysteryNum);
void genNumber(int* mysteryNumber,int len);
void startGame();
int printStatus(int* mysteryNumber,int* guessedNumber,int len);
void guessNumber(int* guessedNumber,int len);


int main(void) {
    startGame();
    return 0;
}
void startGame() {
    outputInfo();
    int len=inputLengthOfMN();
    int mysteryNumber[len];
    genNumber(mysteryNumber,len);
    gameAlgorithm(len, mysteryNumber);
}
int inputLengthOfMN() {

    int erg;
    printf("Length of the mystery number:");
    scanf("%d",&erg);
    return erg;
}
void genNumber(int* mysteryNumber,int len) {
    srand(time(NULL));
    for (int i = 0; i < len ; i++) {
        mysteryNumber[i] = 10;
    }
    int x=0;
    do {
        int generator=rand()%10;
//        if(!arrayContainsNum(mysteryNumber,generator,len)) {
        mysteryNumber[x]=generator;
        x++;
    } while(x!=len);
}

void gameAlgorithm(int len,int* mysteryNum) {
    int correct=0;
    int guessedNumber[len];
    int tries=len*2;
    do {
        correct=printStatus(mysteryNum,guessedNumber,len);
        guessNumber(guessedNumber,len);
    } while(correct==0&&tries!=0);
}

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
    if(correct==len){
        return 1;
    }
    return 0;
}
void guessNumber(int* guessedNumber,int len) {
    int guess=0;
printf("\nGuess:");
scanf("%d",&guess);
printf("%d,%d,%d,%d",guess/1000,guess/100%10,guess/10%10,guess%10);
}
