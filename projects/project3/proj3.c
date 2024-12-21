#include <fcntl.h>   // For open()
#include <stdio.h>   // For printf()
#include <stdlib.h>  // For malloc(), realloc(), free()
#include <sys/stat.h>
#include <sys/time.h>// gettimeofday()
#include <sys/types.h>
#include <unistd.h>  // For read(), write(), close()

#define BUF_SIZE 2  // Read 1 byte at a time, buffer size 2 for null-terminator

//returns -1 incase there is an error and 0 other wise. Compare input files one and two. done by accessing 1 byte at a time from each of the files, comparing them, and writing any byte from
//file one that is not equal to the corresponding byte in file two into the file called differencesFoundInFile1.txt.
int step1(char *file1, char *file2);

/*Compare input files one and two. read both of the files into two dynamically allocated arrays. compares the two arrays and write any byte from file two that is not equal to the corresponding byte
in file one into a third array, and then copy that third array into a file called differencesFoundInFile2.txt.
*/
void step2(char *file1, char *file2);

//starts the prgram and reads in the command arguments and then calls step1 and step2 to find the differences
int main(int argc, char *argv[]) {
    if (argc != 3) {//if there isnt correct num arguments
        printf("Usage: proj3.out <file1> <file2>\n");
        return 0;
    }
    //timing the steps
    struct timeval start, end;
    long seconds, useconds;
    double elapsed1, elapsed2;

    //measure time for Step 1
    gettimeofday(&start, NULL);
    int a = step1(argv[1], argv[2]);
    if(a == -1){
      return 0;
    }
    gettimeofday(&end, NULL);

    //calculate elapsed time for Step 1
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    elapsed1 = (seconds * 1000.0) + (useconds / 1000.0);

    //measure time for Step 2
    gettimeofday(&start, NULL);
    step2(argv[1], argv[2]);
    gettimeofday(&end, NULL);

    //calculate elapsed time for Step 2
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    elapsed2 = (seconds * 1000.0) + (useconds / 1000.0);

    //print the results
    printf("Step 1 took %.6f milliseconds\n", elapsed1);
    printf("Step 2 took %.6f milliseconds\n", elapsed2);

    return 0;
}

int step1(char * file1, char * file2){
  int fd1 = open(file1,O_RDONLY);
  int fd2 = open(file2, O_RDONLY);
  if(fd1 == -1 || fd2 == -1){
    printf("There was an error reading a file.\n");
    return -1;
  }
  char buf1[BUF_SIZE];
  char buf2[BUF_SIZE];
  
  ssize_t numread1 = read(fd1,buf1,BUF_SIZE-1);
  ssize_t numread2 = read(fd2,buf2,BUF_SIZE-1);
  

  int fdDif1 = open("differencesFoundInFile1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);//if file doesn't exist create it & the last parameter is the permissions to read& write for the owner and read-onlyothers. 

  while(numread1 > 0){//check here eventually                                                                                                                                                       
    buf1[numread1] = '\0';
    buf2[numread2] = '\0';

    //for every character check if theres differences and then if there is add it to the new file. dont forget to set it incase the file doenot edxit O CRETE | wr only                                             
    if(buf1[0] != buf2[0]){
      int num_written = write(fdDif1,buf1,BUF_SIZE-1);
      if (num_written == -1) {
                printf("There was an error writing to a file.\n");
                close(fd1);
                close(fd2);
                close(fdDif1);
                return -1;
      }
    }
    numread1 = read(fd1,buf1,BUF_SIZE-1);
    numread2 = read(fd2,buf2,BUF_SIZE-1);


  }
  close(fd1);
  close(fd2);
  close(fdDif1);
  return 0;

}

void step2(char * file1, char * file2){
  int fd1 = open(file1,O_RDONLY);
  int fd2 = open(file2, O_RDONLY);
  char buf1[BUF_SIZE];
  char buf2[BUF_SIZE];

  ssize_t numread1 = read(fd1,buf1,BUF_SIZE-1);
  ssize_t numread2 = read(fd2,buf2,BUF_SIZE-1);

  char * ptr1 = (char *)malloc(BUF_SIZE);//allocated 2 byte of memory 1 for character and the other for the null character                                                                                          
  char * ptr2 = (char *)malloc(BUF_SIZE);//allocated 2 byte of memory 1 for character and the other for the null character                                                                                          

  int pos = 0;
  int capacity = BUF_SIZE;
  ssize_t total = 0;

  while(numread2 > 0){//copies the txt file into a dynamuically stored array                                                                                                                        
    buf1[numread1] = '\0';
    buf2[numread2] = '\0';


    *(ptr1+pos) = buf1[0];
    *(ptr2+pos) = buf2[0];
    pos++;
    if (pos >= capacity - 1 ) {
            capacity += BUF_SIZE;
              char *temp1 = (char *)realloc(ptr1, capacity);
              ptr1 = temp1;
              
             char *temp2 = (char *)realloc(ptr2, capacity);
              ptr2 = temp2;
                  }
    numread1 = read(fd1,buf1,BUF_SIZE-1);
    numread2 = read(fd2,buf2,BUF_SIZE-1);
  }
  total = pos;
  pos = 0;
  int lengthofDiff = 0;
  char * ptr3 = (char *)malloc(capacity);
  while(pos < total){//iterates through the array and checks if the character at position pos is different if so then you write it a dynamically stored array                                                                  
    if(*(ptr1 + pos) != *(ptr2 + pos)){

      *(ptr3 + lengthofDiff) = *(ptr2 + pos);
      lengthofDiff ++;
    }
    pos++;
  }

  int fdDif2 = open("differencesFoundInFile2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);//if file doesn't exist create it & the last parameter is the permissions to read& write for the owner and read-onlyother 
  write(fdDif2, ptr3, lengthofDiff);

  close(fd1);
  close(fd2);
  close(fdDif2);
  free(ptr1);
  free(ptr2);
  free(ptr3);
}
