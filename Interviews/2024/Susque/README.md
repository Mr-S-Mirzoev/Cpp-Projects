# Bank Requests Processing Program

## Task Description

You've been asked to program a bot for a popular bank that will automate the management of incoming requests. There are three types of requests the bank can receive:

- `transfer i j sum`: request to transfer `sum` amount of money from the `i`-th account to the `j`-th one (`i` and `j` are 1-based).
- `deposit i sum`: request to deposit `sum` amount of money in the `i`-th account (1-based).
- `withdraw i sum`: request to withdraw `sum` amount of money from the `i`-th account (1-based).

Your bot should also be able to process invalid requests. There are two types of invalid requests:

- Invalid account number in the requests.
- Withdrawal/transfer of a larger amount of money than is currently available.

For the given list of `balances` and `requests`, return the state of `balances` after all requests have been processed, or an array of a single element `[-request_id]`, where `request_id` is the 1-based index of the first invalid request.

## Examples

- For `balances = [10, 100, 20, 50, 30]` and `requests = ["withdraw 2 10", "transfer 5 1 20", "deposit 5 20", "transfer 3 4 15"]`, the output should be `solution(balances, requests) = [30, 90, 5, 65, 30]`.

Here are the states of `balances` after each request:
- `"withdraw 2 10"`: `[10, 90, 20, 50, 30]`
- `"transfer 5 1 20"`: `[30, 90, 20, 50, 10]`
- `"deposit 5 20"`: `[30, 90, 20, 50, 30]`
- `"transfer 3 4 15"`: `[30, 90, 5, 65, 30]`, which is the answer.

- For `balances = [20, 1000, 500, 40, 90]` and `requests = ["deposit 3 400", "transfer 1 2 30", "withdraw 4 50"]`, the output should be `solution(balances, requests) = [-2]`.

After the first request, `balances` becomes equal to `[20, 1000, 900, 40, 90]`, but the second one turns it into `[-10, 1030, 900, 40, 90]`, which is invalid. Thus, the second request is invalid, and the answer is `[-2]`. Note that the last request is also invalid, but it shouldn't be included in the answer.

## Input/Output

- Execution time limit: 0.5 seconds (cpp)
- Memory limit: 1 GB

### Input

#### `array.integer balances`

Array of integers, where `balances[i]` is the amount of money in the `(i + 1)`-th account.

##### Guaranteed constraints:

- `0 < balances.length ≤ 100`
- `0 ≤ balances[i] ≤ 10^5`

#### `array.string requests`

Array of requests in the order they should be processed. Each request is guaranteed to be in the format described above.

It is guaranteed that for each `i` and `j` in a request `0 < i, j ≤ 1000`, `0 ≤ sum ≤ 10^5`.

##### Guaranteed constraints:

- `0 < requests.length ≤ 100`
- For each `i`, `j` and `sum` in each element of `request`:
  - `0 < i ≤ 1000`
  - `0 < j ≤ 1000`
  - `0 ≤ sum ≤ 10^5`

### Output

#### `array.integer`

The `balances` after executing all of the `requests` or array with a single integer - the index of the first invalid request preceded by `-`.
