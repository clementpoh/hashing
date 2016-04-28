# Makefile
#
# Clement Poh
#
# Makefile to test COMP20007 2016 Assignment 2 submissions
#
spec.pdf: spec.tex
	pdflatex spec.tex && rm spec.log spec.aux

.PHONY: clean
clean:
	rm -f spec.pdf
