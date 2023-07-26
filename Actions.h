/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 26.07.23
 * DATE MODIFIED: 26.07.23
 * FILE: sudokuCLI.cpp
 * DESC: contains the Actions enum class
 ********************/

#ifndef ACTIONS
#define ACTIONS
/* Actions
*  q - quit
*  u - undo
*  a x y z - add z at coordinates (x,y)
*  c - clear board
*  s - solve
*/
enum class Actions{
    quit=1,
    undo,
    clear,
    solve,
    add
};
#endif