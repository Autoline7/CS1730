#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "proj4.h"

//hold the values in a organized manner for the threads and what parts they run
typedef struct {
        grid *input;
        grid *output;
        unsigned long targetSum;
        int startRow;
        int endRow;
} ThreadData;


//works correctly to print the given file and save it to the heap
void initializeGrid(grid * g, char * fileName){
    
    //counts the rows/col and updates the g.n
    countRC(g,fileName);
    
    //allocate memory for the row pointers
    (*g).p = malloc((*g).n * sizeof(unsigned char *));

    //allocate memory for each row
    for(int i = 0; i < (*g).n; i ++){
        *((*g).p + i) = malloc((*g).n * sizeof(unsigned char));
    } 

    int fd = open(fileName,O_RDONLY);

    if(fd == -1){
        printf("Error Opening File");
        return;
    }

    char buf[1];

    int row = 0, col = 0;
    // Read characters and populate the grid
    while (read(fd, buf, 1) > 0) {
        if (buf[0] == '\n') {
            // Move to the next row if a newline is encountered
            row++;
            col = 0;
        } else if (row < (*g).n && col < (*g).n) {
            // Store the character in the grid if within bounds
            *(*((*g).p + row) + col) = buf[0];
            col++;
        }
    }
    close(fd);
    
    return;

}

void countRC(grid * g, char * fileName){
    int buf_size = 2;
    int fd = open(fileName,O_RDONLY);

    char buf[buf_size];
    if(fd == -1){
        printf("Error Opening File");
        return;
    }

    ssize_t numRead = read(fd, buf, buf_size-1);

    int count = 0;


    while(numRead > 0){
        buf[numRead] = '\0';  
        if(buf[0] == '\n'){
            count ++;
        }
        
        numRead = read(fd,buf,buf_size-1);
    }
    (*g).n = count;
    close(fd);
}


// diagonalSums function 
void diagonalSums(grid *input, unsigned long s, grid *output, int t) {
    unsigned int len = (*input).n;
    (*output).n = len;

    // allocate memory for the output grid
    (*output).p = malloc(len * sizeof(unsigned char *));
    for (int i = 0; i < len; i++) {
        *((*output).p + i) = malloc(len * sizeof(unsigned char));
    }

    // initialize all cells of the output grid to '0'
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            *(*((*output).p + i) + j) = '0';
        }
    }

    // divide the grid into chunks for threads
    if (t >= 2) {
        pthread_t threads[t - 1]; // creates t - 1 threads
        ThreadData threadData[t];
        int chunkSize = len / t;

        // create t - 1 threads
        for (int i = 0; i < t - 1; i++) {
            threadData[i].input = input;
            threadData[i].output = output;
            threadData[i].targetSum = s;
            threadData[i].startRow = i * chunkSize;
            threadData[i].endRow = (i + 1) * chunkSize;

            pthread_create(&threads[i], NULL, processDiagonals, &threadData[i]);
        }

        // main thread handles the remaining chunk
        threadData[t - 1].input = input;
        threadData[t - 1].output = output;
        threadData[t - 1].targetSum = s;
        threadData[t - 1].startRow = (t - 1) * chunkSize;
        threadData[t - 1].endRow = len;

        processDiagonals(&threadData[t - 1]); // Main thread processes its chunk

        // wait for all threads to finish
        for (int i = 0; i < t - 1; i++) {
            pthread_join(threads[i], NULL);
        }
    } else if (t == 1) {
        // main thread handles all work
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                forwardDiagonal(input, output, i, j, s, len);
                backDiagonal(input, output, i, j, s, len);
            }
        }
    }
}


// thread function to process a chunk of rows
void *processDiagonals(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    grid *input = data->input;
    grid *output = data->output;
    unsigned long targetSum = data->targetSum;

    for (int i = data->startRow; i < data->endRow; i++) {
        for (int j = 0; j < input->n; j++) {
            forwardDiagonal(input, output, i, j, targetSum, input->n);
            backDiagonal(input, output, i, j, targetSum, input->n);
        }
    }

    return NULL;
}

//check for back diagnal sums
void backDiagonal(grid * input, grid * output, int row, int col, unsigned long targetSum, unsigned int n){
    int givenNum = *(*((*input).p + row) + col) - '0';//convert given val to int
    unsigned long currSum = givenNum;

    int r = row;
    int c = col;
    while (valid(r,c,n) && currSum <= targetSum){
        if(currSum == targetSum){
                //write all the values that added to it into the output (make a function from the givenPointer to the currPointer)
                //for loop copying the values from the value found until the original givenNum
                int oc = col;
                int or = row;
                while( or <= r){
                    *(*((*output).p + or) + oc) = *(*((*input).p + or) + oc);
                    or++;
                    oc++;
                }
        }
        r++;
        c++;
        if(valid(r,c,n)){
            int currentNum = *(*((*input).p + r) + c) - '0';
            currSum += currentNum;
        }
        
    }
    
}

//check for forward diagonal sums
void forwardDiagonal(grid * input, grid * output, int row, int col, unsigned long targetSum, unsigned int n){
    int givenNum = *(*((*input).p + row) + col) - '0';//convert given val to int
    unsigned long currSum = givenNum;

    int r = row;
    int c = col;
    while (valid(r,c,n) && currSum <= targetSum){
        if(currSum == targetSum){
                //write all the values that added to it into the output (make a function from the givenPointer to the currPointer)
                //for loop copying the values from the value found until the original givenNum
            
                int oc = col;
                int or = row;
                while( oc <= c){
                    *(*((*output).p + or) + oc) = *(*((*input).p + or) + oc);
                    or--;
                    oc++;
                }
                
        }
        r--;
        c++;
        if(valid(r,c,n)){
            int currentNum = *(*((*input).p + r) + c) - '0';
            currSum += currentNum;
        }
        
    }
   
    
}

//checks if the given row and col are valid
bool valid(int r, int c, int n){
    return r < n && r >= 0 && c < n && c >= 0;
}

//writes into the output file
void writeGrid(grid * g, char * fileName){
    int fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(fd == -1){
        printf("Error Opening File");
        return;
    }

    
    char newline = '\n';

    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            char digit = g->p[i][j] ; // Convert single-digit number to char
            write(fd, &digit, 1);
        }
        write(fd, &newline, 1); // Newline after each row
    }


    close(fd);
    
    return;

}

//frees the dynamically stored memory
void freeGrid(grid * g){
    for (int i = 0; i < g->n; i++) {
        free(g->p[i]);
    }
    free(g->p);
}


