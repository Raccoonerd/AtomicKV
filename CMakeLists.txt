cmake_minimum_required(VERSION 3.16)

project(AtomicKV
  DESCRIPTION "Multithreaded key-value storage"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
  src/main.cpp
  src/KVStore.cpp
)

add_executable(
  ${PROJECT_NAME}
  ${SOURCES}
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE Threads::Threads
)
