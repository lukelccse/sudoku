/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuCLI.cpp
 * DESC: contains the sudoku CLI implementation
 ********************/
#include <iostream>
#include "sudokuPuzzle.h"
#include "sudokuCLI.h"
#include "sudokuCreator.h"

int main() {
  std::cout << " Welcome to Su-Do-Ku!\n";
  SudokuCreator sc;
  SudokuPuzzle sudoku;
  sc.getNewPuzzle(sudoku, ' ');
  SudokuCLI cli(sudoku);
  cli.run();
  return 0;
}