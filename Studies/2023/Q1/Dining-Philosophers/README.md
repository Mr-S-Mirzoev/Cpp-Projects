# Dining Philosophers

## Problem Statement

The Dining Philosophers problem is a classic multi-threaded synchronization problem. The problem consists of five philosophers sitting at a table who do nothing but think and eat. Between each philosopher, there is a single fork (so there are five forks total). A philosopher may only eat if he has both left and right forks in his possession. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it's not being used by another philosopher. After he finishes eating, he needs to put down both forks so they become available to others. A philosopher can take the fork on his right or the one on his left as they become available, but can't start eating before getting both of them.

## Solution

### Assessing Validity

- No Starvation (Resource Contention): Unit tests should verify that each philosopher gets to eat regularly. This can be done by monitoring the number of times each philosopher eats over a period.
- Exclusive Fork Access: Unit tests should also ensure that no fork is taken by two or more philosophers simultaneously.
- No Deadlock: Unit tests should verify that no philosopher is prevented from eating indefinitely because of the actions of others.
