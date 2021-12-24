#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

void star();
int checking(int userInput , int random_number);
int random_number;
int userInput;


int main(void){

    srand(time(0)); //This will set the starting of the randomn integers according to the time
    random_number = rand() % 100; //rand() function generate the random integer and set it between 1 and 100

    printf("The random number is : %d\n" , random_number);


    bool flag = true;
    for(int i = 0; i < 3; i++){
        printf("\nInput the gessing number(as a integer) : ");
        scanf("%d" , &userInput);
        char temp = checking(userInput , random_number);
        if(temp == 85){
            flag = false;
            break;
        }
    }
    if(flag){
        star();
        printf("%50s\n", "YOU LOST - NO. OF CHANCES ARE OVER");
        star();
    }
    return 0;
}

int checking(int userInput , int random_number){
    if(userInput > random_number){
        printf("The inputed value is greater than the guessing number.\n");
        return 55;
    }
    else if(userInput < random_number){
        printf("The inputed value is smaller than the guessing number.\n");
        return 55;
    }
    else{
        star();
        printf("%40s\n" , "YOU WON");
        star();
        return 85;
    }
}


void star(){
    printf("*************************************************************************************\n");
}
