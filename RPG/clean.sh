#!/bin/bash
find . -regex '.*\.\(cpp\|hpp\|c\|h\)' -exec clang-format -style=file -i {} \;
#clang-format --verbose -i -style=file *.c
