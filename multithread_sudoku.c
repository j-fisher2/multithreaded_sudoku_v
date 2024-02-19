#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 9
#define NUM_THREADS 27

typedef struct {
    int row;
    int column;
} parameters;

int sudoku[SIZE][SIZE] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
};

int result=1;    //initialize sudoku solution as valid;

void *validate_row(void *param) {
    parameters *data = (parameters *)param;
    int row = data->row;

    int valid[SIZE] = {0}; // Array to store whether a digit has been seen in the row
    for (int i = 0; i < SIZE; i++) {
        int digit = sudoku[row][i];
        if (digit < 1 || digit > 9 || valid[digit - 1]) {
            result=0;
            pthread_exit(NULL);
        }
        valid[digit - 1] = 1;
    }
    pthread_exit(NULL);
}

void *validate_column(void *param){
    parameters *data=(parameters *)param;
    int column=data->column;
    int valid[9] = {0};

    for(int i=0;i<SIZE;i++){
        int digit=sudoku[i][column];
        if(digit<1||digit>9||valid[digit-1]){
            result=0;
            pthread_exit(NULL);
        }
        valid[digit-1]=1;
    }
    pthread_exit(NULL);
}

void *validate_subgrid(void *param){
    parameters *data=(parameters *)param;
    int column=data->column;
    int row=data->row;
    int valid[9]={0};
    
    for(int i=row;i<row+3;i++){
        for(int j=column;j<column+3;j++){
            int digit=sudoku[i][j];
            if(digit<1||digit>9||valid[digit-1]){
                result=0;
                pthread_exit(NULL);
            }
            valid[digit-1]=1;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    parameters *data;

    // Create threads to validate rows
    for (int i = 0; i < SIZE; i++) {
        data = (parameters *)malloc(sizeof(parameters));
        data->row = i;
        pthread_create(&threads[i], NULL, validate_row, (void *)data);
    }

    // Create threads to validate columns
    for(int j=9;j<SIZE*2;j++){
        data=(parameters *)malloc(sizeof(parameters));
        data->column=j%SIZE;
        pthread_create(&threads[j],NULL,validate_column,(void *)data);
    }

    // Create threads to validate subgrids
    int cur_thread=18;
    for(int k=0;k<SIZE;k+=3){ //current row
        for(int x=0;x<SIZE;x+=3){  //current column
            data=(parameters *)malloc(sizeof(parameters));
            data->row=k;
            data->column=x;
            pthread_create(&threads[cur_thread],NULL,validate_subgrid,(void *)data);
            cur_thread++;
        }
    }

    //wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    switch(result){
        case 0:
            printf("invalid sudoku");
            break;
        case 1:
            printf("valid sudoku");
            break;
    }

    return result;
}
