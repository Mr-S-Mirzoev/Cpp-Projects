Given a balanced parentheses string `S`, compute the score of the string based on the following rule:

* `()` has score 1
* `AB` has score `A + B`, where A and B are balanced parentheses strings.
* `(A)` has score `2 * A`, where A is a balanced parentheses string.

**Example 1:**

<pre><strong>Input: </strong><span id="example-input-1-1">"()"</span>
<strong>Output: </strong><span id="example-output-1">1</span>
</pre>

**Example 2:**

<pre><strong>Input: </strong><span id="example-input-2-1">"(())"</span>
<strong>Output: </strong><span id="example-output-2">2</span>
</pre>

**Example 3:**

<pre><strong>Input: </strong><span id="example-input-3-1">"()()"</span>
<strong>Output: </strong><span id="example-output-3">2</span>
</pre>

**Example 4:**

<pre><strong>Input: </strong><span id="example-input-4-1">"(()(()))"</span>
<strong>Output: </strong><span id="example-output-4">6</span>
</pre>

**Note:**

1. `S` is a balanced parentheses string, containing only `(` and `)`.
2. `2 <= S.length <= 50`

## Other aproaches to solve this problem

#### Approach 1: Divide and Conquer

**Intuition**

Split the string into `S = A + B` where `A` and `B` are balanced parentheses strings, and `A` is the smallest possible non-empty prefix of `S`.

**Algorithm**

Call a balanced string *primitive* if it cannot be partitioned into two non-empty balanced strings.

By keeping track of `balance` (the number of `(` parentheses minus the number of `)` parentheses), we can partition `S` into primitive substrings `S = P_1 + P_2 + ... + P_n`. Then, `score(S) = score(P_1) + score(P_2) + ... + score(P_n)`, by definition.

For each primitive substring `(S[i], S[i+1], ..., S[k])`, if the string is length 2, then the score of this string is 1. Otherwise, it's twice the score of the substring `(S[i+1], S[i+2], ..., S[k-1])`.

```
class Solution(object):
    def scoreOfParentheses(self, S):
        def F(i, j):
            #Score of balanced string S[i:j]
            ans = bal = 0

            #Split string into primitives
            for k in xrange(i, j):
                bal += 1 if S[k] == '(' else -1
                if bal == 0:
                    if k - i == 1:
                        ans += 1
                    else:
                        ans += 2 * F(i+1, k)
                    i = k+1

            return ans

        return F(0, len(S))
```

**Complexity Analysis**

* Time Complexity: O(N^2)O(N2), where NN is the length of `S`. An example worst case is `(((((((....)))))))`.
* Space Complexity: O(N)O(N), the size of the implied call stack.

---

#### Approach 2: Stack

**Intuition and Algorithm**

Every position in the string has a *depth* - some number of matching parentheses surrounding it. For example, the dot in `(()(.()))` has depth 2, because of these parentheses: `(__(.__))`

Our goal is to maintain the score at the current depth we are on. When we see an opening bracket, we increase our depth, and our score at the new depth is 0. When we see a closing bracket, we add twice the score of the previous deeper part - except when counting `()`, which has a score of 1.

For example, when counting `(()(()))`, our stack will look like this:

* `[0, 0]` after parsing `(`
* `[0, 0, 0]` after `(`
* `[0, 1]` after `)`
* `[0, 1, 0]` after `(`
* `[0, 1, 0, 0]` after `(`
* `[0, 1, 1]` after `)`
* `[0, 3]` after `)`
* `[6]` after `)`

```
class Solution(object):
    def scoreOfParentheses(self, S):
        stack = [0] #The score of the current frame

        for x in S:
            if x == '(':
                stack.append(0)
            else:
                v = stack.pop()
                stack[-1] += max(2 * v, 1)

        return stack.pop()class Solution(object):
    def scoreOfParentheses(self, S):
        stack = [0] #The score of the current frame

        for x in S:
            if x == '(':
                stack.append(0)
            else:
                v = stack.pop()
                stack[-1] += max(2 * v, 1)

        return stack.pop()
```

##### Explanation

this may help you understand [Approach 2: Stack]

* .(()(())) depth=0 stack=[0]
* (.()(())) depth=1 stack=[0,0]
* ((.)(())) depth=2 stack=[0,0,0]
* (().(())) depth=1 stack=[0,1]
* (()(.())) depth=2 stack=[0,1,0]
* (()((.))) depth=3 stack=[0,1,0,1]
* (()(().)) depth=2 stack=[0,1,1]
* (()(()).) depth=1 stack=[0,3]
* (()(()).) depth=0 stack=[6]

`stack[i]`(stack has no [i] api,just for explaination): current score of the ith depth
operations in the iteration:

* see a `(`：`stack.push(0)`increase our depth
* see a `)`：we need to decrease our depth
  * `int v = stack.pop();` score of the ith depth
  * `int w = stack.pop();` score of the（i-1)th depth
  * `stack.push(w + Math.max(2 * v, 1));` collect a new score for the（i-1)th depth

a final score is collected for the 0th depth, so `return stack.pop();`


#### Approach 3: Count Cores

**Intuition**

The final sum will be a sum of powers of 2, as every *core* (a substring `()`, with score 1) will have it's score multiplied by 2 for each exterior set of parentheses that contains that core.

**Algorithm**

Keep track of the `balance` of the string, as defined in *Approach #1*. For every `)` that immediately follows a `(`, the answer is `1 << balance`, as `balance` is the number of exterior set of parentheses that contains this core.

##### Explanation


Let me explain the third solution as best as I can since it's really elegant.

The key idea is that:

1. the balance tells you what "depth" you are at since with each '(' we are increasing the depth by 1 (kind of similar to the concept in Solution 2).
2. the "cores" () are the only structure that provides value, the outer parentheses just add some multiplier to the cores. So we only need to be concerned with those.

With those 2 ideas in mind, we are able to calculate how much the "core" is worth directly without having to calculate substructures recursively and then apply multipliers.

E.g. For the example of `( ( ) ( ( ) ) )`, with the stack method, we are calculating the inner structure `( ) ( ( ) )` first and then multiplying the score by 2. With the 3rd method, by knowing the depth of the core, we are actually performing this calculation `( ( ) ) + ( ( ( ) ) )`.

```
class Solution(object):
    def scoreOfParentheses(self, S):
        ans = bal = 0
        for i, x in enumerate(S):
            if x == '(':
                bal += 1
            else:
                bal -= 1
                if S[i-1] == '(':
                    ans += 1 << bal
        return ans
```

**Complexity Analysis**

* Time Complexity: O(N)O(N), where NN is the length of `S`.
* Space Complexity: O(1)O(1).
