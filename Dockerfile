FROM ubuntu:18.04

RUN apt update && apt install -y build-essential cmake git ninja-build
RUN apt install -y python3
RUN git clone --depth 1 https://github.com/llvm/llvm-project.git && rm -r llvm-project/clang-tools-extra/clang-tidy
RUN cd /llvm-project/ && git checkout -b release/10.x
ADD . /llvm-project/clang-tools-extra/clang-tidy 
RUN mkdir /llvm-project/build && cd /llvm-project/build && cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_USE_LINKER=gold -DCMAKE_BUILD_TYPE=Release -G Ninja ../llvm
RUN cd /llvm-project/build && ninja -j4 clang-tidy
