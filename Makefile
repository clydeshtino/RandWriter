CC = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework 

DEPS = RandWriter.hpp 
OBJ = RandWriter.o 

all: TextWriter test TextWriter.a

TextWriter: TextWriter.o $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

TextWriter.a: $(OBJ)
	ar rcs TextWriter.a $(OBJ)

test: test.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< 

clean: 
	rm *.o test TextWriter TextWriter.a

lint:
	cpplint *.cpp *.hpp 