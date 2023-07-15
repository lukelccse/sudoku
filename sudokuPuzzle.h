/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuPuzzle.h
 * DESC: contains the sudokupuzzle class header file
 ********************/

#ifndef SUDOKUPUZZLE
#define SUDOKUPUZZLE
#include "move.h"
#define SIZE 9
#define SUB_SIZE 3

class SudokuPuzzle {
    private:
        int grid[SIZE][SIZE];
        Move* prev_move;
        bool isValid(int row, int column, int value);
        bool isRowValid(int row, int value);
        bool isColumnValid(int column, int value);
        bool isSubGridValid(int row, int column, int value);
        void getSubgrid(int row, int column, int (&sub_grid_numbers)[SUB_SIZE*SUB_SIZE]);
        void addHistory(int row, int column, int new_value, int old_value);
        void removeHistory(Move* move);
    public:
        SudokuPuzzle();
        SudokuPuzzle(SudokuPuzzle& newPuzzle);
        ~SudokuPuzzle();
        int add(int row, int column, int value);
        void clear();
        void undo();
        int getCoordinate(int row, int column);
};
#endif