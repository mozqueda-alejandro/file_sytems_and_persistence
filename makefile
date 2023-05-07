all: File Directory main objects

objects: main.o Directory.o File.o
	g++ -std=c++11 main.o Directory.o File.o -o singleLevelDirectory

main: main.cpp
	g++ -std=c++11 -c main.cpp -o main.o

Directory: Directory.cpp
	g++ -std=c++11 -c Directory.cpp -o Directory.o

File: File.cpp
	g++ -std=c++11 -c File.cpp -o File.o

clean:
	rm *.o
	rm singleLevelDirectory

re: clean all
