/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 26.07.23
 * FILE: sudokuCLI.cpp
 * DESC: contains the sudoku CLI implementation
 ********************/
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include "sudokuCLI.h"
#include "sudokuSolver.h"
#include "sudokuCreator.h"
#include "Actions.h"
#include "char2enum.h"

// Constructor.
SudokuCLI::SudokuCLI(SudokuPuzzle &sudoku): sudokuPuzzle(sudoku){
    char levels[] = {'E', 'M', 'H', 'I', 'N'};
    for (char lvl : levels){
        difficuilty_lvl.insert(lvl);
    }
    char2enum char_action[] = {{'q', Actions::quit}, 
                               {'u', Actions::undo}, 
                               {'c', Actions::clear}, 
                               {'s', Actions::solve}, 
                               {'a', Actions::add}};
    for (char2enum &ca : char_action){
        action_map[ca.a] = ca.action;
    }
};

// Displays the sudoku puzzle to the terminal.
void SudokuCLI::display() {
    std::string seperator = getColumnSeperator();
    std::cout << seperator;
    for(int i=0; i<SIZE; i++) {
        std::cout << " |";
        for(int j=0; j<SIZE; j++){
            std::cout << " ";
            if (sudokuPuzzle.getValue(i,j) == 0) {std::cout << ".";}
            else {std::cout << sudokuPuzzle.getValue(i,j);}
            if ((j+1)%SUB_SIZE == 0 && j+1 != SIZE){
                std::cout << " |";
            }
        }
        std::cout << " |\n";
        if ((i+1)%SUB_SIZE == 0 && i+1 != SIZE){
            std::cout << seperator;
        }
    }
    std::cout << seperator;
};

std::string SudokuCLI::getColumnSeperator(){
    std::string seperator = " +";
    std::string lines = "";
    for(int i=0; i<(SUB_SIZE*2 + 1); i++){
        lines += "-";
    }
    for(int i=0; i<SUB_SIZE; i++){
        seperator += lines + "+";
    }
    seperator += "\n";
    return seperator;
};

// Prints a prompt, returns the user input.
std::string SudokuCLI::prompt() {
    std::cout << ">>> ";
    std::string input = "";
    std::getline(std::cin, input);
    return input;
};

// Clears the terminal.
void SudokuCLI::clear() {
    int n;
    for (n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
};

// Asks the user for the difficuilty of puzzle
// and calls the SudokuCreator class to give a 
// puzzle of corresponding difficuilty. 
void SudokuCLI::createPuzzle() {
    std::cout << "Select Difficuilty: E-Easy, M-Medium, H-Hard, I-Impossible, N-Empty\n";
    std::string option = prompt();
    transform(option.begin(), option.end(), option.begin(), ::toupper);
    if (difficuilty_lvl.find(option[0]) == difficuilty_lvl.end()){createPuzzle();}
    SudokuCreator sudoku_creator;
    if (option[0] == 'N'){return;}
    sudoku_creator.getNewPuzzle(sudokuPuzzle, option[0]);
};

// Main Loop.
void SudokuCLI::run() {
    //create a puzzle
    createPuzzle();
    display();
    std::string action;
    bool stop = false;
    while (!stop) {
        action = prompt();
        transform(action.begin(), action.end(), action.begin(), ::tolower);
        switch (parseInput(action)){
            case -1: stop = true; break;
            case 0: clear(); display(); break;
            case 1: break; //do nothing, continue
        }
    }
    std::cout << "Thanks for playing!\n";
};

int SudokuCLI::parseInput(std::string action){
    switch (action_map[action[0]]){
        case Actions::quit:{
                return -1;
        }
        case Actions::undo:{
                sudokuPuzzle.undo();
                return 0;
            }
        case Actions::clear:{
                sudokuPuzzle.clear(); 
                return 0;
            }
        case Actions::solve:{
                SudokuSolver sudokuSolver(sudokuPuzzle);
                if(sudokuSolver.solve()){std::cout << "Solution found.\n"; return 0;}
                else {std::cout << "No solution.\n"; return 1;}
                break;
            }
        case Actions::add:{
                if (action.length() < 7){return 1;}
                int row = (int)action[2] - 48;
                int column = (int)action[4] - 48;
                int value = (int)action[6] - 48;
                int result = sudokuPuzzle.add(row, column, value);
                if (result == -1) {
                    std::cout << "Bad coordinates\\value.\n";
                    return 1;
                }
                if (result == -2) {
                    std::cout << "Cannot place value.\n";
                    return 1;
                }
                return 0;
            }
        default:{
                std::cout << "Action not recognised.\n";
                return 1;
            }
    }
    return -1;
};