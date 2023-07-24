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
        void shuffle(SudokuPuzzle &puzzle);
    private:
        bool holes[SIZE][SIZE];
        void generateSudoRandomGrid(SudokuPuzzle &new_puzzle);
        void randomiseArray(int (&array)[SIZE]);
        void digHoles(SudokuPuzzle &puzzle, int N);
        void getCoordinates(int &row, int &column);
        bool uniqueSolution(SudokuPuzzle &puzzle, int row, int column);
        void fillGrid(SudokuPuzzle &puzzle, int (&grid)[SIZE][SIZE]);
        void fillSudoku(SudokuPuzzle &puzzle, int (&grid)[SIZE][SIZE]);
        void twoDigitsPropagation(int (&grid)[SIZE][SIZE]);
        void swapValues(int (&grid)[SIZE][SIZE], int value_one, int value_two);
        void swapColumnsPropagation(int (&grid)[SIZE][SIZE]);
        int randomSubSizeNumber();
        void swapColumns(int (&grid)[SIZE][SIZE], int column_one, int column_two);
        void swapBlocksPropagation(int (&grid)[SIZE][SIZE]);
        void gridRollPropagation(int (&grid)[SIZE][SIZE]);
        void rotateGrid(int (&grid)[SIZE][SIZE]);

};
#endif