
# This creates a library 'mybla' which can be used by executables (so we do not need to add these
# files to all the exes we want to use them in
add_library(mybla SHARED calcinverse.cpp localheap.cpp exception.cpp)
if(WIN32)
target_compile_options(mybla PRIVATE -DNGS_EXPORTS)
endif(WIN32)

install(TARGETS mybla DESTINATION .)