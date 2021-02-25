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
