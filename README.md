# clang-tidy
Fork of clang-tidy, with some extra Copernica checks.

## Building

```
mkdir build/
cd build/
git clone --depth 1 https://github.com/llvm/llvm-project.git
rm -r llvm-project/clang-tools-extra/clang-tidy
ln -s `cd .. && pwd -L` llvm-project/clang-tools-extra/clang-tidy
cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_USE_LINKER=gold -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" llvm-project/llvm
make -j4 clang-tidy
```

## Checks
### Todo
- no getAbc() and setAbc() as method names
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
- automate @var for private members
- autofix docblock variables


### Done
- don't throw from publicly accessible methods (or methods in general)
- private members should start with _
