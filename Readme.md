# Collection Factory Interface

Implement a collection factory with following **APIs**

`add(T )` : Adds element into the collection

`T get()` : Removes and returns next element from the collection

`bool isEmpty()` : Returns `true` if collection is empty

`uint size()` : Returns size of collection

Collection Factory supports creation of FIFO or LIFO collection

## Build

```
$mkdir build
$cd build
$cmake ..
$make
```
This will generate binaries in tests directory


## Dependencies

This project dpends on cmake which needs to be installed as per your system requirement

On Ubuntu `sudo apt-get install cmake`

googletest is used for unit testing and is added by CMake using ExternalProject directive.

This project relies on Address Sanitizer and Thread Sanitizer supported by llvm or gcc > 4.8
These are used for non-functional testing apart from performance and thread-safety tests

Also to extract coverage information, needs `lcov`.

On Ubuntu `sudo apt-get install lcov`

Running the tests creates gcno and gcda files. cd into that directory and run

```
$lcov -c --directory . --output-file main_coverage.info
$genhtml main_coverage.info --output-directory coverage_report
```

