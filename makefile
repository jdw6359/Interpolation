CC=gcc

CFLAGS= -Wall -ansi -pedantic

FILE= data.txt


make: hw7


hw7: hw7.o interp.o Dynamic.o
	$(CC) $(CFLAGS) -o hw7 hw7.o interp.o Dynamic.o


hw7.o: hw7.c
	$(CC) $(CFLAGS) -c hw7.c 

interp.o: interp.c linalg.c
	$(CC) $(CFLAGS) -c interp.c linalg.c

Dynamic.o: Dynamic.c
	$(CC) $(CFLAGS) -c Dynamic.c



natural:
	./hw7 -natural $(FILE)

clamped:
	./hw7 -clamped $(FILE)

nak:
	./hw7 -nak $(FILE)








clean:
	rm -f *.o
	rm -f *.save
	rm -f *.gch
