FROM mvdwerve/llvm-docker

ENV DEBIAN_FRONTEND noninteractive

# move everything over and inject it into 
ADD ./copernica /llvm-project/clang-tools-extra/clang-tidy/copernica
ADD ./inject.sh /llvm-project/
RUN cd /llvm-project && chmod +x ./inject.sh && ./inject.sh

# we can now make clang-tidy, we only have to do the copernica objects
RUN cd /llvm-project/build && ninja clang-tidy && cp /llvm-project/build/bin/clang-tidy /usr/bin/