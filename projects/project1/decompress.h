#ifndef DECOMPRESS_H
#define DECOMPRESS_H

//the main funtion that compresses the method                                                                                                                                                                      
void decompress(int [], int, int);

//updates the "block" of letters into the answer that is represented by the integer and returns the position the block finished at
int lettersOf(unsigned char, char[], int, int);

//prints the deompress char array and takes in the length of the array
void printDecompress(char[], int);


#endif
