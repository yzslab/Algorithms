cmake_minimum_required(VERSION 3.7)
project(BinarySearchTree)
project(RedBlackTree)
project(HashSetTest)

set(CMAKE_CXX_STANDARD 11)

add_executable(BinarySearchTree BinarySearchTreeTest.cpp DataStructure/BinarySearchTree.cpp)
add_executable(RedBlackTree RedBlackTreeTest.cpp DataStructure/RedBlackTree.cpp)
add_executable(HashSetTest HashSetTest.cpp DataStructure/HashSet.cpp)