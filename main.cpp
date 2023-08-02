/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 01.08.23
 * FILE: main.cpp
 * DESC: entry point to run program
 ********************/
#include <iostream>
#include "sudokuPuzzle.h"
#include "sudokuCLI.h"

int main() {
  std::cout << " Welcome to Su-Do-Ku!\n";
  SudokuPuzzle sudoku;
  SudokuCLI cli(sudoku);
  cli.run();
  std::cout << "Thanks for playing!\n";
  return EXIT_SUCCESS;
}