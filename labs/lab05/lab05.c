#include<stdio.h>//print f 
#include<stdlib.h>///atoi atol atof   
#include<string.h>//strlen strcmp
//makes sure it has k characters
void onlyKCharacters(int, char[], char[]);
//converts an int to binary
void toBinary(int, char[]);
//prints on screen or decimal or bits
void printOnScreenDB(int , char[], int);
//prints everything on the screen for the binary
void printOnScreenBinary(int, char[], int);
//return an int thats been converted form a binary char
int base10(char[]);

//main method
int main(int argc, char * argv[]){
  char type[strlen(argv[1])];//works for deciaml, bits or binary                                                                                                                                                  
  strcpy(type,argv[1]);



  //first input is -decimal                                                                                                                                                                                      
  if(strcmp(type,"-decimal") == 0){
    int num = atoi(argv[2]);
    char type2[strlen(argv[3])];//works for deciaml, bit                                                                                                                                                         
    strcpy(type2,argv[3]);
    int length = atoi(argv[4]);//works for deciaml, bits
    char binary[length];
    toBinary(num, binary);
    char binaryAns[length];//stores tha binary answer for the correct length    WORKS
    onlyKCharacters(length, binaryAns, binary);
    printOnScreenDB(num,binaryAns,length); //WORKS
  }
  
  //first input is -bits
  if(strcmp(type,"-bits") == 0){
    int length = atoi(argv[2]);
    char type2[strlen(argv[3])];//works for deciaml, bit                                                                                                                                                         
    strcpy(type2,argv[3]);
    int num = atoi(argv[4]);//works for deciaml, bits 
    char binary[length];
    toBinary(num, binary);
    char binaryAns[length];//stores tha binary answer for the correct length    WORKS                                                                                                                            
    onlyKCharacters(length, binaryAns, binary);
    printOnScreenDB(num,binaryAns,length); //WORKS      
  }
 
  
  //first input is -binary                                                                                                                                                                                         
  if(strcmp(type,"-binary") == 0){
    char binaryInput[strlen(argv[2])];
    strcpy(binaryInput,argv[2]);
     char binaryInputFinalAns[strlen(argv[2])];
    onlyKCharacters(strlen(argv[2]), binaryInputFinalAns, binaryInput);
    
    int ans = base10(binaryInput);
    if(binaryInputFinalAns[0] == '1'){
      ans *= -1;
      ans -= 1;
    }
    printOnScreenBinary(ans,binaryInputFinalAns,strlen(argv[2]));

    

  }
  return 0;

}

//converts a char[] to an int
int base10(char binary[]){
  int len = strlen(binary);

  //flips 1 and 0s
  if(binary[0] == '1'){
    for(int i = 0; i < len; i ++){
      if(binary[i] == '1'){
	binary[i] = '0';
      }else{
	binary[i] = '1';
      }
    }
  }
  
  int ans = 0;
  int base = 1;

  for (int i = len - 1; i >= 0; i--) {
    if (binary[i] == '1') {
        ans += base;
    }
    base *= 2;
  }
  return ans;

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

void printOnScreenDB(int value1, char binaryAns[], int length){
  printf("%i in decimal is equal to %s in binary using %i-bit two’s complement representation\n", value1, binaryAns, length);

}

void printOnScreenBinary(int value1, char binaryAns[], int length){
  printf("%s in binary is equal to %i in decimal using %i-bit two’s complement representation\n" , binaryAns, value1, length);

}


