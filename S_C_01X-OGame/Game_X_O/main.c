
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define clrscr() printf("\e[1;1H\e[2J")
#define MAX_POSITION 9
#define No_OF_PLAYER 2

typedef unsigned char uint8_t;

uint8_t configArray[No_OF_PLAYER];
uint8_t board[MAX_POSITION]={};

void drawBoard(uint8_t *board);

/*   | |
    X|O|O
    _|_|_
     | |
    X|O|X
    _|_|_
     | |
    X|O|x
     | |

            */
void updateBoard(uint8_t*board, uint8_t position, uint8_t value);

uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t *symbol);
void setPlayerConfig(uint8_t *configArray);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t*board, uint8_t *gameState);/*0 = winning, 1=draw, 2=continue */

/**/

int main()
{
    SMALL_RECT windowSize = {0 , 0 , 44 , 20}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    uint8_t state =2;
    uint8_t player_no = 1;

    setPlayerConfig(configArray);

    do{
            system("cls");

            drawBoard(board);
            player_no = (player_no % 2)? 1 : 2;

            loadAndUpdate(player_no);


            printf("\n");
            getGameState(board,&state);
            player_no++;

    }while(state == 2);
    system("cls");
    drawBoard(board);

    if(state == 0){
        printf("Player (%d) win", --player_no);
    }
    else if(state == 1){
        printf("Game draw\n");
    }

    return 0;
}

void drawBoard(uint8_t *board){
    char tmp = ' ';

printf("     |     |    \n");
printf("  %c  |  %c  |  %c  \n", (board[0] == 0)?tmp:board[0],(board[1] == 0)?tmp:board[1],(board[2] == 0)?tmp:board[2]);
printf("_____|_____|_____\n");
printf("     |     |    \n");
printf("  %c  |  %c  |  %c  \n", (board[3] == 0)?tmp:board[3],(board[4] == 0)?tmp:board[4],(board[5] == 0)?tmp:board[5]);
printf("_____|_____|_____\n");
printf("     |     |    \n");
printf("  %c  |  %c  |  %c  \n", (board[6] == 0)?tmp:board[6],(board[7] == 0)?tmp:board[7],(board[8] == 0)?tmp:board[8]);
printf("     |     |    \n");

}

void updateBoard(uint8_t*board, uint8_t position, uint8_t value){
    if(position <= MAX_POSITION){
            position--;
            board[position] =  value;

    }else{

    }

}


uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t *symbol){
    static uint8_t saved_symbol;
    uint8_t result_state =1;
    uint8_t tmp_sym;
    printf("Enter your symbol(X or O) player (%d):", playerNumber);
    scanf(" %c",&tmp_sym);
    if((tmp_sym == 'x'||tmp_sym == 'X')&& saved_symbol != 'X'){
        *symbol = 'X';
        saved_symbol = 'X';
        result_state =0;
    }else if((tmp_sym == 'o'||tmp_sym == 'O')&& saved_symbol != 'O'){
        *symbol = 'O';
        saved_symbol = 'O';
        result_state =0;
    }else{
        result_state =1;
    }
    return result_state;
}


void setPlayerConfig(uint8_t *configArray){
    uint8_t result_state =1;
    for(int i =0; i< No_OF_PLAYER; i++){
        result_state = getPlayerSymbol((i+1), (configArray+i));
        if(result_state == 1){
            printf("You entered wrong symbol or chosen before\n");
            i--;
        }else{

        }

    }

}


void loadAndUpdate(uint8_t playerNumber){
    int position;
    char term;
    uint8_t flag = 0;
    printf("Player(%d)\nEnter your chosen position:", playerNumber);

    while(scanf("%d%c", &position, &term) != 2 || term != '\n'){
        printf("you should enter integer value\n");
        getchar();
        printf("Player(%d)\nEnter your chosen position:", playerNumber);
    }

    do{
        if(board[position-1] != 0){
            printf("Player(%d)\nyou have chose chosen position reenter\n", playerNumber);
            printf("Player(%d)\nEnter your chosen position:", playerNumber);
            scanf("%d",&position);

        }else{

            updateBoard(board, position, configArray[playerNumber-1]);
            flag=1;
        }

    }while(flag == 0);



}
void getGameState(uint8_t*board, uint8_t *gameState){
    uint8_t ret_state =2;
    if(ret_state !=0){

        for(int i=0 ; ((i<MAX_POSITION/3)&&(ret_state != 0));i+=1){
             if((board[i] == 'X')||(board[i] == 'O')){
                 if((board[i] == board[i+3]) && (board[i+3] == board[i+6])){
                    ret_state=0;
                 }
            }

        }
    }
    if(ret_state !=0){

        for(int i=0 ; ((i<MAX_POSITION)&&(ret_state != 0));i+=3){
            if((board[i] == 'X')||(board[i] == 'O')){
                if((board[i] == board[i+1]) && (board[i+1] == board[i+2])){
                ret_state=0;
                }
            }


        }
    }
    if(ret_state !=0){

        if((board[0] == 'X')||(board[0] == 'O')){

            if(((board[0] == board[4]) && (board[4] == board[8]))){

                ret_state=0;
            }


        }else if((board[2] == 'X')||(board[2] == 'O')){
            if(((board[2] == board[4]) && (board[4] == board[6]))){

                ret_state=0;
            }


        }

    }

    if(ret_state !=0){

        uint8_t iter = 0;
        for(;iter <MAX_POSITION;iter++){
            if(board[iter] == 0){
                break;
            }
        }

        if(iter == MAX_POSITION){
            ret_state = 1;
        }
    }
    *gameState=ret_state;
}



