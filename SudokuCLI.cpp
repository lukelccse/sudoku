/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 13.07.23
 * DATE MODIFIED: 01.08.23
 * FILE: sudokuCLI.cpp
 * DESC: sudoku CLI implementation
 ********************/
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include "SudokuCLI.h"
#include "SudokuSolver.h"
#include "SudokuCreator.h"
#include "actions.h"
#include "char2enum.h"
#define ACTION_STR_LENGTH 7

// Constructor.
SudokuCLI::SudokuCLI(SudokuPuzzle &sudoku): sudokuPuzzle(sudoku){
    char levels[] = {'E', 'M', 'H', 'I', 'N'};
    for (char lvl : levels){
        difficuilty_lvl.insert(lvl);
    }
    // assign chars to enum value
    char2enum char_action[] = {{'q', Actions::quit}, 
                               {'u', Actions::undo}, 
                               {'c', Actions::clear},
                               {'r', Actions::reset},
                               {'n', Actions::new_puzzle},
                               {'s', Actions::solve}, 
                               {'h', Actions::help}, 
                               {'a', Actions::add}};
    for (char2enum &ca : char_action){
        action_map[ca.a] = ca.action;
    }
};

// Displays the sudoku puzzle to the terminal.
void SudokuCLI::display() {
    std::string seperator = getColumnSeperator();
    std::cout << seperator;
    for (int i=0; i<SIZE; i++) {
        std::cout << " |";
        for (int j=0; j<SIZE; j++){
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
    for (int i=0; i<(SUB_SIZE*2 + 1); i++){
        lines += "-";
    }
    for (int i=0; i<SUB_SIZE; i++){
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
        std::cout << "\n\n\n\n\n\n\n\n\n\n";
};

// Asks the user for the difficuilty of puzzle,
// calls the SudokuCreator class to give a 
// puzzle of corresponding difficuilty. 
void SudokuCLI::createPuzzle() {
    std::cout << "Select Difficuilty: E-Easy, M-Medium, H-Hard, I-Impossible, N-Empty\n";
    std::string option = prompt();
    transform(option.begin(), option.end(), option.begin(), ::toupper);
    if (difficuilty_lvl.find(option[0]) == difficuilty_lvl.end()){
        createPuzzle();
        return;
    }
    SudokuCreator sudoku_creator;
    if (option[0] == 'N'){return;}
    sudoku_creator.getNewPuzzle(sudokuPuzzle, option[0]);
};

// Main Loop.
void SudokuCLI::run() {
    createPuzzle();
    help();
    sudokuPuzzle.freezePuzzle();
    sudokuPuzzle.startRecordingHistory();
    display();
    std::string action;
    bool stop = false;
    while (!stop) {
        action = prompt();
        transform(action.begin(), action.end(), action.begin(), ::tolower);
        switch (parseInput(action)){
            case -1: stop = true; break;
            case 0: clear(); display(); break;
            case 1: break;
        }
    };
};

// Parses the user input.
int SudokuCLI::parseInput(std::string action){
    switch (action_map[action[0]]){
        case Actions::quit:{
            return -1;
        }
        case Actions::help:{
            help();
            return 1;
        }
        case Actions::undo:{
            sudokuPuzzle.undo();
            return 0;
        }
        case Actions::clear:{
            sudokuPuzzle.clear(); 
            return 0;
        }
        case Actions::reset:{
            sudokuPuzzle.reset();
            return 0;
        }
        case Actions::solve:{
            std::cout << "solving puzzle...\n";
            sudokuPuzzle.stopRecordingHistory();
            SudokuSolver sudokuSolver(sudokuPuzzle);
            bool solved = sudokuSolver.solve();
            sudokuPuzzle.startRecordingHistory();
            if(solved){std::cout << "Solution found.\n"; return 0;}
            else {std::cout << "No solution.\n"; return 1;}
        }
        case Actions::new_puzzle:{
            sudokuPuzzle.stopRecordingHistory();
            sudokuPuzzle.clear();
            createPuzzle();
            sudokuPuzzle.startRecordingHistory();
            return 0;
        }
        case Actions::add:{
            if (action.length() < ACTION_STR_LENGTH){return 1;}
            int row = action[2] - '0' - 1;
            int column = action[4] - '0' - 1;
            int value = action[6] - '0';
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

// Prints user actions.
void SudokuCLI::help(){
    std::cout << "Actions:\n";
    std::cout << "\tq - Quit.\n";
    std::cout << "\th - Help.\n";
    std::cout << "\tu - Undo move.\n";
    std::cout << "\tr - Reset Puzzle.\n";
    std::cout << "\tn - New Puzzle.\n";
    std::cout << "\tc - Clear board.\n";
    std::cout << "\tc - Solve puzzle.\n";
    std::cout << "\ta X Y N - Add number N to coordinate (X, Y).\n";
};