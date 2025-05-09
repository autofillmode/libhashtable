CC = /usr/bin/gcc
OPTS = -Wall -Wpedantic
OBJS = src/murmur.o src/llist.o src/hashtable.o
LIB = -lcjson
BIN = example_json example_types 

default: examples

examples: example_json.o 
	$(CC) $(OPTS) example_json.o libhashtable.a -o example_json $(LIB)

example_json.o: libhashtable.a
	$(CC) $(OPTS) -c examples/example_json.c libhashtable.a $(LIB)

libhashtable.a: $(OBJS)
	ar cr libhashtable.a $(OBJS)

hashtable.o: murmur.o llist.o
	$(CC) $(OPTS) hashtable.c 

llist.o:
	$(CC) $(OPTS) llist.c

murmur.o:
	$(CC) $(OPTS) murmur.c

clean:
	rm $(OBJS) *.o *.a
