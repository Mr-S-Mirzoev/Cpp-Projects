# Print FooBar Alternately

Suppose you are given the following code:

```
class FooBar {
public:
  void foo() {
    for (int i = 0; i < n; i++) {
      std::cout << "foo";
    }
  }

  void bar() {
    for (int i = 0; i < n; i++) {
      std::cout << "bar";
    }
  }
}
```

The same instance of `FooBar` will be passed to two different threads. Thread A will call `foo()` while thread B will call `bar()`. Modify the given program to output "foobar" *n* times.

**Example 1:**

<pre><b>Input:</b> n = 1
<b>Output:</b> "foobar"
<strong>Explanation:</strong> There are two threads being fired asynchronously. One of them calls foo(), while the other calls bar(). "foobar" is being output 1 time.
</pre>

**Example 2:**

<pre><b>Input:</b> n = 2
<b>Output:</b> "foobarfoobar"
<strong>Explanation:</strong> "foobar" is being output 2 times.</pre>
