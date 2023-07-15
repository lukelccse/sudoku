
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

SudokuPuzzle::SudokuPuzzle() {
    //initialise all grid positions to 0
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++){
            grid[i][j] = 0;
        }
    }
    //No history
    prev_move = NULL;
};

SudokuPuzzle::SudokuPuzzle(SudokuPuzzle& newPuzzle) {
    //initialise all grid positions to 0
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++){
            grid[i][j] = newPuzzle.getCoordinate(i, j);
        }
    }
    //No history
    prev_move = NULL;
};

SudokuPuzzle::~SudokuPuzzle() {
    while(prev_move != NULL) {
        removeHistory(prev_move);
    }
};

int SudokuPuzzle::add(int row, int column, int value){
    //check for correct coordinates
    if ((row < 0 || row > SIZE) || (column < 0 || column > SIZE) ||
        (value < 1 || value > 9)){
        return -1;
    }
    //check play is valid
    if (!isValid(row, column, value)) {return -2;}
    //update grid
    addHistory(row, column, value, grid[row][column]);
    grid[row][column] = value;
    return 0;
};

bool SudokuPuzzle::isValid(int row, int column, int value){
    return (isRowValid(row, value) && isColumnValid(column, value) 
        && isSubGridValid(row, column, value));
};

bool SudokuPuzzle::isRowValid(int row, int value){
    for(int i=0; i<SIZE; i++){
        if(grid[row][i] == value){return false;}
    }
    return true;
};

bool SudokuPuzzle::isColumnValid(int column, int value){
    for(int i=0; i<SIZE; i++){
        if(grid[i][column] == value){return false;}
    }
    return true;
};

bool SudokuPuzzle::isSubGridValid(int row, int column, int value){
    int sub_grid_numbers[SUB_SIZE*SUB_SIZE];
    getSubgrid(row, column, sub_grid_numbers);
    for (int i=0; i<SUB_SIZE*SUB_SIZE; i++){
        if (sub_grid_numbers[i] == value){return false;}
    }
    return true;
};

void SudokuPuzzle::getSubgrid(int row, int column, int (&sub_grid_numbers)[SUB_SIZE*SUB_SIZE]){
    int sg_row = (row/3)*3;
    int sg_column = (column/3)*3;
    int n = 0;
    for (int i=sg_row; i<sg_row+3; i++){
        for (int j=sg_column; j<sg_column+3; j++){
            sub_grid_numbers[n] = grid[i][j];
            n++;
        }
    }
};

void SudokuPuzzle::clear() {
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            grid[i][j] = 0;
        }
    }
};

void SudokuPuzzle::addHistory(int row, int column, int new_value, int old_value) {
    Move* new_move = new Move;
    new_move->row = row;
    new_move->column = column;
    new_move->new_value = new_value;
    new_move->old_value = old_value;
    new_move->prev = prev_move;
    prev_move = new_move;
};

void SudokuPuzzle::removeHistory(Move* move){
    if (move == NULL){return;}
    prev_move = move->prev;
    delete move;
};

void SudokuPuzzle::undo() {
    if (prev_move == NULL) {return;}
    grid[prev_move->row][prev_move->column] = prev_move->old_value;
    removeHistory(prev_move);
};

int SudokuPuzzle::getCoordinate(int row, int column) {
    //check for correct coordinates
    if ((row < 0 || row > SIZE) || (column < 0 || column > SIZE)){
        return -1;
    }
    return grid[row][column];
};