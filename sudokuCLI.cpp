/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 13.07.23
 * FILE: sudokuCLI.cpp
 * DESC: contains the sudoku CLI implementation
 ********************/
#include "sudokuCLI.h"
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

void SudokuCLI::clear() {
    char input = std::cin.get();
    int n;
    for (n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
};