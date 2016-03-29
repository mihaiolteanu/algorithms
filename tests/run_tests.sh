#!/bin/sh

# Make sure the object files of the code to be tested are already generated.
cd ..
make

# Build the test binary.
cd tests
make

# Run the tests.
./test_array.exe
