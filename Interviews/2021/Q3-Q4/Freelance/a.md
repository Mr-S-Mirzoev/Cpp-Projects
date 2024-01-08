# Message Cropping

## Task Description

Your task is to write a function that crops messages which exceed a certain length limit without splitting words. The function should adhere to the following rules:

- It must not crop away part of a word.
- The output message must not end with a space.
- The output message may not exceed the specified character limit.
- The output message should be as long as possible.
- If necessary, the algorithm may return an empty string.

## Function Signature

```cpp
std::string solution(std::string& message, int K);
```

## Parameters

- `message`: a non-empty string containing at most 500 English alphabet letters and spaces.
- `K`: an integer within the range [1..500] representing the maximum allowed message length.

## Returns

- A string representing the message cropped to no more than `K` characters.

## Constraints

- There are no spaces at the beginning or at the end of the message.
- There are no consecutive spaces in the message.

## Examples

1. Given `message = "To be or not to be"` and `K = 14`, the function should return `"To be or not"`, as it is the longest substring that does not end with a space and does not crop part of a word.

2. Given `message = "Why not"` and `K = 100`, the function should return `"Why not"`, since the original message is shorter than the limit.

3. Given `message = "The quick brown fox jumps over the lazy dog"` and `K = 39`, the function should return `"The quick brown fox jumps over the lazy"`, ensuring words are not broken.

4. Given `message = "To crop or not to crop"` and `K = 21`, the function should return `"To crop or not to"`, cropping the message properly within the limit.

## Note

- Focus on correctness in your solution.
- The performance of your solution will not be the focus of the assessment.
