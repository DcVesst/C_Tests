#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static const int Gamerunning=1;
static const int GameOver = 2;
static const int GameWon = 3;


void printSquareArray(char *arr, int size){
    printf("  ");
    for (int i = 0 ; i < size ; i++){
        printf("%i", i);
    }
    printf("\n");
    for (int i = 0 ; i < size ; i++){
        printf("%i|",i );
        for (int j = 0 ; j < size ; j++){
        printf("%c", arr[i*size+j]);
        }
        printf("\n");
    }
}


char *return_squares_around(char *arr, int size, int x, int y){
    char **squares_around = malloc(9 * sizeof(char*));
    int size_of = 1;

    if (x - 1 >= 0 && y - 1 >= 0) {
        squares_around[size_of] = &arr[y*size+x-size-1];
        printf("Value at 1 %c \n", *squares_around[size_of]);
        printf("Value at 2 %i \n", &arr[y*size+x-size-1]);
        size_of++;
    }

    if (y - 1 >= 0) {
        squares_around[size_of] = &arr[y*size+x-size];
        size_of++;
    }

    if (x + 1 < size && y - 1 >= 0) {
        squares_around[size_of] = &arr[y*size+x-size+1];
        size_of++;
    }

    if (x - 1 >= 0) {
        squares_around[size_of] = &arr[y*size+x-1];
        size_of++;
    }

    if (x + 1 < size) {
        squares_around[size_of] = &arr[y*size+x+1];
        size_of++;
    }

    if (x - 1 >= 0 && y + 1 < size) {
        squares_around[size_of] = &arr[y*size+x+size-1];
        size_of++;
    }

    if (y + 1 < size) {
        squares_around[size_of] = &arr[y*size+x+size];
        size_of++;
    }

    if (x + 1 < size && y + 1 < size) {
        squares_around[size_of] = &arr[y*size+x+size+1];
        size_of++;
    }
    size_of--;
    squares_around[0] = &size_of;
    return *squares_around;
}

void set_bomb(char *arr, int size, int x , int y){

    arr[y*size+x] = 'X';

}

void count_bombs(char *arr, int size, int x, int y){
    if (arr[y*size+x] != 'X'){
    char *neighbors = return_squares_around(arr, size , x , y);
    int ans = 0; 
    int t = neighbors[0];

    for (int i = 1; i < t+1; i++ ) {
    char temp = neighbors[i];
     printf(" Count bombs string %c \n", temp );
    if (temp == 'X'){
        ans++;
         }
     }
    if (ans != 0){
        arr[y*size+x] =  ans + '0';
    }
    else {
     arr[y*size+x] = ' ';
    }
    //free(neighbors);

    }
}

void fill_board_with_numbers(char *arr, int size){
    for (int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++) {
        count_bombs(arr, size , i, j);
        }
    }
}

void random_bombs(char *arr, int size){

    int nmb_bombs = round(size*size*0.2);
    for (int i = 0 ; i < nmb_bombs; i++){
    int x = random()%size;
    int y = random()%size;
    if (arr[y*size+x] == 'X'){
    i--;
    }
    else {
    set_bomb(arr, size, x ,y);
    }
    }
}

int click(char *map, char *player_map, int size, int x, int y){

    if (map[y*size+x] != 'X'){
    char *neighbors_1 = return_squares_around(player_map, size , x , y);
    char *neighbors_2 = return_squares_around(map, size , x , y);
    int t = neighbors_1[0];

    for (int i = 1; i < t+1; i++ ) {
    char temp = (char) neighbors_2[i];
    if (temp == ' '){
        //click()
        printf("Blank \n ");
         }
     
     else {
        printf("Testing please %c \n ", temp);
        printf("Testing neighbors %c \n", neighbors_1[i]);
       // player_map[y*size+x] = map[y*size+x];
        (neighbors_1[i]) = (char) temp;

        }
     }
    //free(neighbors_1);
    //free(neighbors_2);
    return 1; 
    }
    else {
        return GameOver;
    }

}

int main(){

    int ArraySize = 10;
    char map[ArraySize][ArraySize];
    char player_map[ArraySize][ArraySize];

    for (int i = 0 ; i < ArraySize ; i++){
        for (int j = 0 ; j < ArraySize ; j++){
        player_map[i][j] = '?';
        }
    }

    random_bombs(*map, ArraySize);
    fill_board_with_numbers(*map, ArraySize);
   // click(*map, *player_map, ArraySize, 0, 4);
    printSquareArray(*map, ArraySize);
    printSquareArray(*player_map, ArraySize);
    
    return EXIT_SUCCESS; 

}