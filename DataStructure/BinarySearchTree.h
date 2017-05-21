//
// Created by Zhensheng on 2017/5/7.
//
#include "Exceptions/ElementNotFound.h"

namespace DataStructure {
#ifndef ALGORITHMS_BINARYSEARCHTREE_H
#define ALGORITHMS_BINARYSEARCHTREE_H

    template <typename dataType>
    class BinarySearchTree {
    public:
        BinarySearchTree() {
            this->tree = nullptr;
        };
        dataType predecessor(dataType data) {
            TNode **node = searchNode(&tree, data);
            return (*(this->predecessorNode(node)))->data;
        }
        dataType successor(dataType data) {
            TNode **node = searchNode(&tree, data);
            return (*(this->successorNode(node)))->data;
        };
        dataType maximum() {
            return (*(this->maximumNode(&tree)))->data;
        };
        dataType minimum() {
            return (*(this->minimumNode(&tree)))->data;
        };
        BinarySearchTree<dataType>& insertElement(dataType data) {
            TNode *newNode = new TNode, **p = &tree, **t = &tree;
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            while (*t) {
                p = t;
                if ((*t)->data > data)
                    t = &((*t)->left);
                else
                    t = &((*t)->right);
            }
            newNode->p = *p;
            *t = newNode;
            return *this;
        };
        BinarySearchTree<dataType>& deleteElement(dataType data) {
            TNode **node = searchNode(&tree, data);
            TNode *p = (*node)->p, **tmp, *nodeToDelete;
            if (!(*node)->left && !(*node)->right) {
                delete *node;
                *node = nullptr;
            } else if ((*node)->left && !(*node)->right) {
                nodeToDelete = *node;
                *node = (*node)->left;
                delete nodeToDelete;
            } else if ((*node)->right && !(*node)->left) {
                nodeToDelete = *node;
                *node = (*node)->right;
                delete nodeToDelete;
            } else {
                tmp = successorNode(node);
                (*tmp)->p = (*node)->p;
                (*tmp)->left = (*node)->left;
                if (*tmp != (*node)->right)
                    (*tmp)->right = (*node)->right;
                delete *node;
                *node = *tmp;
                *tmp = nullptr;
            }
            return *this;
        };
    private:
        struct TNode {
            TNode *p;
            TNode *left;
            TNode *right;
            dataType data;
        };

        TNode *tree;

        static TNode** searchNode(TNode **tree, dataType data) {
            while (*tree) {
                if ((*tree)->data == data)
                    return tree;
                if ((*tree)->data > data)
                    tree = &(*tree)->left;
                else
                    tree = &(*tree)->right;
            }
            throw Exceptions::ElementNotFound();
        }

        static TNode** predecessorNode(TNode **tree) {
            if ((*tree)->left)
                return maximumNode(&(*tree)->left);
            TNode **tmp = &(*tree)->p;
            while (*tmp && (*tmp)->left == *tree) {
                tree = tmp;
                tmp = &(*tmp)->p;
            }
            if (!*tmp)
                throw Exceptions::ElementNotFound();
            return tmp;
        }

        static TNode** successorNode(TNode **tree) {
            if ((*tree)->right)
                return minimumNode(&(*tree)->right);
            TNode **tmp = &(*tree)->p;
            while (*tmp && (*tmp)->right == *tree) {
                tree = tmp;
                tmp = &(*tmp)->p;
            }
            if (!*tmp)
                throw Exceptions::ElementNotFound();
            return tmp;
        }

        static TNode** maximumNode(TNode **tree) {
            while (*tree && (*tree)->right)
                tree = &(*tree)->right;
            if (!*tree)
                throw Exceptions::ElementNotFound();
            return tree;
        }

        static TNode** minimumNode(TNode **tree) {
            while (*tree && (*tree)->left)
                tree = &(*tree)->left;
            if (!*tree)
                throw Exceptions::ElementNotFound();
            return tree;
        }
    };

#endif //ALGORITHMS_BINARYSEARCHTREE_H
}
