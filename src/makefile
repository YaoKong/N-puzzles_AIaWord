IDIR=..\.\inc
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=..\.\obj
LDIR=..\.\lib

LIBS=-lm

_DEPS = cell.h node.h problem.h state.h twobuff.h uLong.h direction.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = cell.o problem.o puzzle-main.o state.o twobuff.o uLong.o direction.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

n_puzzle: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del $(ODIR)\*.o *.exe