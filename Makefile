CC = /usr/bin/gcc
OPTS = -c -Wall -Wpedantic
OBJS = murmur.o llist.o compare.o hashtable.o

default: libhashtable.a
	
libhashtable.a: $(OBJS)
	ar cr libhashtable.a $(OBJS)

hashtable.o: murmur.o compare.o llist.o
	$(CC) $(OPTS) hashtable.c 

llist.o: compare.o
	$(CC) $(OPTS) llist.c compare.o

compare.o:
	$(CC) $(OPTS) compare.c

murmur.o:
	$(CC) $(OPTS) murmur.c

clean:
	rm $(OBJS)