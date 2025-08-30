# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SmartHealthLogin_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SmartHealthLogin_autogen.dir\\ParseCache.txt"
  "SmartHealthLogin_autogen"
  )
endif()
