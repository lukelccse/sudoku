MAIN = main
SUDOKU = SudokuPuzzle
CLI = SudokuCLI
SOLVER = SudokuSolver
CREATOR = SudokuCreator
COMPILER = g++
COMPILERFLAGS = -c --std=c++11

all: $(MAIN)

$(MAIN): $(SUDOKU).o $(SOLVER).o $(CREATOR).o $(CLI).o $(MAIN).o
	$(COMPILER) $(SUDOKU).o $(SOLVER).o $(CREATOR).o $(CLI).o $(MAIN).o -o sudoku

$(MAIN).o: $(MAIN).cpp
	$(COMPILER) $(COMPILERFLAGS) $(MAIN).cpp

$(SUDOKU).o: $(SUDOKU).cpp $(SUDOKU).h move.h counter.h
	$(COMPILER) $(COMPILERFLAGS) $(SUDOKU).cpp

$(SOLVER).o: $(SOLVER).cpp $(SOLVER).h
	$(COMPILER) $(COMPILERFLAGS) $(SOLVER).cpp

$(CREATOR).o: $(CREATOR).cpp $(CREATOR).h
	$(COMPILER) $(COMPILERFLAGS) $(CREATOR).cpp

$(CLI).o: $(CLI).cpp $(CLI).h actions.h char2enum.h
	$(COMPILER) $(COMPILERFLAGS) $(CLI).cpp

clean:
	rm -f *.o