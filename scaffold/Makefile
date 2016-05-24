#
# Clement Poh
#
# Makefile for assignment two of COMP20007 2016.
#
# Replace '<STUDENT-ID>' with your Student ID e.g. 269508
STUDENTID = 269508
SUBMIT	= hash.c types.c extra.c report.pdf

# Define the C compiler
CC      = gcc

# Define the compiler flags
#  -Wall to turn on most of the warnings
#  -Wextra to turn on even more warnings
#  -Wpedantic to turn on even more warnings
#  -ansi to ensure ansi compliance
#  -std=c99 to ensure c99 compliance
#  -m32 to compile for 32 bit architectures
#  -O0 to turn off optimisations
#  -g  to include debugging symbols
#  -pg for profiling
CFLAGS  = -Wall -Wextra -Wpedantic -ansi -std=c99 -m32 -O0 -g # -pg

# Define any libraries to be linked
LIB		= -lm

# Define the source, header and object files
HDR		= array.h list.h hashtable.h hash.h types.h extra.h
SRC		= $(HDR:.h=.c)
OBJ     = $(SRC:.c=.o)

# The executable name
TARGET	= ass2

all: $(TARGET) scaffold

$(TARGET): $(OBJ) main.o Makefile
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(OBJ) $(LIB)

scaffold: $(OBJ) scaffold.o Makefile
	$(CC) $(CFLAGS) -o $@ scaffold.o $(OBJ) $(LIB)

submission: $(SUBMIT)
	tar -czvf $(STUDENTID).tar.gz $(SUBMIT)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET).s $(TARGET).o scaffold.o main.o 

.PHONY: clobber
clobber: clean
	rm -f tags $(STUDENTID).tar.gz $(TARGET) scaffold

.PHONY: usage
usage: $(TARGET)
	./$(TARGET)

tags:
	ctags -w $(SRC)

assembly: $(TARGET)
	objdump -S -M i386 $(TARGET) > $(TARGET).s

size: scaffold
	if ./scaffold -n 1000 ; then echo "correct size" ; fi

test: $(TARGET)
	./$(TARGET) -h b -m -t s ../../test/str.in -f ../../test/search.in -p

dumb: $(TARGET)
	./$(TARGET) -h u -t s -c d -g 1500 ../../str.in

clever: $(TARGET)
	./$(TARGET) -h u -t s -c c ../../test/str.in

$(OBJ): $(HDR)
