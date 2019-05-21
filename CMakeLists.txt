cmake_minimum_required(VERSION 3.10)
project(calculator)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(inc)

file(GLOB source_files
  "calc.h"
  "calc.cc"
  "expr.h"
  "op.h"
  "status.h"
  "stdafx.h"
  "main.cc"
)

add_executable(calculator ${source_files})
