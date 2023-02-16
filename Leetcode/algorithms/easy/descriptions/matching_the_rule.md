### Count Items Matching a Rule

[My Submissions](https://leetcode.com/contest/weekly-contest-230/problems/count-items-matching-a-rule/submissions/)[Back to Contest](https://leetcode.com/contest/weekly-contest-230/)

* **User Accepted:**5788
* **User Tried:**5912
* **Total Accepted:**5994
* **Total Submissions:**6680
* **Difficulty:**Easy

You are given an array `items`, where each `items[i] = [type<sub>i</sub>, color<sub>i</sub>, name<sub>i</sub>]` describes the type, color, and name of the `i<sup>th</sup>` item. You are also given a rule represented by two strings, `ruleKey` and `ruleValue`.

The `i<sup>th</sup>` item is said to match the rule if **one** of the following is true:

* `ruleKey == "type"` and `ruleValue == type<sub>i</sub>`.
* `ruleKey == "color"` and `ruleValue == color<sub>i</sub>`.
* `ruleKey == "name"` and `ruleValue == name<sub>i</sub>`.

Return *the number of items that match the given rule*.

**Example 1:**

<pre><strong>Input:</strong> items = [["phone","blue","pixel"],["computer","silver","lenovo"],["phone","gold","iphone"]], ruleKey = "color", ruleValue = "silver"
<strong>Output:</strong> 1
<strong>Explanation:</strong> There is only one item matching the given rule, which is ["computer","silver","lenovo"].
</pre>

**Example 2:**

<pre><strong>Input:</strong> items = [["phone","blue","pixel"],["computer","silver","phone"],["phone","gold","iphone"]], ruleKey = "type", ruleValue = "phone"
<strong>Output:</strong> 2
<strong>Explanation:</strong> There are only two items matching the given rule, which are ["phone","blue","pixel"] and ["phone","gold","iphone"]. Note that the item ["computer","silver","phone"] does not match.</pre>

**Constraints:**

* `1 <= items.length <= 10<sup>4</sup>`
* `1 <= type<sub>i</sub>.length, color<sub>i</sub>.length, name<sub>i</sub>.length, ruleValue.length <= 10`
* `ruleKey` is equal to either `"type"`, `"color"`, or `"name"`.
* All strings consist only of lowercase letters.
