- GNU strcat warning to not use strcat -> prefer a string concatenation function that has size parameters and bounds checking
- decrementing an unsigned value and comparing >= 0 will wrap and never end
- do not use emplace_back with a pre-allocated vector -> assign using index
- it is possible to pass the size argument for a C-style array and use that argument in the array argument's size
- always remember to use typename for dependent types in templates
- if a class is a container give it an initializer_list ctor
- initialize members and bases in order of their declarations
- a virtual function cannot be a template member function


- remove inout parameters where possible
    - see 12.7 advice in C++ Language -> return a result as a return value rather than modifying an argument


- prefer deques for queues and stacks -> additional methods and range based for loop
    - push_back pop_front for queue
    - push_front pop_front for stack
    - for loop forward iteration should follow FIFO for queue and LIFO for stack

