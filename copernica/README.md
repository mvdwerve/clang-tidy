# ideas

- don't throw from publicly accessible methods (or methods in general)
- no getAbc() and setAbc() as method names
- private members should start with _
- every line should have comment
- comment out of sync between C++ and h
- @params out of sync with actual function 
- don't inherit from std
- lambdas dont start on newline
- missing / incorrect type in member variable comment
- large object passed by value (optional)
- self destructing classes private destructor
- exception can escape through function
- don't inherit from std
- missing / incorrect @return type
- const-hint for getters
- method documentation missing
- no nested ternaries
- maximum nesting depth
- eager return instead of if(ab){...} (if possible)
- extra line of white on lambda
- space between if and statement
- long method in header
- long functions overall
- copy/move needs to be defined (default/removed)
- rand() not thread-safe
- can be const hint
- new () not stored should be self-destructing
- @throws missing / incorrect
- use std::memcpy instead of memcpy directly (any bare c function basically)
- @debug statement

# implemented
- disallow goto