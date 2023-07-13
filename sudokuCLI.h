/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuCLI.h
 * DESC: contains the sudoku CLI
 ********************/

#ifndef SUDOKU_CLI
#define SUDOKU_CLI
#include <string>
#include <iostream>
#include "sudokuPuzzle.h"
class SudokuCLI {
    private:
        SudokuPuzzle &sudokuPuzzle;
        void display();
        void clear();
        std::string prompt();
    public:
        SudokuCLI(SudokuPuzzle &sudoku):sudokuPuzzle(sudoku) {}
        void run();
};
#endif