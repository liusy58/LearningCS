#
# Students' Makefile for the Malloc Lab
#
TEAM = bovik
VERSION = 1
HANDINDIR = /afs/cs.cmu.edu/academic/class/15213-f01/malloclab/handin

CC = gcc
CFLAGS = -Wall -O2 -m32 -fsanitize=address

OBJS = mdriver.o mm.o memlib.o fsecs.o fcyc.o clock.o ftimer.o

mdriver: $(OBJS)
	$(CC) $(CFLAGS) -o mdriver $(OBJS)

mdriver.o: src/mdriver.c include/fsecs.h include/fcyc.h include/clock.h include/memlib.h include/config.h include/mm.h
memlib.o: src/memlib.c include/memlib.h
mm.o: src/mm.c include/mm.h include/memlib.h
fsecs.o: src/fsecs.c include/fsecs.h include/config.h
fcyc.o: src/fcyc.c include/fcyc.h
ftimer.o: src/ftimer.c include/ftimer.h include/config.h
clock.o: src/clock.c include/clock.h

handin:
	cp mm.c $(HANDINDIR)/$(TEAM)-$(VERSION)-mm.c

clean:
	rm -f *~ *.o mdriver


