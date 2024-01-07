# Scalar multiplication of compact vectors

## Description

The compact vector is a structure, where values can occur multiple times:

    [{2, 3}, {1, 2}] == [2, 2, 2, 1, 1]

Given 2 compact vectors print their scalar product:

    [{2, 3}, {1, 2}, {-1, 3}] * [{0, 4}, {5, 4}]
    = [2, 2, 2, 1, 1, -1, -1, -1] * [0, 0, 0, 0, 5, 5, 5, 5]
    = -10