/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 01.08.23
 * FILE: sudoku.h
 * DESC: contains the move header
 ********************/

#ifndef MOVE
#define MOVE
struct Move {
    int row;
    int column;
    int new_value;
    int old_value;
    Move* prev;
};
#endif