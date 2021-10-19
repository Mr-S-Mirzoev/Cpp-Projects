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

## Description of algorithm

The sum of *first* 6 digits and the *last* 6 digits is the *same* in a **beautiful**.

The middle element is *arbitrary*, thus having the sum of first 6 digits fixed, the number of
beautiful numbers with the sum of first 6 digits being equal to S is:

    beaut_by_sum(S) = quantity_of_6_digits_with_sum(S) * 13 * quantity_of_6_digits_with_sum(S)

So the idea behind the calculation is a *loop by all elightable sums* which are numbers in range [0 .. 13 * 6)

    overall_beautiful = 0
    for sum in [0 .. 13 * 6]:
        overall_beautiful += beaut_by_sum(sum)

To count beaut_by_sum we'll look on all the sets of 6 digit numbers in the 13-digit system.

To find them we'll look on all ascending vectors with designated sum.

We'll go recursively, having in each recursion such loop:

    for i in [previous_lowest, sum_left/length_left]:
        overall += quantity_of_numbers_with_sum(sum - i, length - 1, concat(s, 'i'));

And when we reach length of 1 we'll have the only digit which could satisfy us. Since we have all the vector now, we'll count the permutations on it:

    if length_left == 1:
        return permutations_on_set(s + 'last');

Why were we iterating from prev_lowest? Because the vector is ascending.

Why were we iterating till sum_left/length_left? This way we guaranty that there would be no dead lists in recursion