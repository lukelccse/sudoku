/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuCLI.cpp
 * DESC: contains the sudoku CLI implementation
 ********************/
#include <iostream>
#include "sudoku.h"
#include "sudokuCLI.h"

int main() {
  std::cout << " Welcome to Su-Do-Ku!\n";
  SudokuPuzzle sudoku;
  SudokuCLI cli(sudoku);
  sudoku.add(0, 0, 4);
  cli.display();
  cli.clear();
  sudoku.add(0, 4, 6);
  cli.display();
  cli.clear();
  sudoku.add(6, 5, 6);
  cli.display();
  sudoku.add(1, 1, 4);
  cli.display();
  sudoku.add(2, 2, 4);
  cli.display();
  cli.clear();
  sudoku.undo();
  cli.display();
  cli.clear();
  sudoku.undo();
  cli.display();
  cli.clear();
  sudoku.undo();
  cli.display();
  cli.clear();
  return 0;
}