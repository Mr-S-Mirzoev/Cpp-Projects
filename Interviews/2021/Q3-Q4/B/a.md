# Frequency Sorting

## Task Description

Write a program that reads a sequence of integers and sorts them according to the frequency of their occurrence in descending order. If two numbers have the same frequency, they should be printed in the order they appeared in the input.

## Input

- The first line of input contains an integer `N`, the number of integers to follow.
- The next `N` lines each contain an integer value that needs to be sorted based on frequency.

## Output

- Output a single line containing all `N` integers sorted by descending frequency.
- If multiple integers have the same frequency, they should be ordered by their appearance in the input.

## Example

### Input

```
8
5
2
2
3
5
4
5
3
```

### Output

```
5 5 5 2 2 3 3 4
```

In this example, the number `5` appears three times, `2` and `3` each appear twice, and `4` appears once, so `5` is printed first, `2` and `3` are printed next in the order they were first encountered, and `4` is printed last.
