/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuCLI.h
 * DESC: contains the sudoku CLI
 ********************/

#ifndef SUDOKU_CLI
#define SUDOKU_CLI
#include <string>
#include <set>
#include "sudokuPuzzle.h"
class SudokuCLI {
    private:
        SudokuPuzzle &sudokuPuzzle;
        std::set<char> difficuilty_lvl;
        void display();
        void clear();
        std::string prompt();
        void createPuzzle();
    public:
        SudokuCLI(SudokuPuzzle &sudoku);
        void run();
};
#endif