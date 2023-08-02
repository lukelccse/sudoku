/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 31.07.23
 * FILE: SudokuPuzzle.h
 * DESC: SudokuPuzzle header file
 ********************/

#ifndef SUDOKUPUZZLE
#define SUDOKUPUZZLE
#include "move.h"
#include "counter.h"
#define SIZE 9
#define SUB_SIZE 3
#define UNASSINGED 0
#define N_COUNTERS 2

class SudokuPuzzle {
    private:
        int grid[SIZE][SIZE];
        bool frozen[SIZE][SIZE];
        Move* prev_move;
        Counter counters[N_COUNTERS];
        bool record_history;
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
        bool isFrozen(int row, int column);
    public:
        SudokuPuzzle();
        SudokuPuzzle(SudokuPuzzle &other);
        ~SudokuPuzzle();
        int add(int row, int column, int value);
        void clear();
        void reset();
        void undo();
        int getValue(int row, int column);
        void getOptimalCoordinates(int &row, int&column);
        void startRecordingHistory();
        void stopRecordingHistory();
        void freezePuzzle();
};
#endif