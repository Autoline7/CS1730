#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compress.h"
#include "decompress.h"

int main(int argc, char * argv[]){
  char func[strlen(argv[1])];
  char input[strlen(argv[2])];
  strcpy(func,argv[1]);//copies the value in argv[1] to func 
  strcpy(input,argv[2]);//copies the value in argv[2] to input
  int length = argc-3;
  int input2[length];
  int lengthOfString = atoi(argv[2]);
  //copies the values from the command line and adds it to input2
  for(int i = 0; i < argc - 3 ; i ++){
    input2[i] = atoi(argv[i + 3]);
  }
  //determines what operation they wanted
  if(strcmp(func, "-c") == 0){
    compress(input);
  }
  if(strcmp(func, "-d") == 0){
    decompress(input2, length, lengthOfString);
  }
  return 0;
}
