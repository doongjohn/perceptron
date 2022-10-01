cmake_minimum_required(VERSION 3.24)

project(
  PerceptronXor
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(perceptron_xor ${SRC_FILES})
target_compile_features(
  perceptron_xor
  PRIVATE cxx_std_20
)
