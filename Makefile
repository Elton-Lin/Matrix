
Test: test.o Matrix.o
	g++ -std=c++1z -Wconversion -Werror -Wall test.o Matrix.o -o test.out

test.o: test.cpp
	g++ -std=c++1z -Wconversion -Werror -Wall -c test.cpp

Matrix: main.o Matrix.o
	g++ -std=c++1z -Wconversion -Werror -Wall main.o Matrix.o -o mat.out

main.o: main.cpp
	g++ -std=c++1z -Wconversion -Werror -Wall -c main.cpp

Matrix.o: Matrix.cpp Matrix.h
	g++ -std=c++1z -Wconversion -Werror -Wall -c Matrix.cpp

clean:
	rm *.o *.out
