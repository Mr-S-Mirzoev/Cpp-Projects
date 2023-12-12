# Solution

[File](../task_g.cpp) with C++ solution

# Definition

    Time limit 1 second
    The memory limit of 64Mb
    Input standard input or input.txt
    Output standard output or output.txt

In this task, you need to write the code for solving the problem about couriers (a detailed condition in the neighboring problem).
Note: The solution must read the input data from STDIN or from a file input.txt (the file is located in the working directory when the solution is launched).

**Input format**
The first line contains an integer m (1≤m≤1000). Each of the following m lines contains two time points start_i and finish_i in the format HH:MM:SS (00≤HH<24, 00≤MM<60, 00≤SS<60).
Note: The input data contains line feeds in UNIX format (Unix LF). https://en.wikipedia.org/wiki/Newline

**The format of the output**
Output a single integer, the minimum number of couriers.

*Example 1*

Input:
4
08:00:00 11:00:00
09:00:00 10:00:00
10:00:00 11:10:00
10:59:59 13:00:00

Output:
3

*Example 2*
Input:
1
08:00:00 09:00:00

Output:
1

*Example 3*
Input:
4
08:00:00 13:00:00
09:00:00 13:00:00
10:00:00 13:00:00
10:59:59 13:00:00

Output:
4

*Example 4*
Input:
10
08:00:00 11:00:00
08:00:00 11:00:00
08:00:00 11:00:00
08:00:00 11:00:00
08:00:00 11:00:00
12:00:00 12:00:01
12:00:00 23:59:59
12:00:00 13:00:01
13:00:00 13:00:01
13:00:00 13:00:01

Output:
5
