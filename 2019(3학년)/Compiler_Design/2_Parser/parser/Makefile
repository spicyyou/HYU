#
# Makefile for TINY
# Gnu C Version
# K. Louden 2/3/98
#

CC = gcc

CFLAGS = 

OBJS = main.o util.o lex.yy.o y.tab.o symtab.o analyze.o code.o cgen.o


all: cminus

cminus: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lfl

main.o: main.c globals.h y.tab.h util.h scan.h parse.h analyze.h cgen.h
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h y.tab.h
	$(CC) $(CFLAGS) -c util.c

lex.yy.c: cminus.l
	flex cminus.l

lex.yy.o: lex.yy.c globals.h y.tab.h util.h scan.h
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.c: cminus.y
	yacc -d -v cminus.y

y.tab.h: y.tab.c

y.tab.o: y.tab.c globals.h y.tab.h util.h scan.h parse.h
	$(CC) $(CFLAGS) -c y.tab.c



#scan.o: scan.c scan.h util.h globals.h
#	$(CC) $(CFLAGS) -c scan.c

#parse.o: parse.c parse.h scan.h globals.h util.h
#	$(CC) $(CFLAGS) -c parse.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

analyze.o: analyze.c globals.h symtab.h analyze.h
	$(CC) $(CFLAGS) -c analyze.c

code.o: code.c code.h globals.h
	$(CC) $(CFLAGS) -c code.c

cgen.o: cgen.c globals.h symtab.h code.h cgen.h
	$(CC) $(CFLAGS) -c cgen.c

clean:
	rm -vf $(OBJS) lex.yy.c y.tab.h y.tab.c cminus
