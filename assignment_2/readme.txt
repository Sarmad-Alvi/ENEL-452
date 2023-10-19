Made changes to the following files:
    queue.cpp:
        Added overloaded insert function for linked list. Function takes
        a data value and a position value, and inserts the data at the 
        specified position in the linked list. Function handles adding
        values at the head of the list or the tail of the list. Function
        also exits program with error code 3 if position specified is out
        of range of the linked list.
    
    testq.cpp:
        Added test function named testInsert. Function takes a queue,
        empties it for testing and addes various values to it with the
        normal insert function and the new overloaded insert function.
        The test function then removes each value from the queue in
        order from the head and checks to make sure the order is what
        it should be according to the positions the values were inserted
        at.