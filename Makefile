
PROGRAM = virus_hunter
CC      = gcc
ZAST    = -g -std=c99 -Wall -L/usr/X11R6/lib -L/usr/pkg/lib
PROG    = virushunter/main.c virushunter/utility.c virushunter/callback.c virushunter/keyboard.c virushunter/variables.c virushunter/model.c
ZAV     = virushunter/utility.h virushunter/callback.h virushunter/keyboard.h virushunter/variables.h virushunter/model.h
BIBL    = -lglut -lGLU -lGL -lm

$(PROGRAM): $(PROG) $(ZAV)
	$(CC) $(ZAST) -o $(PROGRAM) $(PROG) $(BIBL)

.PHONY: run makerun clean

run:
	./$(PROGRAM) &

makerun:
	make
	make run

clean:
	rm -f *~ virushunter/*~ 