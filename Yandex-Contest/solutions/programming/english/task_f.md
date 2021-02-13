# Solution

[File](../task_f.cpp) with C++ solution

# Definition

In this task, you need to find the number of the line containing the error.
Below is the pseudocode for solving the following problem.
*m* delivery orders are given. Each order is described by two time points: *start*, *finish* (in the HH:MM:SS format). Once the courier starts executing an order, the courier cannot execute any other order in the interval between *start* and *finish*.

Determine the minimum number of couriers that will be required to complete all* m * orders.

Consider an example:

If m=4 and
start 1=08: 00:00, finish 1=11:00:00,
start 2=09:00:00, finish 2=10:00:00,
start 3=10:00:00, finish 3=11:10:00,
start 4=10:59:59, finish 4=13:00:00.

One courier can complete 2 orders (2nd and 3rd or 2nd and 4th), two couriers can deliver 3 orders, and three couriers can deliver all 4 orders.
Please note that the courier can take a new order immediately after the completion of the previous one.

 
    # read input:  
    # read number of orders to deliver from first row of the input into m  
    # read start and finish timestamps from each next row in input  
    # and store them in an m*2 array called orders  
    # orders[i][0] - start of order i, orders[i][1] - finish of order i  
    # it is known that for each order i that: orders[i][0] < orders[i][1]  
    
    1.  available_at - [0..m-1] array of timestamps, initialized with 00:00:00  
    2.  sort orders in increasing order of start timestamps  
    3.  
    4.  used_couriers = 0  // count of couriers delivering at least one order  
    5.  
    6.  for order_id from 0 to m - 1:  
    7.    available_courier = -1  
    8.  
    9.    for courier_id from 0 to m - 1:  
    10.      if available_at[courier_id] <= orders[order_id][0]:  
    11.        available_courier = courier_id  // save available courier found  
    12.       break  
    13.  
    14.   if available_at[available_courier] == ’00:00:00’:  
    15.     used_couriers += 1 // assign order to a new courier  
    16.  
    17.   available_at[available_courier] = orders[order_id][0] // update time of availability  
    18.  
    19. return used_couriers

Note: `Error` can correspond to any situation where the program (algorithm) gives an incorrect answer, the pseudocode can be corrected by changing, deleting or adding several characters in one line.
Hint: The error is not syntactic, but in the correctness of the algorithm.

# Answer

17