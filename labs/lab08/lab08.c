#include <stdio.h>//atoi
#include <stdlib.h>//malloc, free
/*
 * Return the sum of the n values in x starting at index 0.
 * If x is NULL, then return -1.
 * If n is 0 and x is not NULL, then return 0.
 */
//returns the sum up tp n values as the pointer shifts.
int sum(int * x, int n);

//global null pointer
int * p;
int main(int argc, char * argv[]){
  //x should point to a new array of ints stored on the heap
  int * x = (int *) malloc(sizeof(int) * (argc -1));
  for(int i = 0; i < argc-1; i++){
     x[i] = atoi(argv[i+1]);
  }
  
  
  if(argc <= 1){//if it contains zero arguments to avoid invalid error
    printf("*x is %d\n", 0);
  }
  else{//if it contains arguments
    printf("*x is %d\n", x[0]);
  }
  //get y
  int y = sum(x, argc-1);
  //print y
  printf("y is %d\n", y);
  //getz if p is a null pointer
  int z = sum(p, argc-1);

  //print z
  printf("z is %d\n", z);

  //freee up the x pointer since its pointing in the heap
  free(x);

  //returns 0 for main funtion
  return 0;
}

int sum(int * x, int n){
  if(x == NULL){
    return -1;
  }
  int sum = 0;
  for(int i = 0; i < n; i++){
    sum += x[i]; 
  }
  return sum;
  
}

