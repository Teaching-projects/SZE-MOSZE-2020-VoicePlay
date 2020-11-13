FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
  g++ \
  g++-10 \
  make \
  cppcheck \
  valgrind \
  cmake \
  libgtest-dev \
&& rm -rf /var/lib/apt/lists/*
