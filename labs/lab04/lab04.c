#include<stdio.h>//print f 
#include<stdlib.h>///atoi atol atof   
#include<string.h>//strlen strcmp 

//prints everything on the screen for the Negation Operator
void printOnScreenNeg(char[], char, char[], int, int, int);
//prints everything on the screen for the Shift Operator       
void printOnScreenShift(char[], char[], char[], int, char[], int, int, int);

//converts an int to binary
void toBinary(int, char[]);

//return an int thats been converted form a binary char
int base10(char[]);

//makes sure it has k characters
void onlyKCharacters(int, char[], char[]);

//main method
int main(int argc, char * argv[]){

  //this 2 variables are for the '~' operator
  char binary[64] = {0};
  char c = 'N';

  //this 3 variables are for the shift  operator 
  char binaryFirst[64] = {0};
  int numOfShifts = 0;
  char operator[] = "!!";

  //determines what operator to use and then saves the input value to a variable
  if(strcmp(argv[1], "-not") == 0){
      c = '~';
      strcpy(binary, argv[2]);//copies the value in argv[2] to binary                                                                                     
  }
  else{
    if(strcmp(argv[2], "-leftshift") == 0){
      operator[0] = '<';
      operator[1] = '<';
      operator[2] = '\0';
    }
    if(strcmp(argv[2], "-rightshift") == 0){
      operator[0] = '>';
      operator[1] = '>';
      operator[2] = '\0';
    }
    strcpy(binaryFirst, argv[1]);//copies the value in argv[1] to binary
    numOfShifts = atoi(argv[3]);//copies the value in argv[3] to an int     
   }

  //does all the work for the negation operator
  
  if(c == '~'){
    int length = strlen(argv[2]);//length of the input
    int value1 = base10(binary);//convers the input to base10

    int ans1 = ~value1;//negates the input
    
    char binaryAns1[64] = {0};//stores the binarychar for the input
    toBinary(ans1, binaryAns1);//converts the integer to binaty and uses the binarayAns1
    
    char finalAns[length];//stores the answer of the negation bu with the correct length
    onlyKCharacters(length,finalAns, binaryAns1);//makes sure it has same amount of characters
    int valueAns = base10(finalAns); //converts the given binary with a certeain amount of bits and converst it to integer
    printOnScreenNeg(binary, c, finalAns, length, value1, valueAns);//prints on the screen
  }
  //does the work for the shift operators
  else{
    int length = strlen(argv[1]);//length of the input
    int value1 = base10(binaryFirst);//convers the input to base10 
    
    int ans1 = 0;
    //determines what operation to use
    if(strcmp(operator, "<<") == 0){
      ans1 = value1 << numOfShifts;
      
    }
    if(strcmp(operator, ">>") == 0){
      ans1 = value1 >> numOfShifts;
    }

    
    char numOfShiftsBinary[64] = {0}; //stores the numOfShiftschar[] for the input to convert to binary
    toBinary(numOfShifts, numOfShiftsBinary);//converts the numofShifts to binary and stores it in the given array

    char finalNumOfShiftsBinary[64] = {0};//stores the answer of the negation bu with the correct number of bits
    onlyKCharacters(length, finalNumOfShiftsBinary, numOfShiftsBinary);//makes sure it has same amount of characters 
    
    char binaryAns1[64] = {0};//stores the binarychar for what the shift operator resulted in
    toBinary(ans1, binaryAns1);//converts the ans1 to binary and stores it in the given array 

    
    char finalAns[length];//stores the finalAnschar for the correctlength 
    onlyKCharacters(length,finalAns, binaryAns1);//makes sure it has same amount of characters 

    
    int valueAns = base10(finalAns);//converts the fianl answer to base 10 with the given bits
    //prints for the shift operator
    printOnScreenShift(binaryFirst, operator, finalNumOfShiftsBinary, numOfShifts, finalAns, length, value1, valueAns);
  }

  return 0;//succesful
}


void onlyKCharacters(int lengthNeeded, char finalAns[], char binary[]) {
    int totalLen = strlen(binary);  // Length of the binary result to copy from

    // Initialize finalAns with all '0's
    for (int i = 0; i < lengthNeeded; i++) {
        finalAns[i] = '0';
    }
    finalAns[lengthNeeded] = '\0';  // Null-terminate finalAns

    // Copy the relevant portion of binary to finalAns, aligned to the right
    int j = lengthNeeded - 1;
    for (int i = totalLen - 1; i >= 0 && j >= 0; i--, j--) {
        finalAns[j] = binary[i];  // Copy from the end of binary to the end of finalAns
    }
}



//converts a char[] to an int
int base10(char binary[]){
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

void toBinary(int n, char binary[]) {
    int bit[64] = {0};
    int bitIndex = 0;
    int remainder = 0;

    if (n == 0) {
        binary[0] = '0';
        binary[1] = '\0';
        return;
    }

    // Convert the number to binary and store bits in the bit array
    unsigned int un = (unsigned int)n;
    while (un > 0) {
        remainder = un % 2;
        un /= 2;
        bit[bitIndex] = remainder;
        bitIndex++;
    }

    // Write the binary result into the binary[] char array  
    int j = 0;
    for (int i = bitIndex - 1; i >= 0; i--) {
        binary[j++] = bit[i] + '0';  // Convert int to char
    }
    binary[j] = '\0'; 
}








void printOnScreenNeg(char binary[], char operator, char  binaryAns[], int length, int value1, int valueAns){
  printf("%c%s evaluates to %s using bit strings of length %i\n",operator, binary, binaryAns, length);
  printf("%c%i evaluates to %i using unsigned %u-bit integers\n", operator, value1, valueAns, length);

}

void printOnScreenShift(char binaryFirst[], char operator[], char binaryAns[],int numOfShifts, char  finalAns[], int length, int value1, int valueAns){
  printf("%s %s %s evaluates to %s using bit strings of length %i\n",binaryFirst, operator, binaryAns, finalAns, length);
  printf("%i %s %i evaluates to %i using unsigned %i-bit integers\n", value1, operator, numOfShifts , valueAns, length);

}
