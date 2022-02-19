cmake_minimum_required(VERSION 3.0)
project(examples)

set(CMAKE_CXX_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if (MSVC)
  add_compile_options(/W4 /WX -lpthread -pthread)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror -lpthread -pthread)
endif()

add_executable(2022_02_09 "2022_02_09.cpp")

add_executable(2022_02_16 "2022_02_16.cpp")
target_link_libraries(2022_02_16 PRIVATE Threads::Threads)
