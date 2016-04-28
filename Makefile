#
# Clement Poh
#
# Makefile for assignment two of COMP20007 2016.
#
# Replace '<STUDENT-ID>' with your Student ID e.g. 269508
STUDENTID = <STUDENT-ID>
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
LIB		=

# Define the source, header and object files
HDR		= array.h list.h hashtable.h hash.h types.h extra.h
SRC		= $(HDR:.h=.c) main.c
OBJ     = $(SRC:.c=.o)

# The executable name
TARGET	= ass2

$(TARGET): $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIB)

submission: $(SUBMIT)
	tar -czvf $(STUDENTID).tar.gz $(SUBMIT)

.PHONY: clean
clean:
	rm -f $(OBJ) spec.pdf

.PHONY: clobber
clobber: clean
	rm -f $(TARGET) tags $(STUDENTID).tar.gz

.PHONY: usage
usage: $(TARGET)
	./$(TARGET)

tags:
	ctags -w $(SRC)

test: $(TARGET)
	./ass2 -h 3 -m -t s test/str.in -f test/not.in -p

collide: $(TARGET)
	./ass2 -h 3 -t s -c 1 test/str.in

spec.pdf: spec.tex
	pdflatex spec.tex && rm spec.log spec.aux

$(OBJ): $(HDR)
