# A simple hashtable

ATTENTION: Stable and mostly tested, but (please) DON'T USE IN PRODUCTION!!

This is a simple hashtable. Uses the murmur32 reference implementation for hashing, and a self-rolled linked list for chaining.
Keys are of type `char*` and Values are `void*`. The user can either only use stack-alloc'd values, and pass a no-op callback to ht_free(), or allocate everything, in which case he must pass a callback to free whatever he has alloc'd.

In short, the user allocates and frees all Keys and Values, and the table cleans up the Nodes and Pairs.

Included are two small examples, feel free to take a look at those. Note that the example using JSON needs cJSON installed.

Compile the examples with the provided Makefile by running
`make`.

Then run the executable with one of the provided json files as an argument:

`./example_json json/10-village-coders.json`

