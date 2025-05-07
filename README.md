# A simple hashtable

ATTENTION: Stable and mostly tested, but (please) DON'T USE IN PRODUCTION!!

This is a simple hashtable. Uses the murmur32 reference implementation for hashing, and a self-rolled linked list for chaining.
Keys and Values are void pointers. 

Included are two small examples, feel free to take a look at those. Note that the example using JSON needs cJSON installed.

Compile the examples with the provided Makefile by running
`make`.

Then run the executable with one of the provided json files as an argument:

`./example_json json/10-village-coders.json`

