/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 23.07.23
 * DATE MODIFIED: 23.07.23
 * FILE: sudokuCreator.cpp
 * DESC: contains the sudokuCreator implementation
 ********************/

/* How do we create a unique sudoku puzzle of varying difficulty?
* Inspiration:
* 1. Generate a some what random sudoku board.
* 2. Dig a "hole" by removing a gird position.
* 3. Check that the puzzle can be solved uniquely using a backtracking solver.
* 4. If the puzzle has more than one solution fill the hole and continue to find 
        other singe solution holes.
* 5. Continue steps 2-4 until enough holes have been dug.
* 6. Shuffle the grid.
*/

#include <algorithm>
#include <random>
#include <iostream>
#include "sudokuCreator.h"
#include "sudokuPuzzle.h"
#include "sudokuSolver.h"

SudokuCreator::SudokuCreator(){
    //init holes matrix
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            holes[i][j] = true;
        }
    }
};

void SudokuCreator::getNewPuzzle(SudokuPuzzle &new_puzzle, char difficuilty_lvl){
    generateSudoRandomGrid(new_puzzle);
    digHoles(new_puzzle, 81); 
};

//Generates a sudo randomly solved sudoku puzzle.
void SudokuCreator::generateSudoRandomGrid(SudokuPuzzle &new_puzzle){
    //generate a random permutation of of numbers in [0, SIZE]
    int seed_array[SIZE];
    for(int i=0; i<SIZE; i++){seed_array[i] = i+1;}
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(&seed_array[0], &seed_array[SIZE], g);
    //fill the diagonals of a puzzle
    for(int i=0; i<SIZE; i++){new_puzzle.add(i, i, seed_array[i]);}
    //solve the puzzle
    SudokuSolver solver(new_puzzle);
    solver.solve();
};

// Dig N holes into a puzzle.
void SudokuCreator::digHoles(SudokuPuzzle &puzzle, int N) {
    int holes_dug = 0;
    while(holes_dug < N){
        //dig hole
        int row = -1;
        int column = -1;
        getCoordinates(row, column);
        if ((row == -1) && (column == -1)){break;}
        int value = puzzle.getValue(row, column);
        // dig hole
        puzzle.add(row, column, UNASSINGED);
        //check hole
        if (!uniqueSolution(puzzle, row, column)) {
            std::cout << "No unique solution: \n";
            puzzle.add(row, column, value);
        } else {holes_dug++;}
        std::cout << "Holes dug: " << holes_dug << "\n";
    }
};

// Check there is only one solution for a puzzle
bool SudokuCreator::uniqueSolution(SudokuPuzzle &puzzle, int row, int column){
    int n_solutions = 0;
    for(int i=0; i<SIZE; i++){
        if (puzzle.add(row, column, i+1) != 0) {continue;}
        SudokuPuzzle copy_puzzle = puzzle;
        SudokuSolver solver(copy_puzzle);
        if(solver.solve()) {
            std::cout << row << " ";
            std::cout << column << " ";
            std::cout << i+1 << "\n";
            n_solutions++;
        }
    }
    puzzle.add(row, column, UNASSINGED);
    // only one solution
    if (n_solutions == 1){return true;}
    return false;
};

// Get grid coordinates to dig.
void SudokuCreator::getCoordinates(int &row, int &column){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(holes[i][j]){
                row=i; column=j;
                holes[i][j] = false;
                return;
            }
        }
    }
};

