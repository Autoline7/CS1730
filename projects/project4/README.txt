Name: Diego Sanchez-Carapia
Student Number: 811568813

1. Compile the program using the following commands: 

   make
   
2. Run the program using the following command:

   make run


The results show that using multithreading to compute diagonal sums equal to 19 (to keep it consistent) significantly improves performance for larger grids. In small grids like 5x5 or 17x17, the differences between 1, 2, and 3 threads are minimal because the computation time is already very short. However, for larger grids, such as 672x672, the time drops from 0.033796 seconds with 1 thread to 0.012346 seconds with 3 threads. This pattern is even more pronounced in grids like 3567x3567, where the time decreases from 0.950189 seconds with 1 thread to 0.342276 seconds with 3 threads. From my findings I can say multithreading reduces computation time for large-scale projects. Also as the target sum increases the computation time also increases. For example in a 3567x3567, the time increases from 0.342276 seconds with 3 threads with a sum of 19 to 13.491756 seconds with 3 threads with a sum of 1222 . 
