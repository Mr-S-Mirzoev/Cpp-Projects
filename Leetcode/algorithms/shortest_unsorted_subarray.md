# Shortest Unsorted Continuous Subarray

Given an integer array `nums`, you need to find one **continuous subarray** that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order.

Return *the shortest such subarray and output its length*.

**Example 1:**

<pre><strong>Input:</strong> nums = [2,6,4,8,10,9,15]
<strong>Output:</strong> 5
<strong>Explanation:</strong> You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
</pre>

**Example 2:**

<pre><strong>Input:</strong> nums = [1,2,3,4]
<strong>Output:</strong> 0
</pre>

**Example 3:**

<pre><strong>Input:</strong> nums = [1]
<strong>Output:</strong> 0
</pre>

**Constraints:**

* `1 <= nums.length <= 10<sup>4</sup>`
* `-10<sup>5</sup><span> </span><= nums[i] <= 10<sup>5</sup>`

**Follow up:** Can you solve it in `O(n)` time complexity?
