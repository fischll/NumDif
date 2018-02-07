
# This creates a library 'mybla' which can be used by executables (so we do not need to add these
# files to all the exes we want to use them in
add_library(mybla calcinverse.cpp localheap.cpp exception.cpp)
