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
#include "counter.h"
#define SIZE 9
#define SUB_SIZE 3
#define UNASSINGED 0

class SudokuPuzzle {
    private:
        int grid[SIZE][SIZE];
        Move* prev_move;
        Counter row_counter; Counter column_counter;
        Counter counters[2] = {row_counter, column_counter};
        void initialiseCounters();
        bool isValid(int row, int column, int value);
        bool isRowValid(int row, int value);
        bool isColumnValid(int column, int value);
        bool isSubGridValid(int row, int column, int value);
        void getSubgrid(int row, int column, int (&sub_grid_numbers)[SUB_SIZE*SUB_SIZE]);
        void addHistory(int row, int column, int new_value, int old_value);
        void removeHistory(Move* move);
        void removeAllHistory();
        void updateCounters(int row, int column, int new_value, int old_value);
        void incrementCounter(Counter &counter, int index);
        void deincrementCounter(Counter &counter, int index);
        void findNewMax(Counter &counter);
    public:
        SudokuPuzzle();
        SudokuPuzzle(SudokuPuzzle& newPuzzle);
        ~SudokuPuzzle();
        int add(int row, int column, int value);
        void clear();
        void undo();
        int getValue(int row, int column);
        void getOptimalCoordinates(int &row, int&column);
};
#endif