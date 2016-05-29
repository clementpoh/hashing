#!/bin/bash
#
# Clement Poh
#
SCRIPTS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TIMEOUT="$SCRIPTS/timeout.sh"

SHELL="/tmp/shell"
ERRORS="/tmp/error"

TESTS="./test"
SOLN="./soln/soln"

COUNT=0
PASS=0

exit_codes()  {
    local EXIT=$1

    case "$EXIT" in
        0)  if $SCAFFOLD < $OUTPUT 2>> $ERRORS > /dev/null; then
                MSG="PASS $BIN $OPTS $INPUT\n"
                PASS=$((PASS + 1))
            else
                MSG="FAIL $BIN $OPTS $INPUT | $SCAFFOLD\n"
            fi ;;
        1)  # Indicates that program exited with EXIT_FAILURE
            MSG="EXIT $BIN $OPTS $INPUT\n";;
        3)  #  failed assertion in MinGW
            MSG="$EXIT $BIN aborted\n";;
        5)  # Seems to indicate segmentation fault in MinGW
            MSG="$EXIT $BIN segmentation fault\n";;
        126) # Command is not executable
            MSG="$EXIT $BIN not executable\n";;
        127) # Command is not found
            MSG="$EXIT $BIN not found\n";;
        255) # Exit called incorrectly
            MSG="$EXIT $BIN exit called incorrectly\n";;
        *)  if [ $EXIT -lt 128 ]; then
                MSG="$EXIT $BIN $OPTS $INPUT\n"
            else
                # Program killed by signal
                SIG=$(kill -l $EXIT)
                MSG="$SIG $BIN $OPTS $INPUT\n"
            fi
    esac

    printf "$MSG"
    printf "$MSG" >> $LOGFILE

    # Append shell errors if they exist
    if [ -s $SHELL ]; then
        printf "    Shell messages:\n" >> $LOGFILE
        nl $SHELL >> $LOGFILE
    fi

    # Append program errors if they exist
    if [ -s $ERRORS ]; then
        printf "    Program output:\n" >> $LOGFILE
        nl $ERRORS >> $LOGFILE
    fi
}

LEN="${#@}"
DIR="${@:$LEN}"
FLAGS="${@:1:$(($LEN - 1))}"

# Run the submission
if [ -d "$DIR" ]; then
    USER=$(basename "$DIR")
    BIN="$DIR/ass2"
    OUT="$DIR/out"
    LOGFILE="$OUT/dumb.txt"

    printf "************************************************\n" > $LOGFILE
    printf "* Testing collide_dumb()\n" >> $LOGFILE
    printf "************************************************\n" >> $LOGFILE

    # Check whether the executable exists
    if [ ! -x $BIN ]; then
        printf "Not found: $BIN\n"
        printf "Not found: $BIN\n" >> $LOGFILE
        exit 127
    fi

    for SEED in 45 95; do
        for SIZE in 30 60 120; do
            INPUT="$TESTS/int.in"
            OUTPUT="$OUT/dumb.n$SIZE.s$SEED.col"

            # Location of the scaffolding binary
            SCAFFOLD="$DIR/scaffold -c $SIZE $SEED 5"

            OPTS="$FLAGS -n $SIZE -s $SEED -c d -h u -t o"

            # Braces are for errors that originate from the shell
            { $TIMEOUT $BIN $OPTS $INPUT > $OUTPUT 2> $ERRORS; } &> $SHELL

            exit_codes $?

            COUNT=$((COUNT + 1))
        done
    done
    printf "\n$PASS/$COUNT successful\n" >> $LOGFILE
fi

exit $((! ($PASS == $COUNT)))
