cmake_minimum_required(VERSION 2.6)

# Define a single cmake project
project(kenlm)

# Compile all libraries into lib/
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Define where include files live
include_directories(
  ${PROJECT_SOURCE_DIR}
)

# Process subdirectories
add_subdirectory(util)
add_subdirectory(lm)
