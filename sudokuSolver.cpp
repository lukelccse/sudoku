/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuSolver.cpp
 * DESC: contains the sudokupuzzle functions
 ********************/

#include <iostream>
#include "sudokuSolver.h"

/* Backtracking Algorithm Method
 1. Try a number for an unnasigned grid value. 
    If a number is valid, see if there is a solution for the puzzle.
 2. If no solution exists, try a different number.
 3. If no trials are successful, there is no solution. 
*/

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

bool SudokuSolver::solve() {
    return backtrackingSolve();
};