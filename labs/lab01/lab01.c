#include <stdio.h>
#include <stdlib.h>

typedef struct {
    short y;
    short z;
} x;

int main(void) {
    short k = 4;
    x ***a = (x ***) malloc(2 * sizeof(x **));
    
    for (int p = 0; p < 2; p++) {
        *(a + p) = (x **) malloc(3 * sizeof(x *));
        for (int i = 0; i < 3; i++) {
            *(*(a + p) + i) = (x *) malloc(3 * sizeof(x));
            for (int j = 0; j < 3; j++) {
                (*(*(*(a + p) + i) + j)).y = (short) k + 1;
                (*(*(*(a + p) + i) + j)).z = (short) k + 2;
                k += 3;
            }
        }
    }

    printf("%ld\n", sizeof(x));             // 1. _______________
    printf("%hd\n", a[0][0][2].y);          // 2. _______________
    printf("%hd\n", a[0][1][2].z);          // 3. _______________
    printf("%hd\n", a[1][0][1].y);          // 4. _______________
    printf("%hd\n", a[1][1][1].z);          // 5. _______________
    
    return 0;
}

/*//Tells compiler the information for printf()
#include <stdio.h>

//Main Function that return an int and takes no arguments
int main(void)
{
  //print the message and "\n" is the new line character
  printf("Hello World!\nI setup my odin to use gcc and g++ version 11.2.0.\nI practiced using basic Unix commands.\n");
  //returns an int and '0'indicates the program ran succesfully
  return 0;
/*/
