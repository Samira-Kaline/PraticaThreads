CFLAGS=-O2 -Wall

all: quickSortSimples quickSortThreads quickSortSimples.class gerador

quickSortSimples: quickSortSimples.o timeMeasurement.o
	$(CC) -o $@ quickSortSimples.o timeMeasurement.o
	
quickSortThreads: quickSortThreads.o timeMeasurement.o
	$(CC) -o $@ quickSortThreads.o timeMeasurement.o  -lpthread

gerador: gerador.o
	$(CC) -o $@ gerador.o

gerador.o: gerador.c
	$(CC) $(CFLAGS) -c -o $@ gerador.c
	
timeMeasurement.o: timeMeasurement.c timeMeasurement.h
	$(CC) $(CFLAGS) -c -o $@ timeMeasurement.c

quickSortSimples.o: quickSortSimples.c
	$(CC) $(CFLAGS) -c -o $@ quickSortSimples.c

quickSortThreads.o: quickSortThreads.c
	$(CC) $(CFLAGS) -c -o $@ quickSortThreads.c

quickSortSimples.class: quickSortSimples.java
	javac quickSortSimples.java

clean:
	rm -rf quickSortSimples quickSortThreads quickSortSimples.class gerador *.o OUT.txt
