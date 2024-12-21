#include <stdio.h>//print f                                                                                                                                                                                         
#include <stdlib.h>//atoi atol atof                                                                                                                                                                                 
#include <string.h> //strlen strcmp                                                                                                                                                                                 
//prints everything on the screen
void printOnScreen(char *binaryFirst, char operator, char *binarySecond, char *binaryAns, int length, unsigned long long int value1, unsigned long long int value2, unsigned long long int valueAns);

//does the operation that the user inputted
int operate(unsigned long long int binaryFirst, char operator, unsigned long long int binarySecond);

//adds leading zeroes to the bitstring with a shorter length
void addLeadingZeroes(int numberOfZeroes, char * s);

//converts a binary to int
void binary(long int n, char binary[]);

//converst a binary to int
int binaryToInt(const char * binary);

//main method
int main(int argc, char * argv[]){

  //stores the 2 bit strings the user inputted
  char first[64], second[64];
  strcpy(first, argv[1]);
  strcpy(second, argv[3]);

  //gets the length of the bitstrings 
  int firstLen = strlen(first);
  int secondLen = strlen(second);


  //determines the number of zeroes needed to add for the shortest bit string
  int numOfZeroes = 0;
  if(firstLen > secondLen){
    numOfZeroes = firstLen - secondLen;
    addLeadingZeroes(numOfZeroes, second);
  }
  if(firstLen < secondLen){
    numOfZeroes = secondLen - firstLen;
    addLeadingZeroes(numOfZeroes,first);
  }

  //stores and calls the users inputs to become ints
  int value1 = binaryToInt(first);
  int value2 = binaryToInt(second);

  //determines what bitwise operation to operate
  char c;
  if(strcmp(argv[2],"-and") == 0){
    c = '&';
  }
  else if (strcmp(argv[2],"-or") == 0){
    c = '|';
  }
  else if (strcmp(argv[2],"-xor") == 0){
    c = '^';
  }

  //stores the answer after the bitwise operation
  int ans = operate(value1,c,value2);

  //used to store the binary value of the answer
  char ansChar[64];
  binary(ans, ansChar);

  //if the answers is a shorter bit length than the others it adds leading zeroes
  if(strlen(ansChar) < strlen(first)){
    numOfZeroes = strlen(first)- strlen(ansChar);
    addLeadingZeroes(numOfZeroes, ansChar);

  }

  //gets the length of the the first even after its modifies so all are the same size
  int length = strlen(first);

  //prints everythin on the screen
  printOnScreen(first, c, second, ansChar, length, value1, value2, ans);

  //successful execution
  return 0;
}


void binary(long int n, char binary[]) {
    int bit[64] = {0};
    int bitIndex = 0;
    int remainder = 0;

    if (n == 0) {
        binary[0] = '0';
        binary[1] = '\0';
        return;
    }

    // Convert the number to binary and store bits in the bit array                                                                                                                                                 
    while (n > 0) {
        remainder = n % 2;
        n /= 2;
        bit[bitIndex] = remainder;
        bitIndex++;
    }

    // Write the binary result into the binary[] char array  
    int j = 0;
    for (int i = bitIndex - 1; i >= 0; i--) {
        if (bit[i] == 1) {
            binary[j] = '1';
        } else {
            binary[j] = '0';
        }
        j++;
    }
    binary[j] = '\0';
}


int binaryToInt(const char *binary){
  int ans = 0;
  int base = 1;
  int len = strlen(binary);
  for (int i = len - 1; i >= 0; i--) {
    if (binary[i] == '1') {
        ans += base;
    }
    base *= 2;
  }
  return ans;
}


//return a string that eveluates the inout with the bitwise operator                                                                                                                                                
int operate(unsigned long long int binaryFirst, char operator, unsigned long long int binarySecond){
  int ans;
  if(operator == '&'){
    ans  = binaryFirst & binarySecond;
  }
  else if(operator == '|'){
    ans  = binaryFirst | binarySecond;
  }
  else if(operator == '^'){
    ans  = binaryFirst ^ binarySecond;

  }
  return ans;
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


void printOnScreen(char * binaryFirst, char operator, char * binarySecond, char * binaryAns, int length, unsigned long long int value1,unsigned long long int value2, unsigned long long int valueAns){
  printf("%s %c %s evaluates to %s using bit strings of length %i\n",binaryFirst, operator, binarySecond, binaryAns, length);
  printf("%llu %c %llu evaluates to %llu using unsigned %i-bit integers\n", value1, operator,value2, valueAns, length);

}
