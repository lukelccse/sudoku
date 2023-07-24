/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 23.07.23
 * DATE MODIFIED: 23.07.23
 * FILE: sudokuCreator.cpp
 * DESC: contains the sudokuCreator header
 ********************/

#ifndef SUDOKUCREATOR
#define SUDOKUCREATOR
#include "sudokuPuzzle.h"
#include "sudokuSolver.h"
#define SIZE 9
#define SUB_SIZE 3
#define UNASSINGED 0
class SudokuCreator {
    public:
        SudokuCreator();
        void getNewPuzzle(SudokuPuzzle &new_puzzle, char difficuilty_lvl);
    private:
        bool holes[SIZE][SIZE];
        void generateSudoRandomGrid(SudokuPuzzle &new_puzzle);
        void digHoles(SudokuPuzzle &puzzle, int N);
        void getCoordinates(int &row, int &column);
        bool uniqueSolution(SudokuPuzzle &puzzle, int row, int column);
};
#endif