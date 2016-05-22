#!/bin/sh
#
# Clement Poh
#
# Copies required files into a submission and compiles the program.
# Outputs the compiler warnings to compile.txt
#

SCRIPTS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SKELETON=${2:-"./skeleton"}
SOLN=${3:-"./soln"}
EXIT=0

HDR="array.h extra.h hash.h hashtable.h list.h types.h"
SRC="array.c hashtable.c list.c main.c"

# Compile the submission
if [ -d "$1" ]; then
    OUT="$1/out"
    LOGFILE="$OUT/make.txt"

    # Copy skeleton files into the directories
    for src in $HDR $SRC Makefile; do
        cp "$SKELETON/$src" "$1"
    done

    mkdir -p "$OUT"
    USER=$(basename "$1")

    printf "******************************************\n" > $LOGFILE
    printf "* Compiling solution:\n" >> $LOGFILE
    printf "******************************************\n" > $LOGFILE
    # Compile the submission
    make -C "$1" >> $LOGFILE 2>&1

    EXIT=$?
    case $EXIT in
        0) printf "PASS compilation $USER\n" ;;
        *) printf "FAIL compilation $USER\n" ;;
    esac

    # Clean up the folder quietly
    make -C "$1" clean &> /dev/null

    exit $EXIT
fi
