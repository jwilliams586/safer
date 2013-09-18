CC=gcc

safer: safer.o boxes.o
	$(CC) -o safer safer.o boxes.o

clean:
	rm safer *.o

.SUFFIXES: .o .c

.c.o :
	$(CC) -c $<

