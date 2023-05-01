# This Works is placed under the terms of the Copyright Less License,
# see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.

COUNT=1000

.PHONY:	love
love:	all

.PHONY:	all
all:	pp_incdec.h tests
	./tests
	$(MAKE) example
	./example mul neg sub neg 8 neg 2 neg add neg 3 neg 4

# Do we really have to re-invent the wheel due to MacOS-X?
# Apparently: Yes
tests:	tests.c *.h
	$(CC) '$<' -o '$@'

pp_incdec.h:	pp_incdec.awk Makefile
	awk -vMAX='$(COUNT)' -vGEN='$<' -f '$<' >'$@'

.PHONY:	clean
clean:
	rm -f tests example pp_incdec.h

