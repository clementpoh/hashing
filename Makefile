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
STREQ	= $(SCRIPTS)/streq.sh
SIZE	= $(SCRIPTS)/size.sh
PROBE	= $(SCRIPTS)/probe.sh
BAD		= $(SCRIPTS)/bad.sh
UNIV	= $(SCRIPTS)/univ.sh

# Header and source files submissions depend on
HDR		= $(wildcard $(SCAFDIR)/*.h)
BASE    = main.c scaffold.c list.c array.c hashtable.c
SRC		= $(foreach src,$(BASE),$(SCAFDIR)/$(src))

# The submission of an individual student
SUBS 	= $(shell /usr/bin/find $(SUBDIR) -mindepth 1 -maxdepth 1 -type d)
STUDBIN	= $(addsuffix /ass2,$(SUBS))

# Test artifacts
STUDSUMMARY	= $(addsuffix /summary.txt,$(SUBS))
STUDMAKE	= $(addsuffix /out/make.txt,$(SUBS))
STUDSTRIO 	= $(addsuffix /out/strio.txt,$(SUBS))
STUDSTREQ 	= $(addsuffix /out/streq.txt,$(SUBS))
STUDSIZE 	= $(addsuffix /out/size.txt,$(SUBS))
STUDPROBE	= $(addsuffix /out/probe.txt,$(SUBS))
STUDBAD		= $(addsuffix /out/bad.txt,$(SUBS))
STUDUNIV	= $(addsuffix /out/univ.txt,$(SUBS))

# Expected outputs
STRPRINT	= $(patsubst %.in,%.out,$(wildcard $(TESTDIR)/*.in))
STRFIND		= $(patsubst %.in,%.eq,$(wildcard $(TESTDIR)/*.in))
HASHUNIV	= $(patsubst %.in,%.univ,$(wildcard $(TESTDIR)/*.in))

SEED	= -s 11

# Rules

.PHONY: all compile strio streq size probe
all: $(SOLNDIR) $(TESTDIR)

spec.pdf: spec.tex
	pdflatex spec.tex && rm spec.log spec.aux

# Rules to run tests on all submissions

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
strio.log: $(STRIO) $(STRPRINT) compile.log
	$(FOREACH) $(STRIO) $(SUBDIR) 2>&1 | tee $@

streq: streq.log
streq.log: $(STREQ) $(STRFIND) compile.log
	$(FOREACH) $(STREQ) $(SUBDIR) 2>&1 | tee $@

size: size.log
size.log: $(SIZE) compile.log
	$(FOREACH) $(SIZE) $(SUBDIR) 2>&1 | tee $@

probe: probe.log
probe.log: $(PROBE) compile.log
	$(FOREACH) $(PROBE) $(SUBDIR) 2>&1 | tee $@

bad: bad.log
bad.log: $(BAD) compile.log
	$(FOREACH) $(BAD) $(SUBDIR) 2>&1 | tee $@

univ: univ.log
univ.log: $(UNIV) $(HASHUNIV) compile.log
	$(FOREACH) $(UNIV) $(SEED) $(SUBDIR) 2>&1 | tee $@

# Rules to generate test cases
.PHONY: $(TESTDIR)
$(TESTDIR): $(TESTDIR)/empty $(TESTDIR)/ints.in $(TESTDIR)/str.in
	touch $(TESTDIR)/empty
	seq 1 50 > $(TESTDIR)/ints.in

# STRPRINT expands to the next rule
$(TESTDIR)/%.out: $(TESTDIR)/%.in $(SOLN) Makefile
	$(SOLN) -t s -p $< > $@

# STRFIND expands to the next rule
$(TESTDIR)/%.eq: $(TESTDIR)/%.in $(SOLN) Makefile
	$(SOLN) -t s -f $(basename $<).keys $< > $@

# HASHUNIV expands to the next rule
$(TESTDIR)/%.univ: $(TESTDIR)/%.in $(SOLN) Makefile
	$(SOLN) $(SEED) -t s -f $(basename $<).keys -h u $< > $@

# Rules for an individual submission
.PHONY: $(SUBDIR) $(SUBS)
$(SUBDIR): $(SUBS)

$(SUBS): % : %/summary.txt

# Rule to compile the student binary
.SECONDARY: $(STUDBIN)
$(STUDBIN): %/ass2 : %/extra.c %/types.c %/hash.c $(HDR) $(SRC)
	-$(COMPILE) $(@D)

$(STUDSTRIO): %/out/strio.txt : %/ass2 $(STRIO) $(STRPRINT)
	-$(STRIO) $(subst /out,,$(@D))

$(STUDSTREQ): %/out/streq.txt : %/ass2 $(STREQ) $(STRFIND)
	-$(STREQ) $(subst /out,,$(@D))

$(STUDSIZE): %/out/size.txt : %/ass2 $(PRINT)
	-$(SIZE) $(subst /out,,$(@D))

$(STUDPROBE): %/out/probe.txt : %/ass2 $(PROBE)
	-$(PROBE) $(subst /out,,$(@D))

$(STUDBAD): %/out/bad.txt : %/ass2 $(BAD)
	-$(BAD) $(subst /out,,$(@D))

$(STUDUNIV): %/out/univ.txt : %/ass2 $(UNIV) $(HASHUNIV)
	-$(UNIV) $(SEED) $(subst /out,,$(@D))

$(STUDSUMMARY): %/summary.txt : %/ass2 \
   	%/out/strio.txt %/out/streq.txt %/out/size.txt %/out/probe.txt \
	%/out/bad.txt %/out/univ.txt
	-cat $(@D)/lms.txt > $@
	-cat $(@D)/out/make.txt >> $@
	-cat $(@D)/out/strio.txt >> $@
	-cat $(@D)/out/streq.txt >> $@
	-cat $(@D)/out/size.txt >> $@
	-cat $(@D)/out/probe.txt >> $@
	-cat $(@D)/out/bad.txt >> $@
	-cat $(@D)/out/univ.txt >> $@

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

.PHONY: cleantests
cleantests:
	-rm -rf test/*.eq test/*.out test/*.bad test/*.univ

.PHONY: clobber
clobber: clean cleantests
	-rm -rf *.log \
	   	$(SUBDIR)/**/out
