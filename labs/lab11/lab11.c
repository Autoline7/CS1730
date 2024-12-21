#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

//prints the initial statements of the program
void printStart(long int id);

//handler for signal kill -8
void  handler1(int signum);

//handler for signal kill -10
void  handler2(int signum);

//handler for signal kill -12
void handler3(int signum);

//prints the sum
void printSum();


//sum for the double input.Its global because the sum method needs access
double sum = 0;

//id for the current process.Its global because the handler needs access  
long int id = -1;

//main method used to start the program and scan until a kill command kills the process
int main(int argc, char * argv[]){
  id = getpid();
  printStart(id);//prints the start
  int count = 0;//counts the number of valid inputs
  double num = 0;//stores the current input
  int x = 0;//stores what scanf returns incase of a failure
  char ch;//to clear the buffer
  //kill -8
  signal(SIGFPE, handler1);
  //kill -10
  signal(SIGUSR1, handler2);
  //kill -12
  signal(SIGUSR2, handler3);
  
  while(1){//run as long as kill or sleep isn't run
    x = scanf("%lf", &num);
    if(x == 0){//not a double
      printf("Error: please input a numeric value.\n");
      while ((ch = getchar()) != '\n' && ch != EOF);
    }
    else if(x == 1){//adds the sum
      count++;
      sum += num;
    }
    else {//sleeps once scanf reached the end of file
      sleep(60);
      printSum();
      printf("Program ended after sleeping for 60 seconds.\n");
      exit(0);
      
    }
  }
  return 0;
}

void handler1(int signum){
  printSum();
  printf("Program ended by handling the signal from kill -8 %lu.\n", id);
  exit(0);
}
void handler2(int signum){
  printSum();
  printf("Program ended by handling the signal from kill -10 %lu.\n", id);
  exit(0);
}
 
void handler3(int signum){
  printSum();
  printf("Program ended by handling the signal from kill -12 %lu.\n", id);
  exit(0);
}

void printSum(){
  printf("The sum is %.6f.\n",sum);
}

void printStart(long int id){
  printf("Program started with pid = %lu.\nEnter a list of doubles to sum,\nand to end the program,\nrun one of the following Unix commands: \n  kill -8 %lu \n  kill -10 %lu \n  kill -12 %lu\n", id,id,id,id);
}
