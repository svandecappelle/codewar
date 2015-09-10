#!/bin/bash

mkdir -p build
cd build && cmake --clean-first .. && make
