#include <stdio.h> //printf
#include <stdlib.h> //atoi, atof, atol
#include <string.h> //strlen

//prints the final statement in correct order
void printOnScreen(long int first, long int second, char binaryFirst[], char binarySecond[], int distance);

//converst integer to binary and changes the value of binaryX
void binary(long int first, char binary[]);

//adds leadingZeroes to make the String the same length
void addLeadingZeroes(int numberOfZeroes, char binary[]);

//return the hamming distance (count of numbers that differ in each position)
int hammingDistance(char x[], char y[]);

//main takes in 2 parameters CONTINUE FILLING COMMENTS
int main(int argc, char * argv[]){
  //input from command line
  long int firstInput = atol(argv[1]);
  long int secondInput = atol(argv[2]);

  //stores the binary outputin a char array
  char binaryFirst[64] = {0};
  char binarySecond[64] = {0};

  //changes the char array to the binary form of the input
  binary(firstInput,binaryFirst);
  binary(secondInput,binarySecond);

  //lengths of the chasr arrays
  int firstLen = strlen(binaryFirst);
  int secondLen = strlen(binarySecond);

  //number of zeroes
  int numberOfZeroes = 0;

  //determines which char array needs leading zeroes and add them
  if(firstLen > secondLen){
    
    numberOfZeroes = firstLen-secondLen;
    addLeadingZeroes(numberOfZeroes,binarySecond);
  }
  if(secondLen > firstLen){
    numberOfZeroes = secondLen-firstLen;
    addLeadingZeroes(numberOfZeroes,binaryFirst);
  }


  //returns the hamming distance to an int
  int distance = hammingDistance(binaryFirst,binarySecond);

  //prints everything on screen
  printOnScreen(firstInput, secondInput, binaryFirst, binarySecond, distance);

  return 0;
}

int hammingDistance(char x[], char y[]){
  int count = 0;
  for(int i = 0; i < strlen(x); i ++){
    if(x[i] != y[i]){
      count++;
    }
  }
  return count;

}




void printOnScreen(long int first, long int second, char binaryFirst[], char binarySecond[], int hdistance){                                                                                               
  printf("%s is the bit string for %li\n", binaryFirst, first);
  printf("%s is the bit string for %li\n", binarySecond, second);
  printf("%i is the Hamming distance between the bit strings\n", hdistance);                                                                                                                                              
  }

void addLeadingZeroes(int numberOfZeroes, char binary[]){
  int len = strlen(binary);
  for (int i = len; i >= 0; i--) {  // shift the numbers to fit leading zeroes
        binary[i + numberOfZeroes] = binary[i];
    }
  for (int i = 0; i < numberOfZeroes; i++) {//insert leading zeroes
        binary[i] = '0';
    }

}

void  binary(long int n, char binary[]){
  int bit[64] = {0};
  int bitIndex = 0;
  int remainder = 0;

  if(n == 0){;
    binary[0] = '0';
    binary[1] = '\0';
  }
  
  while(n > 0){
    remainder = n % 2;
    n /= 2;
    bit[bitIndex] = remainder;
    bitIndex++;
  }

  int j = 0;
  for(int i = bitIndex - 1; i >= 0; i--){
    if(bit[i] == 1){
      binary[j] = '1';
    }
    else{
      binary[j] = '0';
    }
    j++;
  }
  binary[j] = '\0';
}
