cmake_minimum_required(VERSION 3.20)

project(myHtml LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(myHtml ${SRC_FILES})

target_include_directories(myHtml
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(myHtml PRIVATE cxx_std_20)

target_compile_options(myHtml PRIVATE
  -Wall
  -Wextra
  -Wpedantic
)

