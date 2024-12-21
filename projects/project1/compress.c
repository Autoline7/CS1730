#include <stdio.h>
#include "compress.h"
#include <string.h>

void compress(char input[]){
  int inputLength = strlen(input);
  int arrLength = (inputLength / 4) + 2;
  int ans[arrLength];
  ans[0] = inputLength;
  int j = 1;
  unsigned char c = '\0';

  for(int i = 0; i < inputLength ; i ++){
    
    if(i != 0 && i % 4 == 0){
      ans[j] = (int)c;
      j++;
      c = 0b00000000;
     }
    int value = valueOf(input[i]);
    c = c << 2;
    c = c | value;
  }
  
  if(inputLength % 4 != 0){
    int extraLength = inputLength % 4;
      
    int shifts = 2 * (4 - extraLength);  // Calculate how much we need to shift the remaining bits
        c = c << shifts;  // Shift left to align bits
        ans[j] = (int)c;  // Store the last byte
        j++;
  } else if (inputLength > 0) {
        // If perfectly divisible by 4, store the last group
        ans[j] = (int)c;
        j++;
  }
  printAns(ans,j);
  
}

void printAns(int arr[], int length){
  for(int i = 0; i < length; i ++){
      printf("%i ", arr[i]);

  }
  printf("\n");

}

int valueOf(char i){
  if(i == 'A'){
    return 0;
  }
  if(i == 'T'){
    return 1;
  }
  if(i == 'C'){
    return 2;
  }
  return 3;

}
