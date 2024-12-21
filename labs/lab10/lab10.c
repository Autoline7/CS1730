#include <stdio.h>///print f
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>//wait
#include <unistd.h>


//main method to guide the program to succesfully use fork,execve, and wait
int main(int argc, char * argv[]){
  int parentID = getpid();// get the parent process ID
  printf("The parent’s PID is %d.\n", parentID);

  printf("The parent is now forking.\n");
  int pid = fork();// create a new process

  long int input = atol(argv[1]);// convert the input argument to an integer
  
  int childPID = 0;
  if(pid == 0){// check if it's the child process
    childPID = getpid();// get the child process ID
    printf("The child’s PID is %d.\n", childPID);
    printf("The child is executing ps.\n");



    // the path to the 'ps' executable
    char *pathname = "/bin/ps";

    // arguments array for 'ps'                                                                                                                                                   
    char *args[] = {"ps", NULL};  // "ps -ef" command                                                                                                                                                               

    // environment variables array                                                                                                                                                      
    char *env[] = {NULL};

    // call execve to execute 'ps'                                                                                                                                                                 
    if (execve(pathname, args, env) == -1) {
        printf("execve error\n");  // print error if execve fails                                                                                                                                                   
        return 0;
    }
  }
  int status;
  wait(&status);// parent waits for the child process to complete

  printf("The parent waited patiently for its child to complete.\n");

    // check if the correct argument count is provided
    if (argc < 2) {
        printf("Usage: ./parent <countdown_time>\n");
        return 1;
    }

  

  printf("The parent is executing ./countdown.out %lu.\n", input);

// specify the path to the 'countdown.out' executable
  char *pathname = "/home/myid/ds28735/cs1730/lab10/countdown.out";
                                                                                                                                                                                            
  // args array for calling the coundown                                                                                                                                                                           
  char *args[] = {"./countdown", argv[1],  NULL};  // "ps -ef" command
  // environment variables array                                                                                                                                                  
  char *env[] = {NULL};
  // call execve to execute countdown executable                                                                                                                                                                 
  if (execve(pathname, args, env) == -1) {
    printf("execve error\n");  // print error if execve fails                                                                                               
   return 0;
  }

  return 0;
}
