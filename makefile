CC=gcc

CFLAGS= -Wall -ansi -pedantic

FILE= data.txt


make: hw7


hw7: hw7.o interp.o
	$(CC) $(CFLAGS) -o hw7 hw7.o interp.o


hw7.o: hw7.c
	$(CC) $(CFLAGS) -c hw7.c 

interp.o: interp.c
	$(CC) $(CFLAGS) -c interp.c




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
