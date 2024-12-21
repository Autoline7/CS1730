Name: Diego Sanchez-Carapia
Student Number: 811568813

1. Compile the program using the following commands: 

   make
   
2. Run the program using the following command:

   make run


Explanation on why the time for Step 1 and 2 are different

Step 1 is usually slower because it writes each difference immediately, causing many I/O operations, which are slow. Also reading 1 byte of a time increases the amount of system calls. Step 2 has memory allocations which is also slow but it's not as slow as making so many system calls since it only calls a write call once.
