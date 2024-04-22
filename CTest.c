#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int GamingGoing = 1;
const int GameOver = 2;
const int GameWon = 3; 
int wincon;


void printSquareArray(char *arr, int size){
    printf("Squares left %i \n", wincon);
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
    printf("\n");
}


int *return_squares_around(char *arr, int size, int x, int y){
    
    int *squares_around = malloc(17 * sizeof(int));
    int size_of = 1;

    if (x - 1 >= 0 && y - 1 >= 0) {
        squares_around[size_of] = x-1;
        size_of++;
        squares_around[size_of] = y-1;
        size_of++;

    }

    if (y - 1 >= 0) {
        squares_around[size_of] = x;
        size_of++;
        squares_around[size_of] = y-1;
        size_of++;
    }

    if (x + 1 < size && y - 1 >= 0) {
        squares_around[size_of] = x+1;
        size_of++;
        squares_around[size_of] = y-1;
        size_of++;
    }

    if (x - 1 >= 0) {
        squares_around[size_of] = x-1;
        size_of++;
        squares_around[size_of] = y;
        size_of++;
    }

    if (x + 1 < size) {
        squares_around[size_of] = x+1;
        size_of++;
        squares_around[size_of] = y;
        size_of++;
    }

    if (x - 1 >= 0 && y + 1 < size) {
        squares_around[size_of] = x-1;
        size_of++;
        squares_around[size_of] = y+1;
        size_of++;
    }

    if (y + 1 < size) {
        squares_around[size_of] = x;
        size_of++;
        squares_around[size_of] = y+1;
        size_of++;
    }

    if (x + 1 < size && y + 1 < size) {
        squares_around[size_of] = x+1;
        size_of++;
        squares_around[size_of] = y+1;
        size_of++;
    }
    size_of--;
    squares_around[0] = size_of;
    return squares_around;
}

void set_bomb(char *arr, int size, int x , int y){

    arr[y*size+x] = 'X';
    wincon--; 

}

void count_bombs(char *arr, int size, int x, int y){
    if (arr[y*size+x] != 'X'){
    int *neighbors = return_squares_around(arr, size , x , y);
    int ans = 0; 
    int t = neighbors[0];
    for (int i = 1; i < t+1; i++ ) {
    int x = neighbors[i];
    i++; 
    int y = neighbors[i];
    char temp = arr[y*size+x];
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

int click(char *player_map, char *map, int size, int x, int y){

if (map[y*size+x] == 'X') {
return GameOver;
}
else {
player_map[y*size + x ] = map[y*size + x];
int *neighbors = return_squares_around(map, size , x , y);
int t = neighbors[0];
for (int i = 1; i < t ; i++ ){
int x = neighbors[i];
i++;
int y = neighbors[i];
    if (map[y*size + x] != 'X'){
    player_map[y*size + x ] = map[y*size + x];
    wincon--;
            }
    if (map[y*size + x] == ' ' && player_map[y*size+x] != '?'){
    //click(player_map, map, size, x, y);
       } 
    
        }
        free(neighbors);
        return GamingGoing;
    }
}

int main(){

    int ArraySize = 10;
    char map[ArraySize][ArraySize];
    char player_map[ArraySize][ArraySize];
    wincon = ArraySize*ArraySize;
    

    for (int i = 0 ; i < ArraySize ; i++){
        for (int j = 0 ; j < ArraySize ; j++){
        player_map[i][j] = '?';
        }
    }

    random_bombs(*map, ArraySize);
    fill_board_with_numbers(*map, ArraySize);
    click(*player_map, *map, ArraySize, 4, 5);
    printSquareArray(*map, ArraySize);
    printSquareArray(*player_map, ArraySize);
    
    return EXIT_SUCCESS; 

}