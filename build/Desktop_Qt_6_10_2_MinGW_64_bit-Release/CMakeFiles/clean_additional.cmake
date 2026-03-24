# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\SystemHelper_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SystemHelper_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\TestyAplikacji_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TestyAplikacji_autogen.dir\\ParseCache.txt"
  "SystemHelper_autogen"
  "TestyAplikacji_autogen"
  )
endif()
