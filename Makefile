# This Works is placed under the terms of the Copyright Less License,
# see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.

COUNT=1000

.PHONY:	love
love:	all

.PHONY:	all
all:	pp_incdec.h tests
	./tests

tests:	tests.c *.h

pp_incdec.h:	pp_incdec.awk Makefile
	awk -vMAX='$(COUNT)' -vGEN='$<' -f '$<' >'$@'

.PHONY:	clean
clean:
	rm -f tests

