COMP20007 Assignment 2 Marking Scheme
=====================================

The `summary.txt` that resides in each student folder shows the commands used
to test and verify each submission task.

The log files on the top level replicate this information and do not offer
anymore detailed information.

Practical (10 marks)
====================

Part A0 Working with strings (1 mark)
--------------------------------------

At this stage we use the student's `determine_size()`, so some tests may fail
if the student did not implement the function correctly.

If the test case fails, the summary displays the diff command that was used to
verify the program, which it failed.

For example: `diff -w ./test/int.out subs/cjpoh-269508/out/int.out`.

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Passes all test cases for first two sections.
0.5  | Fails any of the test cases not caused by hash table size.
0    | Fails all test cases.

Part A: `determine_size()` (1 mark)
-----------------------------------

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Passes test.
0    | Fails test.

Part B: Linear probing with double hashing (1 mark)
---------------------------------------------------

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Passes test, i.e. the function `linear_probe()` returns 1.
0    | Fails test.

Part C: Bad hash (1 mark)
-------------------------

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Passes test.
0    | Fails test.

D: Universal Hash (2 marks)
---------------------------

The automated test treats `universal_hash()` as a black box, it mainly tests
the consistency of hash function by inserting values into a hash table then
searching for them.

Universal hash is supposed to be able to handle strings up to `MAXSTRLEN` in
length. If a student's `universal_hash()` does not multiply each character in
the input string with a random coefficient deduct 0.5.

E.g. Some submissions only use the first five coefficients and characters of
the input strings.

If the test case fails, the summary displays the diff command that was used to
verify the program, which it failed.

For example: `diff -w ./test/int.out subs/cjpoh-269508/out/int.out`.

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

E & F: Collisions (4 marks each)
--------------------------------

The functions `collide_dumb()` and `collide_clever()` are functionally
identical. Each are worth 2 marks. Only deduct marks once for entries marked
-0.5 in the table if the mistake is made in both collide dumb and collide
clever.

The testing suite asks each submission for five colliding strings. The
scaffold program reads the outputs of each submission and passes the test
cases if it can hash at least two strings to zero with the coefficients
printed by the program.

It's quite possible that if the student did not correctly print out the
coefficients, their output strings would fail the replica hash. However their
strings may still be hashed to zero by the official universal hash, or their
own implementation of the universal hash.

The scaffold program uses three implementations of the `universal_hash()`
function to hash each string.

+   The `replica` hash reads in the coefficients that the submission prints
    out and hashes the input string against that. This is the hash function
    that is used to pass or fail the submission.

+   The `official` hash is my implementation of the universal hash.

+   The `student` hash is the student's implementation of the universal hash.

### Interpreting the summary ###

When the scaffolding reads in a string it first tries to read the universal
coefficients, then any number of strings until the `EOF`.

Below the student printed 5 coefficients then 5 strings. Each of the strings
hashed to 3 according to the coefficients they printed.

Each of the strings hashed to zero using the student's implementation of
universal hash.

Each of the strings hashed to zero using the official implementation of
universal hash.

I print out the first 10 `chars` of each string. In this case each string was
length 8 as determined by `strlen()`.

    hash:   3: student:   0 official:   0 len:   8, F▒u▒▒u▒
    hash:   3: student:   0 official:   0 len:   8, +!u▒▒u▒
    hash:   3: student:   0 official:   0 len:   8, h!u▒▒u▒
    hash:   3: student:   0 official:   0 len:   8, V"u▒▒u▒
    hash:   3: student:   0 official:   0 len:   8, D#u▒▒u▒
    total strings: 5, coefficients: 5
    hashed to zero - replica: 0 student: 5, official: 5

### Guide Scheme ###

Mark | Condition
---- | -------------------------------------------------------------------
2    | Submission passes all test cases and makes no mistakes below.
-0.5 | Submission does not follow output specification, e.g. `hash.orig.c`.
-0.5 | Any printed coefficients are larger than size.
-0.5 | `FPE`: Floating point error, or arithmetic error.
-0.5 | Prints out more or less than `n` (5 for testing) strings.
1.5  | Fails replica hash but passes official official hash.
1    | Only one string hashes to zero in each test case.
0    | Failed all.

Report (10 marks)
=================

As per Vanessa's guidance.

### Theory of hash functions and hash tables ###

Q1 (1 mark)
-----------

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Both O(n).
0.5  | One O(n).
0    | Otherwise.

Q2 (1 mark)
-----------

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Both O(n / size).
0.5  | One O(n / size).
0    | Otherwise.

Q3 (1 mark)
-----------

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Both O(1).
0.5  | One O(1).
0    | Otherwise.

Q4 (1 mark)
-----------

### 1 mark ###

If `a` was generated differently for each call to the function, then it
doesn't even hash the same thing to the same place, so it clearly doesn't work.

Also, if `a` remains static (so at least it's a real hash function), it's still
bad because any two strings with the same first character will hash to the same
place.

Q5 (3 marks)
------------

### 3 marks ###

O(n/size). For full marks, I expect some version of the argument in Dasgupta
that the probability of two items colliding is 1/n. (Strictly speaking, this
doesn't prove that the probability of n/size colliding is small, but we'll let
that go.)  Full marks for a specific reference to the collision property
mentioned on p.37 of Dasgupta, even if the argument is not reiterated.

### 2 marks ###

O(n/size) and arguing that each individual element has probability 1/n of
hashing to any particular i, without noticing that it's the collision
probability that matters.

Q6 (1 mark)
-----------

Most people should have a O(size) algorithm. Full marks for a sensible
explanation of how it works.

Q7 (2 marks)
------------

The answer I was expecting was to use extended Euclid as described in my *LMS*
message, but shifting a character up or down to get to zero.  There were,
however, so many other sensible ways of doing this that I'm willing to accept
them all, as long as they're reasonably clearly explained.

Optional
========

Q8 Hashing questions
--------------------
1. 2^255 to get a string of all 1's, with 50% probability.
2. 2^29 to get a string with 30 zeros, with 50% probability.

Block chain manipulation
------------------------
See the _brute force attack_ at https://en.bitcoin.it/wiki/Double-spending

The point of this question is that you could perform the same attack, but it
wouldn't have to be a brute-force attack, because you could use the clever way
of generating collisions.

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

