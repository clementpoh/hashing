COMP20007 Assignment 2 Marking Scheme
=====================================

The `summary.txt` that resides in each student folder shows the commands used
to test and verify each submission task.

The log files on the top level replicate this information and do not offer
anymore detailed information.

Practical (10 marks)
====================

Part A0: Working with strings (1 mark)
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
0    | Inconsistent: Reinitialises coefficients on every call.
0    | Failed all.

E & F: Collisions (2 marks each)
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

### Marking Scheme ###

Mark | Condition
---- | -------------------------------------------------------------------
2    | Submission passes all test cases and makes no mistakes below.
-0.5 | Does not follow output specification, e.g. `hash.orig.c` exists.
-0.5 | Any printed coefficients are larger than size.
-0.5 | `FPE`: Floating point error, or arithmetic error.
-0.5 | Prints out more or less than `n` (5 for testing) strings.
1.5  | Fails replica hash but passes official official hash.
1    | Fails some test cases.
1    | Only one string hashes to zero in each test case.
0    | Failed all.


General Coding style
--------------------
Please look out for the issues below and deduct marks accordingly.
+    Student not identifying themselves at the top of every submission file.
+    Magic numbers.


Report (10 marks)
=================

As per Vanessa's guidance.

### Theory of hash functions and hash tables ###

Q1 (1 mark)
-----------

Suppose the hash function hashes everything to the same bucket. Using big-O
notation, write the complexity of insert and search in terms of `size` and `n`. Justify your answer.

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Both O(n).
1    | Insert O(1) if prepend is specified, O(n) search.
0.5  | One O(n).
0    | Otherwise.

Q2 (1 mark)
-----------

Suppose the hash function spreads the input perfectly evenly over all the
buckets. Using big-O notation, write the complexity of insert and search in
terms of `size` and `n`. Justify your answer.

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Both O(n / size).
1    | Insert O(1) if prepend is specified, O(n/size) search.
0.5  | One O(n / size).
0    | Otherwise.

Q3 (1 mark)
-----------

Suppose that the hash function never hashes two different inputs to the same
bucket. Using big-O notation, write the complexity of insert and search in terms of `size` and `n`. Justify your answer.

Mark | Condition
---- | ---------------------------------------------------------------------
1    | Both O(1).
0.5  | One O(1).
0    | Otherwise.

Q4 (1 mark)
-----------

Why is this a bad hash function? Give some example input on which the hash table would behave badly if it was using this hash function.

### 1 mark ###

+    If `a` was generated differently for each call to the function, then it
     doesn't even hash the same thing to the same place, so it clearly doesn't
     work.

