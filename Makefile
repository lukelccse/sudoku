MAIN = main
SUDOKU = sudokuPuzzle
CLI = sudokuCLI
COMPILER = g++
COMPILERFLAGS = -c

all: $(MAIN)

$(MAIN): $(SUDOKU).o $(CLI).o $(MAIN).o
	$(COMPILER) $(SUDOKU).o $(CLI).o $(MAIN).o -o sudoku

$(MAIN).o: $(MAIN).cpp
	$(COMPILER) $(COMPILERFLAGS) $(MAIN).cpp

$(SUDOKU).o: $(SUDOKU).cpp $(SUDOKU).h move.h
	$(COMPILER) $(COMPILERFLAGS) $(SUDOKU).cpp

$(CLI).o: $(CLI).cpp $(CLI).h
	$(COMPILER) $(COMPILERFLAGS) $(CLI).cpp

clean:
	rm -f *.o sudoku