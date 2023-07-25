/********************
 * AUTHOR: lukelccse
 * DATE CREATED: 23.07.23
 * DATE MODIFIED: 23.07.23
 * FILE: sudokuCreator.cpp
 * DESC: contains the sudokuCreator implementation
 ********************/

/* How do we create a unique sudoku puzzle of varying difficulty?
* Inspiration: https://zhangroup.aporc.org/images/files/Paper_3485.pdf
* 1. Generate a some what random sudoku board.
* 2. Dig a "hole" by removing a gird position.
* 3. Check that the puzzle can be solved uniquely using a backtracking solver.
* 4. If the puzzle has more than one solution fill the hole and continue to find 
        other singe solution holes.
* 5. Continue steps 2-4 until enough holes have been dug or no more holes can be dug.
* 6. Shuffle the grid.
*/

#include <algorithm>
#include <random>
#include <iostream>
#include <cstdlib>
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
    // Provide a seed value
    std::srand((unsigned) time(NULL));
    //create difficuilty map
    char lvl_names[] = {'E', 'M', 'H', 'I'};
    int n_holes[] = {31, 45, 49, 53};
    for(int i=0; i<sizeof(lvl_names); i++){
        lvl[lvl_names[i]] = n_holes[i];
    }
};


void SudokuCreator::getNewPuzzle(SudokuPuzzle &new_puzzle, char difficuilty_lvl){
    generateSudoRandomGrid(new_puzzle);
    digHoles(new_puzzle, lvl[difficuilty_lvl]);
    shuffle(new_puzzle);
};

//Generates a sudo randomly solved sudoku puzzle.
void SudokuCreator::generateSudoRandomGrid(SudokuPuzzle &new_puzzle){
    //generate a random combination of of numbers in [0, SIZE]
    int seed_array[SIZE];
    randomiseArray(seed_array);
    //fill the diagonals of a puzzle
    for(int i=0; i<SIZE; i++){new_puzzle.add(i, i, seed_array[i]);}
    //solve the puzzle
    SudokuSolver solver(new_puzzle);
    solver.solve();
};

// Initialises an array of size=SIZE with a random combination
// of numbers from [0, SIZE]
void SudokuCreator::randomiseArray(int (&array)[SIZE]){
    for(int i=0; i<SIZE; i++){array[i] = i+1;}
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(&array[0], &array[SIZE], g);
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
            puzzle.add(row, column, value);
        } else {holes_dug++;}
    }
};

// Check there is only one solution for a puzzle
bool SudokuCreator::uniqueSolution(SudokuPuzzle &puzzle, int row, int column){
    int n_solutions = 0;
    for(int i=0; i<SIZE; i++){
        if (puzzle.add(row, column, i+1) != 0) {continue;}
        SudokuPuzzle copy_puzzle = puzzle;
        SudokuSolver solver(copy_puzzle);
        if(solver.solve()) {n_solutions++;}
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

// Shuffle a sudoku puzzle.
void SudokuCreator::shuffle(SudokuPuzzle &puzzle){
    int grid[SIZE][SIZE];
    fillGrid(puzzle, grid);
    twoDigitsPropagation(grid);
    swapColumnsPropagation(grid);
    swapBlocksPropagation(grid);
    gridRollPropagation(grid);
    fillSudoku(puzzle, grid);
};

// Place sudoku puzzle values into a grid for easy manipulation.
void SudokuCreator::fillGrid(SudokuPuzzle &puzzle, int (&grid)[SIZE][SIZE]){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            grid[i][j] = puzzle.getValue(i, j);
        }
    }
}

// Place grid values into sudoku puzzle.
void SudokuCreator::fillSudoku(SudokuPuzzle &puzzle, int (&grid)[SIZE][SIZE]){
    puzzle.clear();
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            puzzle.add(i, j, grid[i][j]);
        }
    }
}

// Swap sets of values on the sudoku grid.
void SudokuCreator::twoDigitsPropagation(int (&grid)[SIZE][SIZE]){
    //generate a random combination of of numbers in [0, SIZE]
    int rand_array[SIZE];
    randomiseArray(rand_array);
    // swap the values by grouping the array in twos
    for(int i=0; i<(SIZE-1); i+=2){
        swapValues(grid, rand_array[i], rand_array[i+1]);
    }
};

// Swap two values on the grid.
void SudokuCreator::swapValues(int (&grid)[SIZE][SIZE], int value_one, int value_two){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if (grid[i][j] == value_one){grid[i][j] = value_two;}
            else if (grid[i][j] == value_two){grid[i][j] = value_one;}
        }
    }
};

// Swap columns or rows in the same block.
void SudokuCreator::swapColumnsPropagation(int (&grid)[SIZE][SIZE]){
    //swap columns in each block
    for (int block=0; block < SUB_SIZE; block++){
        //find random pairing
        int column_one = randomSubSizeNumber();
        int column_two = randomSubSizeNumber();
        column_one += block*SUB_SIZE;
        column_two += block*SUB_SIZE;
        swapColumns(grid, column_one, column_two);
    }
};

// generates a random number in [0, SUB_SIZE]
int SudokuCreator::randomSubSizeNumber(){
    return (std::rand() % SUB_SIZE);
};

// swaps two columns
void SudokuCreator::swapColumns(int (&grid)[SIZE][SIZE], int column_one, int column_two){
    if (column_one == column_two) {return;}
    for(int i=0; i<SIZE; i++){
        int tmp = grid[i][column_one];
        grid[i][column_one] = grid[i][column_two];
        grid[i][column_two] = tmp;
    }
};

// Swap two blocks.
void SudokuCreator::swapBlocksPropagation(int (&grid)[SIZE][SIZE]){
    //swap blocks
    int block_one = randomSubSizeNumber();
    int block_two = randomSubSizeNumber();
    if(block_one == block_two){return;}
    for (int i=0; i < SUB_SIZE; i++){
        //swap corresponding columns
        int column_one = block_one * SUB_SIZE + i;
        int column_two = block_two * SUB_SIZE + i;
        swapColumns(grid, column_one, column_two);
    }
};
// Rotate the grid a number of times clockwise.
void SudokuCreator::gridRollPropagation(int (&grid)[SIZE][SIZE]){
    int n_rotations = (std::rand() % 4); // [0, 1, 2, 3]
    for(int i=0; i<n_rotations; i++){
        rotateGrid(grid);
    }
};

// Rotate the grid clockwise
void SudokuCreator::rotateGrid(int (&grid)[SIZE][SIZE]){
    //rotate values into the new grid
    int tmp_grid[SIZE][SIZE];
    for(int x=0; x<SIZE; x++){
        for(int y=0; y<SIZE; y++){
            tmp_grid[x][y] = grid[SIZE-y-1][x];
        }
    }
    //copy to original grid
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            grid[i][j] = tmp_grid[i][j];
        }
    }
};

