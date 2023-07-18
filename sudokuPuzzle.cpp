
/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuPuzzle.cpp
 * DESC: contains the sudokupuzzle functions
 ********************/
#include <iostream>
#include <string>
#include "sudokuPuzzle.h"

// Constructor.
SudokuPuzzle::SudokuPuzzle() {
    // initialise all grid positions to 0
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++){
            grid[i][j] = UNASSINGED;
        }
    }
    // initialise all Counter values
    initialiseCounters();
    // no history
    prev_move = NULL;
};

// Deconstructor.
SudokuPuzzle::~SudokuPuzzle() {
    removeAllHistory();
};

// Initialise all Counter values.
void SudokuPuzzle::initialiseCounters(){
    for(Counter &counter : counters){
        for(int i=0; i<SIZE; i++){
            counter.counts[i] = 0;
        }
        counter.max = 0;
        counter.index = 0;
        counter.filled = 0;
    }
};

// Adds a value to the sudoku grid.
int SudokuPuzzle::add(int row, int column, int value){
    //check for valid coordinates and value
    if ((row < 0 || row > SIZE) || (column < 0 || column > SIZE) ||
        (value < UNASSINGED || value > SIZE)){
        return -1;
    }
    //check play is valid
    if (!isValid(row, column, value) && value != UNASSINGED) {return -2;}
    //update grid
    int old_value = grid[row][column];
    grid[row][column] = value;
    //update history and counters
    addHistory(row, column, value, old_value);
    updateCounters(row, column, value, old_value);
    return 0;
};

//Checks to see if a value can be added to the grid.
bool SudokuPuzzle::isValid(int row, int column, int value){
    return (isRowValid(row, value) && isColumnValid(column, value) 
        && isSubGridValid(row, column, value));
};

// Checks to see if a value can be added to a row.
bool SudokuPuzzle::isRowValid(int row, int value){
    for(int i=0; i<SIZE; i++){
        if(grid[row][i] == value){return false;}
    }
    return true;
};

// Checks to see if a value can be added to a column.
bool SudokuPuzzle::isColumnValid(int column, int value){
    for(int i=0; i<SIZE; i++){
        if(grid[i][column] == value){return false;}
    }
    return true;
};

// Checks to see if a value can be added to a subgrid.
bool SudokuPuzzle::isSubGridValid(int row, int column, int value){
    int sub_grid_numbers[SUB_SIZE*SUB_SIZE];
    getSubgrid(row, column, sub_grid_numbers);
    for (int i=0; i<SUB_SIZE*SUB_SIZE; i++){
        if (sub_grid_numbers[i] == value){return false;}
    }
    return true;
};

// Places the values of a subgrid into an array.
void SudokuPuzzle::getSubgrid(int row, int column, int (&sub_grid_numbers)[SUB_SIZE*SUB_SIZE]){
    int sg_row = (row/SUB_SIZE)*SUB_SIZE;
    int sg_column = (column/SUB_SIZE)*SUB_SIZE;
    int n = 0;
    for (int i=sg_row; i<sg_row+SUB_SIZE; i++){
        for (int j=sg_column; j<sg_column+SUB_SIZE; j++){
            sub_grid_numbers[n] = grid[i][j];
            n++;
        }
    }
};

// Unassinges all values from the grid.
void SudokuPuzzle::clear() {
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            grid[i][j] = UNASSINGED;
        }
    }
    // reinitialise counters
    initialiseCounters();
    // remove history
    removeAllHistory();

};

//Adds a Move object to the linked list.
void SudokuPuzzle::addHistory(int row, int column, int new_value, int old_value) {
    Move* new_move = new Move;
    new_move->row = row;
    new_move->column = column;
    new_move->new_value = new_value;
    new_move->old_value = old_value;
    new_move->prev = prev_move;
    prev_move = new_move;
};

//Remove a Move from the linked list.
void SudokuPuzzle::removeHistory(Move* move){
    if (move == NULL){return;}
    prev_move = move->prev;
    delete move;
};

void SudokuPuzzle::removeAllHistory(){
    while(prev_move != NULL) {
        removeHistory(prev_move);
    }
}

//Revert to previous move.
void SudokuPuzzle::undo() {
    if (prev_move == NULL) {return;}
    add(prev_move->row, prev_move->column, prev_move->old_value);
    removeHistory(prev_move);
    removeHistory(prev_move);
};

//Get value for coordinates.
int SudokuPuzzle::getValue(int row, int column) {
    //check for correct coordinates
    if ((row < 0 || row > SIZE) || (column < 0 || column > SIZE)){
        return -1;
    }
    return grid[row][column];
};

// Updates the row and column Counters.
void SudokuPuzzle::updateCounters(int row, int column, int new_value, int old_value){
    int indexes[2] = {row, column};
    // removing an element
    if (new_value == UNASSINGED && old_value != UNASSINGED) {
        for (int i=0; i<2; i++){
            deincrementCounter(counters[i], indexes[i]);
        }
    // adding an element
    } else if(new_value != UNASSINGED && old_value == UNASSINGED){
        for (int i=0; i<2; i++){
            incrementCounter(counters[i], indexes[i]);
        }
    }
};

// Increment a Counter
void SudokuPuzzle::incrementCounter(Counter &counter, int index){
    //increment the counter and check if it is larger than the max
    if (++counter.counts[index] >= counter.max){
        if (counter.counts[index] == SIZE) {
            //set to -1 to move the index to the next largest
            counter.filled += 1;
            counter.counts[index] = -1;
            findNewMax(counter);
        } else {
            counter.max = counter.counts[index];
            counter.index = index;
        }
    }
};

// Deincrement a Counter.
void SudokuPuzzle::deincrementCounter(Counter &counter, int index){
    // if row/column was filled
    if (counter.counts[index] == -1){
        counter.counts[index] = SIZE;
        counter.filled -= 1;
    }
    // deincrement and find new max if row/column was max
    if (--counter.counts[index] == counter.max - 1){
        findNewMax(counter);
    }
};

// Sets the max value for a Counter object.
void SudokuPuzzle::findNewMax(Counter &counter){
    int new_max = 0;
    for (int i=0; i<SIZE; i++){
        if (counter.counts[i] >= new_max){
            counter.max = counter.counts[i];
            new_max = counter.max;
            counter.index = i;
        }
    }
};

// Sets the given values to grid coordinates with the
// most other values in the row or column.
void SudokuPuzzle::getOptimalCoordinates(int &row, int&column) {
    Counter row_counter = counters[0];
    Counter column_counter = counters[1];

    // puzzle is solved
    if (row_counter.filled == SIZE && column_counter.filled == SIZE){
        row = -1; column = -1;
        return;
    }

    if (row_counter.max >= column_counter.max){
        // return an unassinged coordinate in that row
        row = row_counter.index;
        int free_column_counts = 0;
        for (int i=0; i<SIZE; i++){
            if ((getValue(row_counter.index, i) == UNASSINGED) &&
                (column_counter.counts[i] >= free_column_counts))
            {
                column = i;
                free_column_counts = column_counter.counts[i];
            }
        }
    } else {
        // return an unassinged coordinate in the column
        column = column_counter.index;
        int free_row_counts = 0;
        for (int i=0; i<SIZE; i++){
            if ((getValue(i, column_counter.index) == UNASSINGED) &&
                (row_counter.counts[i] >= free_row_counts))
            {
                row = i;
                free_row_counts = row_counter.counts[i];
            }
        }
    }
};