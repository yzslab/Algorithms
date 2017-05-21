#include <iostream>
#include "DataStructure/BinarySearchTree.h"

int main(){
    try {
        DataStructure::BinarySearchTree<int> binarySearchTree;
        binarySearchTree.insertElement(6).insertElement(3).insertElement(2).insertElement(4).insertElement(1).insertElement(5).insertElement(8).insertElement(7).insertElement(9).insertElement(10);
        std::cout << binarySearchTree.maximum() << std::endl;
        std::cout << binarySearchTree.minimum() << std::endl;
        std::cout << binarySearchTree.predecessor(7) << std::endl;
        std::cout << binarySearchTree.successor(5) << std::endl;
        binarySearchTree.deleteElement(6).deleteElement(2).deleteElement(10);
        return 0;
    } catch (DataStructure::Exceptions::ElementNotFound e) {
        std::cerr<<"Exception ElementNotFound catch."<<std::endl;
        return 1;
    }
}