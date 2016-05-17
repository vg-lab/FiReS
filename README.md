# FiReS - Filtering, Retrieval and Search
(c) 2015. GMRV / URJC

www.gmrv.es
gmrv@gmrv.es

## Introduction

FiReS is a library to ease filtering, search and content-based
retrieval operations over any kind of object that can be characterized
by a set of properties.

## Features and usage:

TODO

## Dependencies

Boost.Any is the only required dependency. OpenMP and Boost's Unit
Test Framework are optional.

## Building

FiReS has been succesfully built and used on Ubuntu 14.04, Mac OSX
Yosemite and Windows 7/8 (Visual Studio 2013 Win64). The following steps
should be enough to build it:

```bash
git clone https://github.com/gmrvvis/FiReS.git
mkdir FiReS/build && cd FiReS/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
