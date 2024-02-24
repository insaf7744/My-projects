CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
OBJDIR := ../OBJDIR
QUESTS := print_module documentation_module bst_create_test bst_insert_test bst_traverse_test
FORMAT_SOURCES := $(wildcard *.c) $(wildcard *.h)   
CLANG_FORMAT := clang-format

all: graph

graph: mystack.o parsing_in_polish_notation.o calculation.o draw.o graph.o
	$(CC) $(CFLAGS) Stack.o Graph.o PARSINGRPN.o Draw.o Calculations.o -o $(OBJDIR)graph

calculation.o: Calculations.c Calculations.h
	$(CC) $(CFLAGS)	Calculations.c -c

draw.o:
	$(CC) $(CFLAGS)	Draw.c -c

graph.o: Graph.c
	$(CC) $(CFLAGS) Graph.c -c

polish_notation.o: RPN.c
	$(CC) $(CFLAGS) RPN.c -c

parsing_in_polish_notation.o: PARSINGRPN.c
	$(CC) $(CFLAGS) PARSINGRPN.c -c

mystack.o: Stack.c Stack.h
	$(CC) $(CFLAGS) Stack.c -c

format:
	$(CLANG_FORMAT) -i $(FORMAT_SOURCES)
	$(CLANG_FORMAT) -n $(FORMAT_SOURCES)

clean:
	rm -rf *.o $(OBJDIR)graph

reOBJDIR: clean all
