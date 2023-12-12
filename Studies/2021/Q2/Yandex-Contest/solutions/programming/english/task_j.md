# Solution

[File](../task_j.cpp) with C++ solution

# Definition

    Time limit 1 second
    Memory limit 512Mb
    Input standard input or input.txt
    Output standard output or output.txt

Petya came up with a strange data transfer protocol. Its essence is that by transmitting the correct message
S, millions of bytes of extra information are added to the data stream. It is assumed that the attacker will break his head until he finds the right part of the message. Innovative? Of course!
To transmit a secret message, a key is used — a string of digits ABC, where A, B, and C are some positive integers that satisfy the ratio A + B = C.

Vasya highlighted a part of the transmitted message. Confirm that it can be divided into three parts to get the correct mathematical equality with addition.
More formally, a message of the form ABC is given, which can be represented as a mathematical identity of the form A+B=C, where A, B, C are some positive integers. Find this identity.

Input format:
A single line contains a message of the form ABC, consisting of digits from 0 to 9. The line length is not less than three characters and does not exceed one hundred characters.

The format of the output:
Output a message like A+B=C. Thus, the response must differ from the input string by exactly two inserted characters — one + character and one =character. Leading zeros in the decimal notation of the numbers A, B, and C
are not allowed.
If there are several solutions, output any of them. It is guaranteed that at least one solution exists.

Example 1
Input:
123123246

Output:
123+123=246

Example 2
Input:
999108

Output:
9+99=108

Example 3
Input:
11111122

Output:
11+111=122
