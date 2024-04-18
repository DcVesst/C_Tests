#include <stdio.h>
#include <stdlib.h>


void printSquareArray(int *arr, int size){

    for (int i = 0 ; i < size ; i++){
        for (int j = 0 ; j < size ; j++){
        printf("%i", arr[i*size+j]);
        }
        printf("\n");
    }
}


int *return_squares_around(int *arr, int size, int x, int y){
    
    int* squares_around = (int*)malloc(9 * sizeof(int));
    int size_of = 1;
        arr[y*size+x] = 0;
    if (x - 1 >= 0 && y - 1 >= 0) {
        arr[y*size+x-size-1] = 1;
        squares_around[size_of] = arr[x*size+y-size-1];
       size_of++;

    }

    if (y - 1 >= 0) {
        arr[y*size+x-size] = 2;
        squares_around[size_of] = arr[x*size+y-size];
        //printf("Pointer %p \n value at pointer %i \n", squares_around[size_of], *squares_around[size_of]);
        size_of++;
    }

    if (x + 1 < size && y - 1 >= 0) {
        arr[y*size+x-size+1] = 3;
        squares_around[size_of] = arr[y*size+x-size+1];
        size_of++;
    }

    if (x - 1 >= 0) {
        arr[y*size+x-1] = 4;
        squares_around[size_of] = arr[y*size+x-1];
        size_of++;
    }

    if (x + 1 < size) {
        arr[y*size+x+1] = 5;
        squares_around[size_of] = arr[y*size+x+1];
        size_of++;
    }

    if (x - 1 >= 0 && y + 1 < size) {
        arr[y*size+x+size-1] = 6;
        squares_around[size_of] = arr[y*size+x+size-1];
        size_of++;
    }

    if (y + 1 < size) {
        arr[y*size+x+size] = 7;
        squares_around[size_of] = arr[y*size+x+size];
        size_of++;
    }

    if (x + 1 < size && y + 1 < size) {
        arr[y*size+x+size+1] = 8;
        squares_around[size_of] = arr[y*size+x+size+1];
        size_of++;
    }
    size_of--;
    squares_around[0] = size_of;
    return squares_around;
}

void printy(int *arr){
int x = arr[0];
printf("Number of surronding squares is = %i which is good! \n" , x);
for (int i = 1; i < x+1; i++ ) {
    int temp = arr[i];
    printf("Value at the pointer is %i \n", temp );
    }

    free(arr);
}

int main(){
    int ArraySize = 10;
    int map[ArraySize][ArraySize];

    for (int i = 0 ; i < 10 ; i++){
        for (int j = 0 ; j < 10 ; j++){
        map[i][j] = 1;
        }
    }

 printy(return_squares_around(*map, 10 , 4, 0));
 
    printSquareArray(*map, 10);
    return EXIT_SUCCESS; 

}