MAIN = main
SUDOKU = sudokuPuzzle
CLI = sudokuCLI
SOLVER = sudokuSolver
COMPILER = g++
COMPILERFLAGS = -c

all: $(MAIN)

$(MAIN): $(SUDOKU).o $(CLI).o $(SOLVER).o $(MAIN).o
	$(COMPILER) $(SUDOKU).o $(CLI).o $(MAIN).o -o sudoku

$(MAIN).o: $(MAIN).cpp
	$(COMPILER) $(COMPILERFLAGS) $(MAIN).cpp

$(SUDOKU).o: $(SUDOKU).cpp $(SUDOKU).h move.h
	$(COMPILER) $(COMPILERFLAGS) $(SUDOKU).cpp

$(CLI).o: $(CLI).cpp $(CLI).h
	$(COMPILER) $(COMPILERFLAGS) $(CLI).cpp

$(SOLVER).o: $(SOLVER).cpp $(SOLVER).h
	$(COMPILER) $(COMPILERFLAGS) $(SOLVER).cpp

clean:
	rm -f *.o sudoku