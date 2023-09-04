#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void outputInfo() {
    printf("-----------------------------\n          Mastermind\n-----------------------------\nHow to play:\n1)Enter a lenght\n2)Guess the number\n3)Win the game!\nLegend:\n*=Correct position\n~=Position Incorrect (Number exists)\n_=Number does not exist\n\n");
}
int inputLengthOfMN();
int arrayContainsNumber(int num,int* mn,int len);
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
    int flag = 0;
    for (int i = 0; i < len ; i++) {
        mysteryNumber[i] = 10;
    }
    int x=0;
    do {
        flag=0;
        int generatedNumber=rand()%10;
        flag=arrayContainsNumber(generatedNumber,mysteryNumber,x);
        if(flag==1) {
            mysteryNumber[x]=generatedNumber;
            x++;
        }
    } while(x!=len);

}

void gameAlgorithm(int len,int* mysteryNum) {

    int correct=0;
    int guessedNumber[len];
    for (int i = 0; i < len ; i++) {
        guessedNumber[i] = 10;
    }
    int tries=len*2;
    do {
        //    printf("Mystery Number:");
//    for (int i = 0; i < len ; i++) {
//            printf("%d",mysteryNum[i]);
//    }
//    printf("\nGuessed Number:");
//        for (int i = 0; i < len ; i++) {
//            printf("%d",guessedNumber[i]);
//    }
//    printf("\n");
        guessNumber(guessedNumber,len);
        correct=printStatus(mysteryNum,guessedNumber,len);

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
    if(correct==len) {
        return 1;
    }
    return 0;
}
void guessNumber(int* guessedNumber,int len) {
    int guess=0;
    int begin=len-1;
    printf("\nGuess:");
    scanf("%d",&guess);
//printf("%d,%d,%d,%d",guess/1000%10,guess/100%10,guess/10%10,guess%10);
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
