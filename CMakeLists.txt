cmake_minimum_required(VERSION 3.15)
project(AtomicKV CXX)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DBOOST_LOG_DYN_LINK)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(BOOST_LIBRARIES
    boost_thread
    boost_log
    boost_log_setup
    boost_filesystem
    boost_date_time
    boost_program_options 
)

set(SOURCES
    src/main.cpp
    src/KVStore.cpp
    src/Parser.cpp
    src/Logger.cpp
    src/Session.cpp
    src/Server.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
    ${BOOST_LIBRARIES}
    pthread
)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)
