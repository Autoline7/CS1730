#include <stdio.h>
#include "decompress.h"

void decompress(int input[], int lengthOfArray, int lengthOfString){
  int length = lengthOfArray;
  char ans[length * 4];
  int pos = 0;
  int num = 0;
  for(int i = 0; i < length; i ++){
    unsigned char curr = input[i];
    if(lengthOfString>=4){
    num = 4;
    lengthOfString-=4;
    }
    else{
      num = lengthOfString;
      lengthOfString = 0;
    }
    
    if(num >= 0){
       pos = lettersOf(curr, ans, num, pos);      
    }
    
  }
  printDecompress(ans, length * 4);

  
}

int lettersOf(unsigned char c, char block[], int num,int pos){
  
  for(int i = pos; i < pos + num; i ++){
    unsigned char x  = c & 192;

    if(x == 0){
      
      block[i] = 'A';
    }
    else if(x == 64){
      block[i] = 'T';
    }
    else if(x == 128){
      block[i] = 'C';
    }
    else if(x == 192){
      block[i] = 'G';
    }
    
    c = c << 2;
  }
  return pos + num;

}

void printDecompress(char arr[], int length){
  for(int i = 0; i < length; i ++){
      printf("%c", arr[i]);

  }
  printf("\n");

}

