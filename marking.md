COMP20007 Assignment 2 Marking Scheme
=====================================

The `summary.txt` that resides in each student folder shows the commands used
to test and verify each submission task.

The log files on the top level replicate this information and do not offer
anymore detailed information.

Universal Hash
--------------

Universal hash is supposed to be able to handle strings up to `MAXSTRLEN` in
length. If a student's `universal_hash()` does not multiply each character in
the input string with a random coefficient deduct 0.5.

E.g. Some submissions only use the first five coefficients and characters of
the input strings.

Mark | Condition                                                          
---- | ---------------------------------------------------------------------
2    | Submission passes all test cases and makes no mistakes below.
-0.5 | Not all `MAXSTRLEN` coefficients used on strings `MAXSTRLEN` long.
-0.5 | Any universal hash coefficients are larger than size.
-0.5 | Calls `srand()` within `universal_hash()`.
1.5  | Inconsistent: In edge cases would re-initialise some coefficients.
1    | Inconsistent: Reinitialises zero coefficients on subsequent calls.
0.5  | Inconsistent: Reinitialises coefficients on subsequent calls.
0    | Failed all.

Collisions
----------

The functions `collide_dumb()` and `collide_clever()` are functionally
identical. Each are worth 2 marks. Only deduct marks once for entries marked
-0.5 in the table if the mistake is made in both collide dumb and collide
clever.

The testing suite asks each submission for five colliding strings. The
scaffold program reads the outputs of each submission and passes the test
cases if it can hash at least two strings to zero with the coefficients
printed by the program.

The scaffold program uses three implementations of the `universal_hash()`
function to hash each string.

+   The `replica` hash reads in the coefficients that the submission prints
    out and hashes the input string against that. This is the hash function
    that is used to pass or fail the submission.

+   The `official` hash is my implementation of the universal hash.

+   The `student` hash is the student's implementation of the universal hash.

It's quite possible that if the student did not correctly print out the
coefficients, their output strings would fail the replica hash. However their
strings may still be hashed to zero by the official universal hash, or their
own implementation of the universal hash.

Mark | Condition                                                          
---- | -------------------------------------------------------------------
2    | Submission passes all test cases and makes no mistakes below.
-0.5 | Submission does not follow output specification, e.g. `hash.orig.c`.
-0.5 | Any printed coefficients are larger than size.
-0.5 | `FPE`: Floating point error, or arithmetic error.
-0.5 | Prints out more or less than `n` (5 for testing) strings.
1.5  | Fails replica hash but passes official official hash.
1    | Only one string hashes to zero.
0    | Failed all.

Appendix A: From the specification
----------------------------------

### Submission ###

The four coding parts of the assignment will be marked as follows:

+   You will lose a mark if your submission does not identify you in the
    opening comment of each submitted file.

+   You will lose a mark if your solution is incorrect in some way (breaks on
    certain inputs, has memory leaks, requires fixing to work at all).

+   You will lose a mark if your solution is difficult to interpret (minimal or
    unhelpful comments, obscure variable names).

+   The report will get full marks if it is a succinct, factual report on
    running times including a discussion comparing times to big-O bounds.

+   You will lose marks for missing timing results, missing graph, missing
    big-O discussion.

### Submission ###

+   It should unpack into a folder, where the folder is named using your
    student ID.

+   Submissions not adhering to these requirements will be subject to a 2 point
    penalty.

