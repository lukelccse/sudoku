/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 16.07.23
 * FILE: sudokuPuzzle.h
 * DESC: contains the counter class header file
 ********************/

#ifndef COUNTER
#define COUNTER
#define SIZE 9
struct Counter {
    int counts[SIZE];
    int max;
    int index;
    int filled;
};
#endif