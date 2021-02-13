# Solution

[File](task_i.cpp) with C++ solution

# Definition

    Time limit 1 second
    Memory limit 512Mb
    Input standard input or input.txt
    Output standard output or output.txt

Here is a log of effective shots in a basketball game. Your task is to determine the final result of the match.
The rules for scoring points in basketball are as follows:

the team receives 1 point for a free throw thrown by a free throw;
for a ball thrown from a close distance, the team receives 2 points;
for a ball thrown from a long distance, the team gets 3 points.
If the distance to the basket during the throw was no more than 
6 meters, then the distance is considered close, otherwise-far. Of course, these are somewhat simplified rules of the game of basketball.

Input format:
The first line contains an integer 
n — the number of goals thrown (1≤n≤1000). The next n lines contain information about the dropped balls. Each line contains two integers t_i and d_i (1≤t_i≤2, -1≤d_i≤20). If d_i≥0, it means that a player from team t_i threw the ball from a distance of d_i meters to the basket. If d_i=-1, it means that the player from the team t_i threw the ball from a free throw.

The format of the output:
Output the result of the match — the number of points scored by the first and second teams, separated by a colon.
Example 1
Input:
3
1 2
2 5
1 10

Output:
5:2

Example 2
Input:
4
1 2
1 -1
1 20
1 20

Output:
9:0

Example 3
Input:
10
1 -1
1 -1
2 -1
2 -1
1 1
1 5
2 6
2 7
1 11
1 12

Output:
12:7