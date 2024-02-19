Sudoku Validator

This program is designed to validate the solution to a Sudoku puzzle using multithreading in C. It checks whether the given Sudoku solution is valid by examining the rows, columns, and 3x3 subgrids for any duplicate digits.
Usage
Prerequisites

Ensure that you have a C compiler and pthread library installed on your system.
Compilation

Compile the program using your preferred C compiler. For example:


gcc sudoku_validator.c -o sudoku_validator -pthread

Execution

Run the compiled program:

./sudoku_validator

Multithreading Approach

The program utilizes pthreads (POSIX threads) for multithreading. It creates separate threads to validate each row, column, and 3x3 subgrid concurrently, improving the efficiency of the validation process.
