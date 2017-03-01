- remove inout parameters where possible
    - see 12.7 advice in C++ Language -> return a result as a return value rather than modifying an argument


- prefer deques for queues and stacks -> additional methods and range based for loop
    - push_back pop_front for queue
    - push_front pop_front for stack
    - for loop forward iteration should follow FIFO for queue and LIFO for stack