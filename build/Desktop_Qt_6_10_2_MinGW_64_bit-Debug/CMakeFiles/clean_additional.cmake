# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SystemHelper_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SystemHelper_autogen.dir\\ParseCache.txt"
  "SystemHelper_autogen"
  )
endif()
