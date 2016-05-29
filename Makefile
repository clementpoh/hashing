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
UNI		= $(SCRIPTS)/uni.sh
DUMB	= $(SCRIPTS)/dumb.sh
CLEVER	= $(SCRIPTS)/clever.sh

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
STUDUNI		= $(addsuffix /out/uni.txt,$(SUBS))
STUDDUMB	= $(addsuffix /out/dumb.txt,$(SUBS))
STUDCLEVER	= $(addsuffix /out/clever.txt,$(SUBS))

# Expected outputs
seeds	= 45 95
sizes	= 10 50

STRPRINT= $(patsubst %.in,%.out,$(wildcard $(TESTDIR)/*.in))
STRFIND	= $(patsubst %.in,%.eq,$(wildcard $(TESTDIR)/*.in))
HASHUNI = $(foreach n, $(sizes),\
		  	$(foreach s,$(seeds),\
		  		$(patsubst %.in,%.n$n.s$s.uni,$(wildcard $(TESTDIR)/*.in))))

seed	= $(shell echo $(1) | sed -r "s/.*\.s([0-9]*).*\.uni/\1/g")
size	= $(shell echo $(1) | sed -r "s/.*\.n([0-9]*).*\.uni/\1/g")
keys	= $(shell echo $(1) | sed -r "s/(.*)\..*\..*\.uni/\1/g").keys
in		= $(shell echo $(1) | sed -r "s/(.*)\..*\..*\.uni/\1/g").in

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

uni: uni.log
uni.log: $(UNI) $(HASHUNI) compile.log
	$(FOREACH) $(UNI) $(SUBDIR) 2>&1 | tee $@

dumb: dumb.log
dumb.log: $(DUMB) compile.log
	$(FOREACH) $(DUMB) $(SUBDIR) 2>&1 | tee $@

clever: clever.log
clever.log: $(CLEVER) compile.log
	$(FOREACH) $(CLEVER) $(SUBDIR) 2>&1 | tee $@

# Rules to generate test cases
.PHONY: $(TESTDIR)
$(TESTDIR): $(STRPRINT) $(STRFIND) $(HASHUNI)

# STRPRINT expands to the next rule
$(TESTDIR)/%.out: $(TESTDIR)/%.in $(SOLN) Makefile
	$(SOLN) -t s -p $< > $@

# STRFIND expands to the next rule
$(TESTDIR)/%.eq: $(TESTDIR)/%.in $(SOLN) Makefile
	$(SOLN) -t s -f $(basename $<).keys $< > $@

$(HASHUNI): $(TESTDIR)/int.in $(TESTDIR)/str.in $(SOLN) Makefile
	$(SOLN) -t s -f $(call keys,$@) -s $(call seed,$@) -h u $(call in,$@) -n $(call size,$@) > $@

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

$(STUDUNI): %/out/uni.txt : %/ass2 $(UNI) $(HASHUNI)
	-$(UNI) $(subst /out,,$(@D))

$(STUDDUMB): %/out/dumb.txt : %/ass2 $(DUMB)
	-$(DUMB) $(subst /out,,$(@D))

$(STUDCLEVER): %/out/clever.txt : %/ass2 $(CLEVER)
	-$(clever) $(subst /out,,$(@D))

$(STUDSUMMARY): %/summary.txt : %/ass2 \
   	%/out/strio.txt %/out/streq.txt %/out/size.txt %/out/probe.txt \
	%/out/bad.txt %/out/uni.txt %/out/dumb.txt %/out/clever.txt
	-cat $(@D)/lms.txt > $@
	-cat $(@D)/out/make.txt >> $@
	-cat $(@D)/out/strio.txt >> $@
	-cat $(@D)/out/streq.txt >> $@
	-cat $(@D)/out/size.txt >> $@
	-cat $(@D)/out/probe.txt >> $@
	-cat $(@D)/out/bad.txt >> $@
	-cat $(@D)/out/uni.txt >> $@
	-cat $(@D)/out/dumb.txt >> $@
	-cat $(@D)/out/clever.txt >> $@

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
	-rm -rf test/*.eq test/*.out test/*.bad test/*.uni

.PHONY: clobber
clobber: clean cleantests
	-rm -rf *.log \
	   	$(SUBDIR)/**/out
