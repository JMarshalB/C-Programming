To compile the program:
- Run make, to compile all the files.
- Make sure to include main.c, readerwriter.c, and readerwriter.h on the same directory.
- Alternatively, could also run gcc -o rwmain main.c readerwriter.c -l pthread.

To run the program:
- Include scenarios.txt to run an scenario for the program.
- In addition, you could modify that scenario to test other scenarios (1 scenario per run). 
- run ./rwmain to see the result.

$ make
gcc     -o      rwmain  main.c  readerwriter.c  -l      pthread

./rwmain
