Design of Algorithms Assignment 2
=================================

This is the solution and test suite for COMP20007 Design of Algorithms
Assignment 2 semester 1 2016.

Students were tasked with implementing topological sorting algorithms in C.
The detailed specification can be found in the file _spec.tex_.

Compatibility
-------------

The scripts and non-student source files were designed for Unix platforms. They
were written, tested and executed in _Arch Linux_; however, they should work
without difficulty on other Linux distributions.

The scripts were also run and tested on _MinGW_, working with slight
differences. The exit codes that are returned by programs running in _MinGW_
differ to conventional Unix exit codes.

The list module uses an internal function in its implementation of `filter()`.
The default C compiler on _OSX_ does not support these extensions, so either
the _filter()_ function definition needs to be deleted or the GNU C compiler
needs to be installed when running the scripts on Mac computers.

Usage
-----

The Makefile takes care of the dependencies. It automatically builds each
submission, solution, and expected outputs where necessary.

The following commands are most important:

+   `make complete`

    Runs all test scripts on all submissions if Make can't detect the
    script's corresponding log file.

+   `make subs/subdirectory`

    Runs all test scripts on one submission directory: _subs/subdirectory_.

+   `make clean`
    + Cleans the solution directory
    + Deletes the header files, `Makefile`s, and non-submission C files from
      each submission directory.
    + Deletes the `ass2` and `scaffold` binaries from each submission directory.

+   `make cleantests`
    + Deletes generated verification files from the `test` folder.

+   `make clobber`
    + Does everything `make clean` and `make cleantests` does.
    + Deletes the summary report from each submission folder.
    + Deletes the `out` folder from each submission directory, where
      submission outputs reside.

### Test reports ###

Each script keeps a log and it also prints separately to `stdout`.

The messages printed to `stdout` are a human readable form of the program exit
signal when run on a test case and the command that was called on the test case.

Below is a table of common signals and what they mean in the context of the
assignment.

| Signal | Meaning                                                      |
| ------ | ------------------------------------------------------------ |
| `PASS` | Output matches expected output                               |
| `FAIL` | `EXIT_SUCCESS` but output does not match expected output     |
| `EXIT` | `EXIT_FAILURE` is unexpected or issue with submission output |
| `TERM` | Program terminated, usually timeout                          |
| `KILL` | Program killed, usually timeout                              |
| `SEGV` | Segmentation fault                                           |
| `ABRT` | Program aborted, assertion failure or memory errors          |
| `FPE`  | Arithmetic error, like a division by zero                    |

The log resides in the _out/_ directory of the submission folder. The log
states whether a test either passed or failed, any program output and shell
messages.

### Test case timeout ###

Each individual test case is given *9 seconds* to run through an individual
test case before it is terminated or killed. The timeout can be revised in
the `scripts/timeout.sh` file.

If a test case is terminated, it will appear as a *TERM* or *KILL* in the
report, even if if it may actually be correct.

### Submission testing ###

After `make subs/user-STUDENTID` the submission directory contents are as
follows:

    subs/user-STUDENTID/
    ├── array.c             # Copied from scaffolding
    ├── array.h             # Copied from scaffolding
    ├── ass2
    ├── extra.c
    ├── extra.h             # Copied from scaffolding
    ├── hash.c
    ├── hash.h              # Copied from scaffolding
    ├── hashtable.c         # Copied from scaffolding
    ├── hashtable.h         # Copied from scaffolding
    ├── list.c              # Copied from scaffolding
    ├── list.h              # Copied from scaffolding
    ├── lms.txt             # From the LMS
    ├── main.c              # Copied from scaffolding
    ├── Makefile            # Copied from scaffolding
    ├── official.c          # Official implementations of functions
    ├── official.h          # Copied from scaffolding
    ├── out
    │   ├── bad.txt         # Results of bad hash stage
    │   ├── clever.txt      # Results of collide clever stage
    │   ├── dumb.txt        # Results of collide dumb stage
    │   ├── make.txt        # Compiler warnings
    │   ├── probe.txt       # Results of linear probe stage
    │   ├── size.txt        # Results of the determine size stage
    │   ├── streq.txt       # Generated during the string equality stage
    │   ├── strio.txt       # Generated during the string IO stage
    │   ├── *.out           # Generated during the string IO stage
    │   ├── *.eq            # Generated during the string equality stage
    │   ├── clever.*.col    # Generated during the collide clever stage
    │   ├── dumb.*.col      # Generated during the collide dumb stage
    │   ├── int.*.uni       # Generated during the universal hash stage
    │   ├── str.*.uni       # Generated during the universal stage
    │   └── uni.txt         # Results of universal hash stage
    ├── scaffold            # Scaffolding program to test individual functions
    ├── scaffold.c          # Copied from scaffolding
    ├── types.c
    └── types.h             # Copied from scaffolding

Scaffolding
-----------

The `main.c` that is copied to each submission through the compilation process
differs to the `main.c` provided to the students as skeleton code.

+   There is a new option `-t o` that switches to using official
    implementations of `str_eq()`, `str_copy()`, `str_print()` and
    `determine_size()`.

+   There is a new option `-g n` where n is the number of collisions
    `collide_dumb()` and `collide_clever()` need to generate.

There is also an executable `scaffold` that calls student implemented functions
by calling them directly.

Directory structure
-------------------

This is a diagram of the whole directory structure with short descriptions for
notable files.

    hashing
    ├── bad.log         # Results of the bad hash stage
    ├── changelog.md    # Documents changes to submissions to run them
    ├── clever.log      # Results of the collide clever stage
    ├── compile.log     # Results of the compilation stage
    ├── dumb.log        # Results of the collide dumb stage
    ├── probe.log       # Results of the linear probe stage
    ├── streq.log       # Results of string equality stage
    ├── strio.log       # Results of string IO stage
    ├── size.log        # Results of determine size stage
    ├── uni.log         # Results of universal hashing stage
    ├── unpack.log      # Results of unpacking zip from LMS
    ├── README.md       # This file
    ├── scaffold
    │   ├── array.c
    │   ├── array.h
    │   ├── extra.h
    │   ├── hash.h
    │   ├── hashtable.c
    │   ├── hashtable.h
    │   ├── list.c
    │   ├── list.h
    │   ├── main.c
    │   ├── Makefile
    │   ├── official.c  # Official implementations needed for later stages
    │   ├── official.h
    │   ├── scaffold.c  # Program to test and call student functions directly
    │   └── types.h
    ├── skeleton        # Skeleton code supplied to students
    │   └── ...
    ├── scripts
    │   ├── bad.sh
    │   ├── clever.sh
    │   ├── compile.sh
    │   ├── dumb.sh
    │   ├── foreach.sh
    │   ├── probe.sh
    │   ├── size.sh
    │   ├── streq.sh
    │   ├── strio.sh
    │   ├── timeout.sh
    │   ├── uni.sh
    │   └── unpack.sh
    ├── soln
    │   └── ...
    ├── spec.tex
    ├── subs
    ├── test
    │   ├── int.in      # List of numbers
    │   ├── int.keys    # List of numbers, some present in int.in
    │   ├── str.in      # List of strings
    │   ├── str.keys    # List of strings, some present in str.in
    │   ├── *.eq
    │   ├── *.uni
    │   └── *.out       # Verification file for string IO
    └── Makefile

