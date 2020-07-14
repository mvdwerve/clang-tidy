FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt install -y build-essential cmake git ninja-build python3
RUN git clone --depth 1 https://github.com/llvm/llvm-project.git
RUN cd /llvm-project/ && git checkout -b release/10.x
ADD ./copernica /llvm-project/clang-tools-extra/clang-tidy/copernica
ADD ./inject.sh /llvm-project/
RUN cd /llvm-project && ./inject.sh
RUN mkdir /llvm-project/build && cd /llvm-project/build && cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_USE_LINKER=gold -DCMAKE_BUILD_TYPE=Release -G Ninja ../llvm
RUN cd /llvm-project/build && ninja clang-tidy