TARGET=test_array
INC=-I../include
CFLAGS=-g -std=c99
OBJ=../obj

$(TARGET): test_array.o $(OBJ)/array.o
	$(LINK.o) -o $@ $< $(OBJ)/array.o

test_array.o: test_array.c
	$(COMPILE.c) $(INC) -o $@ $<


