/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuCLI.h
 * DESC: contains the sudoku CLI
 ********************/

#ifndef SUDOKU_CLI
#define SUDOKU_CLI
#include "sudoku.h"
class SudokuCLI {
    private:
        SudokuPuzzle &sudokuPuzzle;
    public:
        SudokuCLI(SudokuPuzzle &sudoku):sudokuPuzzle(sudoku) {}
        void display();
        void clear();
};
#endif