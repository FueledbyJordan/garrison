cmake_minimum_required(VERSION 3.15)

project(garrison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
configure_file(${CMAKE_SOURCE_DIR}/garrison.cfg ${CMAKE_BINARY_DIR} COPYONLY)

set(LIB_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ArgParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/File.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FileList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FileParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ParserBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utilities.cpp
)

add_library(garrison_library SHARED
    ${SRC_FILES}
)
target_include_directories(garrison_library PUBLIC ${LIB_FILE_PATH})

add_executable(garrison src/main.cpp)
target_link_libraries(garrison garrison_library)