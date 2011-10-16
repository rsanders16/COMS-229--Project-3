proj3.exe: proj3.o 8-puzzle.o
	 g++ -o proj3.exe proj3.o 8-puzzle.o

proj3.o: proj3.cpp 8-puzzle.h
       g++ -c proj3.cpp

8-puzzle.o: 8-puzzle.cpp 8-puzzle.h
	    g++ -c 8-puzzle.cpp