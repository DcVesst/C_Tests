#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
    
    char* squares_around = (char*)malloc(9 * sizeof(char));
    int size_of = 1;

    if (x - 1 >= 0 && y - 1 >= 0) {
        squares_around[size_of] = arr[y*size+x-size-1];
        size_of++;

    }

    if (y - 1 >= 0) {
        squares_around[size_of] = arr[y*size+x-size];
        size_of++;
    }

    if (x + 1 < size && y - 1 >= 0) {
        squares_around[size_of] = arr[y*size+x-size+1];
        size_of++;
    }

    if (x - 1 >= 0) {
        squares_around[size_of] = arr[y*size+x-1];
        size_of++;
    }

    if (x + 1 < size) {
        squares_around[size_of] = arr[y*size+x+1];
        size_of++;
    }

    if (x - 1 >= 0 && y + 1 < size) {
        squares_around[size_of] = arr[y*size+x+size-1];
        size_of++;
    }

    if (y + 1 < size) {
        squares_around[size_of] = arr[y*size+x+size];
        size_of++;
    }

    if (x + 1 < size && y + 1 < size) {
        squares_around[size_of] = arr[y*size+x+size+1];
        size_of++;
    }
    size_of--;
    squares_around[0] = size_of;
    return squares_around;
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
    char temp = (char) neighbors[i];
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
    free(neighbors);
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

void click(char *arr, int size, int x, int y){
char *neighbors = return_squares_around(arr, size , x , y);
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
    printSquareArray(*map, ArraySize);
    printSquareArray(*player_map, ArraySize);
    
    return EXIT_SUCCESS; 

}