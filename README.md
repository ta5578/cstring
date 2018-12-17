# cstring

An ultra small and portable C99 string utility library.

## Library Features
* Extremely lightweight (single header and single source) library.
* Very fast -- performance tests don't lie :)
* Consistent, documented, and easy to learn API.

## Building
cstring is an ultra small library so no building is necessary to use it! Using the library is as simple as 123:

1) Clone the repository somewhere on your machine.
2) Move the header file into one of your project's include directories.
3) Move the source file into one of your project's source directories.

Easy!

In the future, the build instructions may be updated so the library can be installed system-wide.

## Examples
Splitting a string with a token:
```
char **tokens = NULL;
size_t count = 0;
if (!cstr_split("this is a sentence", " ", &tokens, &count)) {
    // handle the error
}

for (size_t i = 0; i < count; ++i) {
    puts(tokens[i]);
    free(tokens[i]); // clean up
}
free(tokens);
```

## Building Unit and Performance Tests
The library comes packaged with unit and performance tests to ensure reliability. Note that building and running these is not required to use the library. It is only necessary if you are either:

1) Actively working on the library's development
2) Curious :)

To build the unit and performance tests, simply do the following (assuming you're in the repo's directory)

```
mkdir build
cd build
cmake ..
```
This is a standard out-of-source CMake build that will build the unit tests into an executable called `cstring_tests` and the performance test into an executable called `cstring_perf`.

## Tools
* [CMake](https://cmake.org/)
* [CuTest](http://cutest.sourceforge.net/)
