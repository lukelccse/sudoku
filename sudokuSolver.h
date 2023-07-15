/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuSolver.h
 * DESC: contains the sudokupuzzle header file
 ********************/

#ifndef SUDOU_SOLVER
#define SUDOU_SOLVER
#define SIZE 9
#define SUB_SIZE 3
#define UNNASINGED 0
#define N_COORDINATES 2
#include "sudokuPuzzle.h"

class SudokuSolver {
    private:
        void findUnnasngedCoordinates(SudokuPuzzle &sudokuPuzzle, int &row, int &column);
        bool backtrackingSolve(SudokuPuzzle &sudokuPuzzle);
    public:
        SudokuPuzzle &sudokuPuzzle;
        SudokuSolver(SudokuPuzzle &sudoku):sudokuPuzzle(sudoku) {}
        bool solve(); 
};
#endif