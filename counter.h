/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 28.06.23
 * DATE MODIFIED: 01.08.23
 * FILE: counter.h
 * DESC: Counter struct
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