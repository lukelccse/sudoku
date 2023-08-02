/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 26.07.23
 * DATE MODIFIED: 01.08.23
 * FILE: actions.h
 * DESC: Actions enum class
 ********************/

/* Actions
*  q - quit
*  u - undo
*  a x y z - add z at coordinates (x,y)
*  r - reset
*  n - new puzzle
*  c - clear board
*  s - solve
*  h - help
*/

#ifndef ACTIONS
#define ACTIONS
enum class Actions{
    quit=1,
    undo,
    clear,
    reset,
    new_puzzle,
    solve,
    help,
    add
};
#endif