+    If `a` remains static (so at least it's a real hash function), it's still
     bad because any two strings with the same first character will hash to the
     same place.

Q5 (3 marks)
------------

Average-case analysis. Assume that `r0`, `r1`, . . . are chosen randomly and
independently of the list of inputs. Using big-O notation, write the expected
complexity of insert and search in terms of size and n. Justify your answer.

### 3 marks ###

O(n/size). For full marks, I expect some version of the argument in Dasgupta
that the probability of two items colliding is 1/n. (Strictly speaking, this
doesn't prove that the probability of n/size colliding is small, but we'll let
that go.) Full marks for a specific reference to the collision property
mentioned on p.37 of Dasgupta, even if the argument is not reiterated.

If they make it clear that they understand that universal hashing implies an
even distribution over buckets, then they can have full (3) marks.

### 2 marks ###

O(n/size) and arguing that each individual element has probability 1/n of
hashing to any particular i, without noticing that it's the collision
probability that matters.

#### Sample answers ####

Student 1:

    Considering only the average case, the time complexity for both insert and
    search is O(n/size), that is, unless you keep track of the tail in the
    linked lists of each bucket in which case the insert function has a
    constant time complexity. This is because the universal hash function is
    expected to distribute the items amongst the buckets quite evenly. On an
    even distribution, the number of items in each bucket is n/size. This
    indicates that searching would take O(n/size) because it has to go through
    n/size items, and the same thing for insertion.

**VT**: 3 marks, for saying "universal hash function is expected to distribute the
items amongst the buckets quite evenly."

Student 2:

    If the co-efficients [r0, r1, . . .] are indeed chosen randomly and
    independently of the list of inputs, there is no reason that getting a
    remainder between [0… size-1] is any more likely than any other remainder
    in that range. So there is almost an equal probability of hashing to any
    bucket in the hashtable (a probability of 1/H), which essentially means
    that all keys are theoretically spread over the table relatively evenly.
    The average case running time then, is primarily determined by the average
    size of a bucket which is, n/size (since the hashing is relatively even).

**VT**: This is a real borderline case, as it doesn't mention universal hashing,
and doesn't seem to understand that it's collisions, rather than individual
probabilities, that determine insertion and search size.  I say this falls into
the second case of my first set of guidelines "2 marks out of 3 for getting the
O(.) right and arguing that each individual element has prob 1/n of hashing to
any particular i, without noticing that it's the collision prob that matters."
The point is that this student derives the "evenly spread" claim from the equal
prob of any individual item hashing to any particular bucket, which isn't in
general valid.  To get full marks, they either have to derive that themselves
or make it clear they know it's a property of the universal hash function.

Student 3:

    Average-case analysis: Assume that r0, r1, . . . are chosen randomly and
    independently of the list of inputs. Using big-O notation, write the
    expected complexity of insert and search in terms of size and n. Justify
    your answer.  Using random independent numbers when universal hashing gives
    pseudo-randomness to where each value will be hashed. It can be assumed
    that each bucket will receive a similar number of elements due to this,
    however it is possible that another element will be hashed to the same
    value. Therefore, each bucket will have approximately 𝑛/size elements each,
    which suggests Insert and Search times of O(n/size)

**VT**: 3 marks.  Poorly expressed, but successfully mentions universal hashing
implying that each bucket would receive similar numbers of elements.

Student 4:

    Since, for a universal hash function, the probability of hashing two items
    to the same bucket is 1/size then there will only by n/size collisions.
    Since, for every collision, the lookup will increase by O(1) we will have a
    total insert and search time of O(n/size).

**VT**: 2 marks.  1 for getting the answer O(n/size) right.  One more because the
keywords are present (universal hashing, and collision probabilities).  But the
mathematical argument is just downright wrong.  It's saying that there will be
only n/size collisions, when in fact there will be n/size items colliding per
bucket. It's saying that each collision increases the lookup time by O(1), when
in fact it's really `O(bucket_size / table_size)`.

Student 5:

    Insert has an expected complexity of O(𝑛/𝑠𝑖𝑧𝑒) and search has an expected
    complexity of O(𝑛/𝑠𝑖𝑧𝑒). As the complexity of insert and search is
    proportional to the average number of items hashed to one hash table
    bucket, the complexity of both the hash functions is proportional to the
    number of items per hash table bucket, which assuming there is a relatively
    uniform distribution across the hash table , is 𝑛/𝑠𝑖𝑧𝑒 on average, resulting
    in complexity of O(𝑛/𝑠𝑖𝑧𝑒) in the general case. However, if size is much
    larger than n (around 2+ times), the average case complexity for search and
    insert is O(1), as most buckets would have 0 or 1 items. (Which is what
    usually happens in good real-world hash function implementations.)

**VT**: 2 marks.  One for getting the answer O(n/size) right.  One for noticing
that there is a relatively uniform distribution across the hash table.  But
"assuming" is not enough for the third mark: there needed to be a statement
that this is true because it's a universal hash function, or an argument as to
why it's true.

Student 6:

    Assuming r1, r2, ... are randomly distributed, each bucket should be evenly
    loaded, so insert is expected to take O(1), hash + append, and search
    O(n/size), as each bucket is expected to have n/size elements.

**VT**: 2 marks.  Same as Student 5.  "should be" doesn't cut it.  Also, although
O(1) is OK for insert with prepend, this student has written O(1) for hash plus
append.  Sigh.

Everything else gets 0.


Q6 (1 mark)
-----------

Explain briefly (in a few sentences) how your algorithm works. Using big-O
notation, write the expected running time of your algorithm, for generating 2
hashes to 0 in a table of size size.


Most people should have a O(size) algorithm. Full marks for a sensible
explanation of how it works.

Q7 (2 marks)
------------

Explain briefly (about half a page) how your algorithm works. Using big-O
notation, write the expected complexity of your algorithm in terms of size.
Justify your answer. You can assume that integer operations (like + and *) take
a constant amount of time.


The answer I was expecting was to use extended Euclid as described in my *LMS*
message, but shifting a character up or down to get to zero.  There were,
however, so many other sensible ways of doing this that I'm willing to accept
them all, as long as they're reasonably clearly explained.

Optional
========

Q8 Hashing questions
--------------------
1. 2<sup>255</sup> to get a string of all 1's, with 50% probability.
2. 2<sup>29</sup> to get a string with 30 zeros, with 50% probability.

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



