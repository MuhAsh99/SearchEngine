cmake_minimum_required(VERSION 3.20)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)

add_executable(22s_final_proj main.cpp catch_setup.cpp AVLtree.h DocParser.cpp include/StopWords.txt tests.cpp porter2_stemmer.cpp porter2_stemmer.h util/hash.h util/string_view.h DocInfo.cpp DocInfo.h Leaf.cpp Leaf.h UserInterface.cpp)
