cmake_minimum_required(VERSION 3.15)
project(chattingbotC__)

set(CMAKE_CXX_STANDARD 14)

include_directories("inc/")
aux_source_directory("src/" SOURCE_FILES)

add_executable(chattingbotC__ ${SOURCE_FILES})
