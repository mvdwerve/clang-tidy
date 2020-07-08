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
make -C /tools/clang/tools/extra/clang-tidy
```
