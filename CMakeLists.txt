cmake_minimum_required(VERSION 3.10)
project(EntropyTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/headers)

add_executable(entropy_test
	entropy_test.cpp
	cpp/entropy.cpp
)

add_executable(huffman_test
	huffman_test.cpp
	cpp/huffman.cpp
)

add_executable(sf_test
	sf_test.cpp
	cpp/sha_fanno.cpp
)