#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

const int game_going = 1;
const int game_over = 2;
const int game_won = 3; 
int wincon;

//Around 6.6 times faster than my implementation in C#

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

int click(char *player_map, char *map, int size, int x, int y) {
    if (x < 0 || y < 0 || x > size || y > size) {
    printf(" Please enter a valid cordinates \n");
    return game_going;
    }
    if(player_map[y*size+x] != '?'){
    printf("Already pressed this square \n");
    return game_going;
    }
    if (map[y * size + x] == 'X') {
        return game_over;
    } else {
        player_map[y * size + x] = map[y * size + x];
        wincon--;
        int *neighbors = return_squares_around(map, size, x, y);
        int t = neighbors[0];
        for (int i = 1; i < t; i += 2) {
            int x = neighbors[i];
            int y = neighbors[i + 1];

            if ((map[y * size + x] == ' ') && (player_map[y * size + x] == '?')) {
               click(player_map, map, size, x, y);
            }

            if ((map[y * size + x] != 'X') && (player_map[y * size + x] == '?')) {
                player_map[y * size + x] = map[y * size + x];
                wincon--;
            }

             
        }
        free(neighbors);
        if (wincon == 0 ) {
            return game_won;
        }
        else {
            return game_going;
        }
       
    }
}

int main(){

    int ArraySize = 5000;
    char *map = malloc(ArraySize*ArraySize* sizeof(char));
    char *player_map = malloc(ArraySize*ArraySize* sizeof(char));
    wincon = ArraySize*ArraySize;
    

    for (int i = 0 ; i < ArraySize ; i++){
        for (int j = 0 ; j < ArraySize ; j++){
        player_map[j*ArraySize + i] = '?';
        }
    }
    int game_state = game_going;

    time_t t0 = time(0);
    random_bombs(map, ArraySize);
    time_t t1 = time(0);
    double datetime_diff_ms = difftime(t1, t0) * 1000.;
    printf("Generate bombs %f ms \n",datetime_diff_ms);

    time_t t2 = time(0);
    fill_board_with_numbers(map, ArraySize);
    time_t t3 = time(0);
    double datetime_diff_ms2 = difftime(t3, t2) * 1000.;
    printf("Generate numbers %f ms \n",datetime_diff_ms2);
    //click(*player_map, *map, ArraySize, 5, 7);
    //printSquareArray(map, ArraySize);
    //printSquareArray(player_map, ArraySize);
    while(game_state == game_going) {
    
    char line[100]; // Assuming a maximum line length of 100 characters 
    printf("Enter cordinates \n"); 
    fgets(line, sizeof(line), stdin);
    
    int x = line[0]-'0';
    int y = line[2]-'0';
    
    game_state = click(player_map, map, ArraySize, x, y);
   // printSquareArray(*map, ArraySize);
    //printSquareArray(player_map, ArraySize);
    }
    if (game_state == game_won) {
    printf("You won! \n");
    }
    if (game_state == game_over) {
    printSquareArray(map, ArraySize);
    printf("Pressed a bomb! \n");

    }
    free(map);
    free(player_map);
    return EXIT_SUCCESS; 

}