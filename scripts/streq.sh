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
        0)  if diff -w "$OUTPUT" "$VERIFY" &> /dev/null; then
                MSG="PASS $BIN $OPTS $INPUT\n"
                PASS=$((PASS + 1))
            else
                MSG="FAIL $BIN $OPTS $INPUT | diff -w $VERIFY -\n"
            fi ;;
        1)  # Indicates that program exited with EXIT_FAILURE
            MSG="$EXIT EXIT_FAILURE $BIN $OPTS $INPUT\n";;
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
    printf "    diff -w $VERIFY $OUTPUT\n" >> $LOGFILE

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
    LOGFILE="$OUT/streq.txt"

    printf "************************************************\n" > $LOGFILE
    printf "* Working with strings: str_copy() and str_eq()\n" >> $LOGFILE
    printf "************************************************\n" >> $LOGFILE

    # Check whether the executable exists
    if [ ! -x $BIN ]; then
        printf "Not found: $BIN\n"
        printf "Not found: $BIN\n" >> $LOGFILE
        exit 127
    fi

    INPUTS="$TESTS/*.in"
    for INPUT in $INPUTS; do
        BASE=$(basename $INPUT ".in")
        # Location of the output dot file
        OUTPUT="$OUT/$BASE.eq"
        # Location of the verification file
        VERIFY="$TESTS/$BASE.eq"

        KEYS="$TESTS/$BASE.keys"

        OPTS="$FLAGS -t s -f $KEYS"

        # Braces are for errors that originate from the shell
        { $TIMEOUT $BIN $OPTS $INPUT > $OUTPUT 2> $ERRORS; } &> $SHELL

        exit_codes $? $BIN $OPTS $INPUT

        COUNT=$((COUNT + 1))
    done
    printf "\n$PASS/$COUNT successful\n" >> $LOGFILE
fi

# The $((expr)) works like in C, so negate it to get the correct exit status
exit $((! ($PASS == $COUNT)))
