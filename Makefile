# Makefile
#
# Clement Poh
#
# Makefile to test COMP20007 2016 Assignment 2 submissions
#

# Subdirectories
SOLNDIR	= soln
SUBDIR	= subs
SCRIPTS = scripts
TESTDIR	= test
SCAFDIR = scaffold

# Solution binaries
SOLN	= $(SOLNDIR)/soln

# Scripts to execute
FOREACH = $(SCRIPTS)/foreach.sh
UNPACK  = $(SCRIPTS)/unpack.sh
COMPILE = $(SCRIPTS)/compile.sh
STRING  = $(SCRIPTS)/string.sh

# Header and source files submissions depend on
HDR		= $(wildcard $(SCAFDIR)/*.h)
BASE    = main.c list.c array.c hashtable.c
SRC		= $(foreach src,$(BASE),$(SCAFDIR)/$(src))

# The submission of an individual student
SUBS	= $(shell /usr/bin/find $(SUBDIR) -mindepth 1 -maxdepth 1 -type d)
STUDBIN = $(addsuffix /ass2,$(SUBS))

# Test artifacts
STUDSUMMARY	= $(addsuffix /summary.txt,$(SUBS))
STUDMAKE	= $(addsuffix /out/make.txt,$(SUBS))
STUDSTRING  = $(addsuffix /out/string.txt,$(SUBS))

# Expected outputs
TYPES = $(patsubst %.in,%.out,$(wildcard $(TESTDIR)/*.in))

# Rules to run tests on all submissions

.PHONY: all
all: $(SOLNDIR) $(TYPES)

.PHONY: $(SOLNDIR)
$(SOLNDIR): $(SOLN)

.SECONDARY: $(SOLN)
$(SOLN):
	$(MAKE) -C $(SOLNDIR)
	$(MAKE) -C $(SOLNDIR) clean

unpack: unpack.log
unpack.log: $(UNPACK)
	$(UNPACK) $(SUBDIR) 2>&1 | tee unpack.log

compile: compile.log
compile.log: $(COMPILE) unpack.log
	$(FOREACH) $(COMPILE) $(SUBDIR) 2>&1 | tee compile.log

string: string.log
string.log: $(STRING) $(TYPES) compile.log
	$(FOREACH) $(STRING) $(SUBDIR) 2>&1 | tee string.log

# Rules to generate test cases
$(TESTDIR)/%.out: $(TESTDIR)/%.in $(SOLN)
	$(SOLN) -p -t s $< > $@

# Rules for an individual submission

# Rule to compile the student binary
.SECONDARY: $(STUDBIN)
$(STUDBIN): %/ass2 : %/extra.c %/types.c %/hash.c $(HDR) $(SRC)
	-$(COMPILE) $(@D)

spec.pdf: spec.tex
	pdflatex spec.tex && rm spec.log spec.aux

# Rules to clean up
.PHONY: clean
clean:
	$(MAKE) -C $(SOLNDIR) clobber
	-rm -rf spec.pdf \
		$(SUBDIR)/**/ass2 \
		$(SUBDIR)/**/*.exe \
	   	$(SUBDIR)/**/*.h \
		$(SUBDIR)/**/list.c \
		$(SUBDIR)/**/hashtable.c \
		$(SUBDIR)/**/array.c \
		$(SUBDIR)/**/main.c \
		$(SUBDIR)/**/Makefile
