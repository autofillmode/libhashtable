# a simple hashtable

ATTENTION: Incomplete, DON'T USE IN PRODUCTION!!

This is a simple hashtable. Uses the murmur32 reference implementation for hashing, and a self-rolled linked list for chaining.
Can use integers or strings as keys. Values can be floats, ints, or strings. 

To use, first compile it into a static library by running 
`make`
Then use the produced static library while linking:
`gcc foo.o libhashtable.a -o bar.out`

Included are two small examples, feel free to take a look at those. Note that the example using JSON needs cJSON installed.
