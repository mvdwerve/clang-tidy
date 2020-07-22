#!/bin/bash

docker run -v `pwd`/project -v `pwd`/copernica:/llvm-project/clang-tools-extra/clang-tidy/copernica -v `pwd`/tests:/tests -it mvdwerve/clang-tidy bash
