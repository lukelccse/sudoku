/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 31.07.23
 * FILE: SudokuSolver.cpp
 * DESC: SudokuSolver implementation
 ********************/

#include <iostream>
#include "SudokuSolver.h"

/* Backtracking Algorithm Method
 1. Try a number for an unnasigned grid value. 
    If a number can be placed, see if there is a solution 
    for the remaining puzzle.
 2. If no solution exists, try a different number.
 3. If no trials are successful, there is no solution for the puzzle.
*/

// Find an unassinged coordinates and set row and column.
void SudokuSolver::findUnnasngedCoordinates(int &row, int &column){
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            if (sudokuPuzzle.getValue(i, j) == UNNASINGED){
                row = i; column = j;
                return;
            }
        }
    }
};

// Solves the sudoku puzzle using backtracking.
bool SudokuSolver::backtrackingSolve(){
    int row = -1;
    int column = -1;
    /*How can we improve on this backtracking?*/
    //findUnnasngedCoordinates(row, column);
    sudokuPuzzle.getOptimalCoordinates(row, column);

    //puzzle is solved
    if (row == -1 && column == -1){return true;}

    for (int trial=1; trial<=SIZE; trial++){
        if (sudokuPuzzle.add(row, column, trial) == 0){
            if(backtrackingSolve()) {
                return true;
            }
        }
    }
    sudokuPuzzle.add(row, column, UNNASINGED);
    return false;
};

// Solves the sudokupuzzle.
bool SudokuSolver::solve() {
    return backtrackingSolve();
};