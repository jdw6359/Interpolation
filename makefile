




















CC=gcc

CFLAGS= -Wall -ansi -pedantic

FILE= data.txt


make: hw7


hw7: hw7.o interp.o Dynamic.o linalg.o
	$(CC) $(CFLAGS) -o hw7 hw7.o interp.o Dynamic.o linalg.o


hw7.o: hw7.c
	$(CC) $(CFLAGS) -c hw7.c 

interp.o: interp.c
	$(CC) $(CFLAGS) -c interp.c


Dynamic.o: Dynamic.c
	$(CC) $(CFLAGS) -c Dynamic.c

linalg.o: linalg.c
	$(CC) $(CFLAGS) -c linalg.c


natural: hw7
	./hw7 -natural $(FILE)

clamped: hw7
	./hw7 -clamped $(FILE)

nak: hw7
	./hw7 -nak $(FILE)








clean:
	rm -f *.o
	rm -f *.save
	rm -f *.gch
