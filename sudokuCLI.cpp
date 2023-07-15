/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuCLI.cpp
 * DESC: contains the sudoku CLI implementation
 ********************/
#include "sudokuCLI.h"
#include "sudokuSolver.h"
#include <string>
#include <iostream>

void SudokuCLI::display() {
    std::string h_delimiter = " +-------+-------+-------+\n";
    std::cout << h_delimiter;
    for(int i=0; i<SIZE; i++) {
        std::cout << " |";
        for(int j=0; j<SIZE; j++){
            std::cout << " ";
            if (sudokuPuzzle.getCoordinate(i,j) == 0) {std::cout << ".";}
            else {std::cout << sudokuPuzzle.getCoordinate(i,j);}
            if ((j+1)%3 == 0 && j+1 != SIZE){
                std::cout << " |";
            }
        }
        std::cout << " |\n";
        if ((i+1)%3 == 0 && i+1 != SIZE){
            std::cout << h_delimiter;
        }
    }
    std::cout << h_delimiter;
};

std::string SudokuCLI::prompt() {
    std::cout << ">>> ";
    std::string input = "";
    std::getline(std::cin, input);
    return input;
};

void SudokuCLI::clear() {
    int n;
    for (n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
};

//actions
//q - quit
//u - undo
//a x y z - add z at coordinates (x,y)
//c - clear board
//s - solve

void SudokuCLI::run() {
    while (true) {
        display();
        std::string action = prompt();
        if (action.compare("q") == 0){
            break;
        } else if (action.compare("u") == 0) {
            sudokuPuzzle.undo();
        } else if (action.compare("r") == 0) {
            sudokuPuzzle.clear();
        } else if (action.compare("s") == 0) {
            SudokuSolver sudokuSolver(sudokuPuzzle);
            if(sudokuSolver.solve()){std::cout << "Solution found.\n";}
            else {std::cout << "No solution.\n";}
        } else if (action[0] == 'a') {
            if (action.length() < 7){continue;}
            int row = (int)action[2] - 48;
            int column = (int)action[4] - 48;
            int value = (int)action[6] - 48;
            int result = sudokuPuzzle.add(row, column, value);
            if (result == -1) {
                std::cout << "Bad coordinates\\value.\n";
                continue;
            }
            if (result == -2) {
                std::cout << "Cannot place value.\n";
                continue;
            }
        } else {
            continue;
        }
        clear();
    }
};