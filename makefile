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


# HDIR = headers
# CDIR = src
# ODIR = objs
# CPPFLAGS = -std=c++11 -g
# DEPS = $(wildcard $(HDIR)/*.h)
# OBJ_FILES = main.o# put all dependencies for driver here
# OBJS = $(patsubst %.o, $(ODIR)/%.o, $(OBJ_FILES))
# vpath %.h headers
# vpath %.cpp src
# vpath %.o objs
# DIRS = $(HDIR) $(CDIR) $(ODIR)
# $(shell mkdir -p $(DIRS))

# $(ODIR)/%.o: %.cpp $(DEPS)
# 	g++ $(CPPFLAGS) -c $< -o $@

# main: $(OBJS)
# 	g++ $(CPPFLAGS) -o $@ $^

# clean:
# 	rm $(ODIR)/*.o main

# .PHONY: clean all
