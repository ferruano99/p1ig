# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.20
cmake_policy(SET CMP0009 NEW)

# SRC_FILES at CMakeLists.txt:19 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "C:/Users/ferna/Desktop/Universidad/4/IG/practicas/prac1/src/*.cpp")
set(OLD_GLOB
  "C:/Users/ferna/Desktop/Universidad/4/IG/practicas/prac1/src/Model.cpp"
  "C:/Users/ferna/Desktop/Universidad/4/IG/practicas/prac1/src/Shaders.cpp"
  "C:/Users/ferna/Desktop/Universidad/4/IG/practicas/prac1/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/ferna/Desktop/Universidad/4/IG/practicas/prac1/cmake-build-debug/CMakeFiles/cmake.verify_globs")
endif()