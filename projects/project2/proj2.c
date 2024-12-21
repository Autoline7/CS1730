#include <stdio.h>//scanf
#include <stdlib.h>//malloc calloc

//prints the List of the grades compared to the average and also 
void printList(double (*ptr)[5], int count, double avg, int allocs, int frees, int bytes, int aloccatedBytes);

//copies tmp array to ptr array everytime it resizes
void copy(double * tmp, double * ptr,int count);

//returns the average of the array
double averageOfArray(double *ptr, int numOf);

//main method guides the program in the general direction and has a couple of other funtions to help it
int main(){

  printf("Enter a list of grades below where each grade is separated by a newline character.\n");
  printf("After the last grade is entered, enter a negative value to end the list.\n");
  double input = 0;//value the input
  int numOf = 0;//number of Inputs
  double (*ptr) [5] = NULL;//pointer to an array of doubles
  double avg = 0;// average of the grades
  int allocs = 0;//counts the number of allocations
  int frees = 0;//counts the number of frees
  int bytes = 0;//counts the number of bytes to are getting allocated next allocation
  int aloccatedBytes = 0;//counts the total number of bytes allocated
  
  while(input >= 0){
    scanf("%lf", &input);

    if(numOf == 0 && input < 0){
      printf("The average of %i grades is %.6f. \ntotal heap usage: %i allocs, %i frees, %i bytes allocated\n", numOf, avg, allocs, frees, bytes);
      return 0;
    }
    
    if(input < 0){
      frees++;
      avg = averageOfArray(*ptr, numOf);
      printList(ptr,numOf,avg,allocs, frees, bytes, aloccatedBytes);//prints the list and ending lines
      free(ptr);
      return 0;
    }
    numOf++;//counts number of valid inputs
    
    
    if (numOf == 1){
      ptr = (double (*)[]) malloc(sizeof(double) * 5);
      printf("Allocated 40 bytes to the heap at %p.\n" , (void*)ptr);
      allocs++;
      bytes += 40;
      aloccatedBytes += ( 1+  (numOf / 5)) * sizeof(double) * 5;//adds the bytes that were just allocated
      
      *((*ptr )+ numOf-1) = input;//saves input in the heap "Array of length 5 at most" its numOf -1 so the array starts at index 0                                                                                
      printf("Stored %.6f in the heap at %p.\n", *((*ptr )+ numOf-1) , (void*)(ptr + numOf-1) );
    }
    else if(numOf % 5 == 0){
      *((*ptr )+ numOf-1) = input;//saves input in the heap "Array of length 5 at most" its numOf -1 so the array starts at index 0
      printf("Stored %.6f in the heap at %p.\n", *((*ptr )+ numOf-1) , (void*)(ptr + numOf-1) );

      
      printf("Stored %d grades (%lu bytes) to the heap at %p.\n",numOf, numOf * sizeof(double), (void*)ptr);
      printf("Heap at %p is full.\n", (void*)ptr);

      
      double (* tmp)[5] = ptr;//temp pointer to help copy the values
      
      ptr = (double (*)[]) malloc(( 1+  (numOf / 5)) * sizeof(double) * 5);
      //COPY THE ARRAY FROM TEMP TO THE ARRAY THAT PTR IS POINTING TO
      copy(*tmp,*ptr,numOf);

      printf("Allocated %lu bytes to the heap at %p.\n" , (5 + numOf) * sizeof(double), (void*)ptr);

      printf("Copied %i grades from %p to %p.\n", numOf, (void *) tmp, (void *) ptr);
      printf("Freed %lu bytes from the heap at %p.\n", numOf * sizeof(double), (void *) tmp);

      free(tmp);//frees the previus array                                                                                                                                                                          
      frees++;
      allocs++;
      bytes += 40;
      aloccatedBytes += ( 1+  (numOf / 5)) * sizeof(double) * 5;//adds the bytes that were just allocated   ;
      
    }else{
      *((*ptr )+ numOf-1) = input;//saves input in the heap "Array of length 5 at most" its numOf -1 so the array starts at index 0                                                                                
      printf("Stored %.6f in the heap at %p.\n", *((*ptr )+ numOf-1) , (void*)(ptr + numOf-1) );


    }

  }
  free(ptr);
  frees++;


  return 0;
}

double averageOfArray(double *ptr, int count){
  double ans = 0;
  for(int i = 0; i < count; i ++){
    ans += *(ptr + i);
  }

  return ans/count;
}

void copy(double * tmp, double * ptr,int count){

  for(int i = 0; i < count; i ++){
    *(ptr + i) = *(tmp + i);
  }

}

void printList(double (*ptr)[5], int count, double avg, int allocs, int frees, int bytes, int aloccatedBytes){
  printf("The average of %i grades is %.6f. \n", count, avg);

  
  for(int i = 0; i < count; i ++){
    char c[3];
    if(*((*ptr )+ i) < avg){
      *c = '<';
      *(c+1) = '\0';
      *(c+2) = '\0';
    }
    else{
      *c = '>';
      *(c+1) = '=';
      *(c+2) = '\0';
    }
       printf("%i. The grade of %.6f is %s the average.\n", i+1, *((*ptr )+ i), c);
  }
  printf("Freed %i bytes from the heap at %p.\n", bytes, (void *)ptr);

  printf("total heap usage: %i allocs, %i frees, %i bytes allocated\n", allocs, frees, aloccatedBytes);

}
