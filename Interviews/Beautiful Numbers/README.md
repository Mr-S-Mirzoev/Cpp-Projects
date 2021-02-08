# Beautiful numbers

See task description in [task.md](task.md)

## How to build

    cmake -B build
    make -C build -j 8

## How to get the result

    ./build/beautiful_numbers 

This should give you an output:

    Quantity of "beautiful" 13-digit numbers in 13-digit system of calculations:
    In scientific notation: 1.031993e+15
    In usual notation: 1031993073373201.000000

## How to test the supporting library

The supporting library has a few functions which should essentially work correctly.

Those are:

    int factorial(int k);
    int permutations_on_set(const std::string &numbers);
    int64_t quantity_of_numbers_with_sum(short sum);

To see the result of GTest:

    ./build/tests/beautiful_numbers_tst 