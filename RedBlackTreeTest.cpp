//
// Created by Zhensheng on 2017/5/9.
//

#include <iostream>
#include "DataStructure/RedBlackTree.h"

int main(void) {
    try {
        DataStructure::RedBlackTree<int> redBlackTree;
        redBlackTree.insertElement(10).insertElement(85).insertElement(15).insertElement(70).insertElement(20).insertElement(60).insertElement(30).insertElement(50).insertElement(65).insertElement(80).insertElement(90).insertElement(40).insertElement(5).insertElement(55);
        std::cout << redBlackTree.maximum() << std::endl;
        std::cout << redBlackTree.minimum() << std::endl;
        std::cout << redBlackTree.predecessor(7) << std::endl;
        std::cout << redBlackTree.successor(5) << std::endl;
        redBlackTree.deleteElement(6).deleteElement(2).deleteElement(10);
        redBlackTree.leftRotate(3).rightRotate(4);
        return 0;
    } catch (DataStructure::Exceptions::ElementNotFound e) {
        std::cerr<<"Exception ElementNotFound catch.\n"<<std::endl;
        return 1;
    }
}