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
STRIO   = $(SCRIPTS)/strio.sh
SIZE	= $(SCRIPTS)/size.sh
PROBE	= $(SCRIPTS)/probe.sh

# Header and source files submissions depend on
HDR		= $(wildcard $(SCAFDIR)/*.h)
BASE    = main.c scaffold.c list.c array.c hashtable.c
SRC		= $(foreach src,$(BASE),$(SCAFDIR)/$(src))

# The submission of an individual student
SUBS 		= $(shell /usr/bin/find $(SUBDIR) -mindepth 1 -maxdepth 1 -type d)
STUDBIN 	= $(addsuffix /ass2,$(SUBS))
STUDSTRIO 	= $(addsuffix /out/strio.txt,$(SUBS))
STUDSTREQ 	= $(addsuffix /out/streq.txt,$(SUBS))
STUDSIZE 	= $(addsuffix /out/size.txt,$(SUBS))
STUDPROBE	= $(addsuffix /out/probe.txt,$(SUBS))

# Test artifacts
STUDSUMMARY	= $(addsuffix /summary.txt,$(SUBS))
STUDMAKE	= $(addsuffix /out/make.txt,$(SUBS))
STUDSTRING  = $(addsuffix /out/strio.txt,$(SUBS))

# Expected outputs
HTPRINTS = $(patsubst %.in,%.out,$(wildcard $(TESTDIR)/*.in))

# Rules to run tests on all submissions

.PHONY: all
all: $(SOLNDIR) $(HTPRINTS) $(TESTDIR)

.PHONY: $(SOLNDIR)
$(SOLNDIR): $(SOLN)

.SECONDARY: $(SOLN)
$(SOLN):
	$(MAKE) -C $(SOLNDIR)
	$(MAKE) -C $(SOLNDIR) clean

unpack: unpack.log
unpack.log: $(UNPACK)
	$(UNPACK) $(SUBDIR) 2>&1 | tee $@

compile: compile.log
compile.log: $(COMPILE) $(HDR) $(SRC) unpack.log
	$(FOREACH) $(COMPILE) $(SUBDIR) 2>&1 | tee $@

strio: strio.log
strio.log: $(STRIO) $(HTPRINTS) compile.log
	$(FOREACH) $(STRIO) $(SUBDIR) 2>&1 | tee $@

size: size.log
size.log: $(SIZE) compile.log
	$(FOREACH) $(SIZE) $(SUBDIR) 2>&1 | tee $@

probe: probe.log
probe.log: $(PROBE) compile.log
	$(FOREACH) $(PROBE) $(SUBDIR) 2>&1 | tee $@

# Rules to generate test cases
.PHONY: $(TESTDIR)

$(TESTDIR): $(TESTDIR)/empty $(TESTDIR)/ints.in $(TESTDIR)/str.in
	touch $(TESTDIR)/empty
	seq 1 50 > $(TESTDIR)/ints.in

# HTPRINTS expands to the next rule
$(TESTDIR)/%.out: $(TESTDIR)/%.in $(SOLN)
	$(SOLN) -p -t s $< > $@

# Rules for an individual submission

# Rule to compile the student binary
.SECONDARY: $(STUDBIN)
$(STUDBIN): %/ass2 : %/extra.c %/types.c %/hash.c $(HDR) $(SRC)
	-$(COMPILE) $(@D)

$(STUDSTRIO): %/out/strio.txt : %/ass2 $(STRIO) $(HTPRINTS)
	-$(STRIO) $(subst /out,,$(@D))

$(STUDSIZE): %/out/size.txt : %/ass2 $(PRINT) $(DOTS)
	-$(SIZE) $(subst /out,,$(@D))

spec.pdf: spec.tex
	pdflatex spec.tex && rm spec.log spec.aux

# Rules to clean up
.PHONY: clean
clean:
	$(MAKE) -C $(SOLNDIR) clobber
	$(MAKE) -C $(SCAFDIR) clobber
	-rm -rf spec.pdf \
		$(SUBDIR)/**/ass2 \
		$(SUBDIR)/**/scaffold \
		$(SUBDIR)/**/*.exe \
	   	$(SUBDIR)/**/*.h \
		$(SUBDIR)/**/list.c \
		$(SUBDIR)/**/hashtable.c \
		$(SUBDIR)/**/array.c \
		$(SUBDIR)/**/main.c \
		$(SUBDIR)/**/scaffold.c \
		$(SUBDIR)/**/Makefile

.PHONY: clobber
clobber: clean
	-rm -rf $(SUBDIR)/**/out
