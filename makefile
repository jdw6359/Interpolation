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


all_sparameters: nak_sparameters natural_sparameters clamped_sparameters

nak_sparameters:
	./hw7 -nak $(FILE) > sparameters1.txt

natural_sparameters:
	./hw7 -natural $(FILE) > sparameters2.txt

clamped_sparameters:
	./hw7 -clamped $(FILE) > sparameters3.txt



all_eval: all_sparameters nak_eval natural_eval clamped_eval

nak_eval:
	./hw7 -e sparameters1.txt eval.txt

natural_eval:
	./hw7 -e sparameters2.txt eval.txt
	
clamped_eval:
	./hw7 -e sparameters3.txt eval.txt


clean:
	rm -f *.o
	rm -f *.save
	rm -f *.gch
