#include <stdio.h>////print f
#include <string.h>//strlen strcmp
#include <stdlib.h>///atoi atol atof

//prints all statements fro doubles
void printStatementsD(double x, char binary[],char binary2[], char binary3[], int sign, int bits, int frac, int ex);

//prints all the statements for floats
void printStatementsF(double x, char binary[],char binary2[], char binary3[], int sign, int bits, int frac, int ex);

//converts the double/float to binary
void toBinaryF(float input, char binary[]);

//converts the double/float to binary                                                                                                                                                                              
void toBinaryD(double input2, char binary[]);

//main method, starts by reading the arguments and determining what methods to use
int main(int argc, char * argv[]){
  char type[strlen(argv[1])];//place to store a copy of argv[1]                                                                                                                                                  
  strcpy(type,argv[1]);
  
  //first input is -f                                                                                                                                                                                     
  if(strcmp(type,"-f") == 0){
    float f = (float)atof(argv[2]);
    int sign = 0;//sign of the first bit
    if(f < 0){
      sign = 1;
    }
    char binary1[33];//the 32 bit representation
    toBinaryF(f,binary1);//converts f to binary and holds it in binary1
    binary1[32] = '\0';
    //crops based on index
    char binary8[9];//hold the 8 bit part of the exponent
    //copies the substring starting from index 1 until length is 8
    strncpy(binary8, binary1+1, 8);
    binary8[8] = '\0';
    char binary23[24];
    //copies the substring starting from index 9 until length is 23                                                                                                                                                
    strncpy(binary23, binary1+9, 23);
    binary23[23] = '\0';
    printStatementsF(f,binary1,binary8,binary23, sign, 32, 23, 8); //prints the statements 
  }

  //if the input is -d
  if(strcmp(type,"-d") == 0){
    double d = atof(argv[2]);
    int sign = 0;
    if(d < 0){
      sign = 1;
    }
    char binary1[65];//64 bit representation
    toBinaryD(d,binary1);//converts d to binary and hold it in binary1
    printf("%s\n", binary1);
    binary1[64] = '\0';
    //crops based on index
    char binary11[12];
    //copies the substring starting from index 1 until length is 8                                                                                                                                                
    strncpy(binary11, binary1+1, 11);
    binary11[11] = '\0';
    char binary52[53];
    //copies the substring starting from index 9 until length is 23                                                                                                                                                
    strncpy(binary52, binary1+12, 52);
    binary52[52] = '\0';
    printStatementsD(d,binary1,binary11,binary52, sign, 64, 52, 11);//prints the statements
  }


 
  
  //returns 0 because main returns an int
  return 0;

}


void toBinaryF(float input, char binary[]) {

  unsigned int  n;
    // Use a union to access the bit-level representation of the float
    //used to convert a float to an int since it uses the same memory
    union {	                                                                                                                                                                                                   
      unsigned int x;    //unsigned int to store the bits in an integer data type and then convert                                                                                                                                                                                     
      float f;          //float to store the input
    } cov;
    cov.f = input;
    n = cov.x;

    // Convert the number to a 32-bit binary string
    for (int i = 31; i >= 0; i--) {
        binary[31 - i] = (n & (1 << i)) ? '1' : '0';
    }
    binary[32] = '\0';  // Null-terminate the binary string
}

void toBinaryD(double input2, char binary[]) {

  unsigned long long n;
  // Use a union to access the bit-level representation of the double 
  //used to convert a double to an int since it uses the same memory
    union {
      unsigned long long x;   //unsigned long long to store the bits in an integer data type and then convert
      double d;               //double to store the input
    } cov;
    cov.d = input2;
    n = cov.x;

    // Convert the number to a 64-bit binary string                                                                                                                                                                 
    for (int i = 63; i >= 0; i--) {//ULL is using an 1 as an unsigned long long
        binary[63 - i] = (n & (1ULL << i)) ? '1' : '0';
    }
    binary[64] = '\0';  // Null-terminate the binary string                                                                                                                                                         
}

void printStatementsD(double x, char binary[],char binary2[], char binary3[], int sign, int bits, int frac, int ex){
  printf("%.6f encoded in binary using a %i bit IEEE 754 encoding is below.\n%s\n",x, bits, binary);
  printf("sign bit:          %i\n",sign);
  printf("exponent (%i bit): %s\n", ex, binary2);
  printf("fraction (%i bit): %s\n", frac, binary3);
}

void printStatementsF(double x, char binary[],char binary2[], char binary3[], int sign, int bits, int frac, int ex){
  printf("%.6f encoded in binary using a %i bit IEEE 754 encoding is below.\n%s\n",x, bits, binary);
  printf("sign bit:          %i\n",sign);
  printf("exponent (%i bit):  %s\n", ex, binary2);
  printf("fraction (%i bit): %s\n", frac, binary3);
}
