//
// Created by Zhensheng on 2017/5/9.
//

#ifndef BINARYSEARCHTREE_REDBLACKTREE_H
#define BINARYSEARCHTREE_REDBLACKTREE_H

#include "Exceptions/ElementNotFound.h"

namespace DataStructure {
    template <typename dataType>
    class RedBlackTree {
    public:
        RedBlackTree() {
            nil = new Nil;
            nil->color = BLACK;
            nil->nil = nil;
            tree = nil;
        }
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
        RedBlackTree<dataType>& leftRotate(dataType data) {
            leftRotateNode(searchNode(&tree, data));
            return *this;
        }
        RedBlackTree<dataType>& rightRotate(dataType data) {
            rightRotateNode(searchNode(&tree, data));
            return *this;
        }
        RedBlackTree<dataType>& insertElement(dataType data) {
            TNode *newNode = new TNode, **p = &tree, **t = &tree;
            newNode->data = data;
            newNode->left = nil;
            newNode->right = nil;
            newNode->color = RED;
            newNode->nil = nil;
            while (*t != nil) {
                p = t;
                if ((*t)->data > data)
                    t = &((*t)->left);
                else
                    t = &((*t)->right);
            }
            newNode->p = *p;
            *t = newNode;
            insertFixUP(&tree, t);
            return *this;
        };
        RedBlackTree<dataType>& deleteElement(dataType data) {
            TNode **node = searchNode(&tree, data);
            TNode *p = (*node)->p, **tmp, *nodeToDelete;
            if ((*node)->left == tree->nil && (*node)->right == tree->nil) {
                delete *node;
                *node = tree->nil;
            } else if ((*node)->left != tree->nil && (*node)->right == tree->nil) {
                nodeToDelete = *node;
                *node = (*node)->left;
                delete nodeToDelete;
            } else if ((*node)->right != tree->nil && (*node)->left == tree->nil) {
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
                *tmp = tree->nil;
            }
            return *this;
        };
    private:
        enum Color {
            RED,
            BLACK
        };

        typedef struct TNode {
            TNode *p;
            TNode *left;
            TNode *right;
            TNode *nil;
            Color color;
            dataType data;
        } Nil;

        TNode *tree;
        Nil *nil;

        static TNode** searchNode(TNode **tree, dataType data) {
            while (*tree != (*tree)->nil) {
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
            if ((*tree)->left != (*tree)->nil)
                return maximumNode(&(*tree)->left);
            TNode **tmp = &(*tree)->p;
            while (*tmp != (*tree)->nil && (*tmp)->left == *tree) {
                tree = tmp;
                tmp = &(*tmp)->p;
            }
            if (*tmp == (*tree)->nil)
                throw Exceptions::ElementNotFound();
            return tmp;
        }

        static TNode** successorNode(TNode **tree) {
            if ((*tree)->right != (*tree)->nil)
                return minimumNode(&(*tree)->right);
            TNode **tmp = &(*tree)->p;
            while (*tmp != (*tree)->nil && (*tmp)->right == *tree) {
                tree = tmp;
                tmp = &(*tmp)->p;
            }
            if (*tmp == (*tree)->nil)
                throw Exceptions::ElementNotFound();
            return tmp;
        }

        static TNode** maximumNode(TNode **tree) {
            while (*tree != (*tree)->nil && (*tree)->right != (*tree)->nil)
                tree = &(*tree)->right;
            if (*tree == (*tree)->nil)
                throw Exceptions::ElementNotFound();
            return tree;
        }

        static TNode** minimumNode(TNode **tree) {
            while (*tree != (*tree)->nil && (*tree)->left != (*tree)->nil)
                tree = &(*tree)->left;
            if (*tree == (*tree)->nil)
                throw Exceptions::ElementNotFound();
            return tree;
        }

        static TNode** leftRotateNode(TNode **tree) {
            TNode *originRoot = (*tree), *right = (*tree)->right;
            *tree = right;
            (*tree)->p = originRoot->p; // 继承原树根的父
            originRoot->right = right->left; // 使原树根接管新树根的左子树
            right->left = originRoot; // 原树根成为新树根的左子树
            originRoot->p = right; // 原树根的父指向新树根
            // 修改新树根新右子树的父指针
            originRoot->right->p = originRoot;
            return tree;
        }

        static TNode** rightRotateNode(TNode **tree) {
            TNode *originRoot = (*tree), *left = (*tree)->left;
            *tree = left; // 使左子树成为新树根
            (*tree)->p = originRoot->p; // 继承原树根的父
            originRoot->left = (*tree)->right; // 原树根接管新树根的右子树
            (*tree)->right = originRoot; // 使原树根成为新树根的右子树
            originRoot->p = *tree; // 原树根父改为新树根
            // 修改新树根新右子树的父指针
            originRoot->left->p = originRoot;
            return tree;
        }

        static TNode** insertFixUP(TNode **tRoot, TNode **redNode) {
            // newNode是新的RED节点，意味着其父节点不能为RED，因此当父节点为RED时需要进行调整
            TNode *uncle, **grandFather, **fatherPtr;
            while ((*redNode)->p->color == RED) {
                /*
                 * 第一种情况，redNode的叔叔节点是红色的
                 * 如果redNode的叔叔节点是红色的，那么把叔叔和父节点改为黑色，爷爷改为红色，则不会破坏到各路径到nil经过黑色节点数相同这个性质
                 * 不过把爷爷节点改成了红色，爷爷的父亲可能也是红色的，因此需要把redNode指向爷爷，进行下一次迭代
                 *
                 * 第二种情况，redNode的叔叔是黑色的
                 * 此时一个节点到nil的各路径经过的黑色节点数一定相同
                 * 如果直接把redNode的父节点置黑色，则在一条路径上增加了一个黑色节点，爷爷节点到nil的各路径经过的黑色节点数则在父节点处出现了差异
                 * 要修复这种情况，不可以直接修改父节点的颜色
                 * 可在redNode的父节点与爷爷节点之间进行左(右)旋
                 * 左(右)旋后，原来的父亲到了原来爷爷的位置，爷爷成为了父亲的其中一个子
                 * 原爷爷是黑色的，父亲是红色，redNode是红色，明显父亲到爷爷到nil的路径比父亲到redNode到nil的路径多了一个黑色节点，因此需要进行颜色重置，把父亲改为黑色，爷爷和redNode改为红色，完事
                 * 至于左旋还是右旋，这里还得看情况，如果新节点在靠内部，还需要进行额外的旋转，让内部转到外部
                 */

                // 取爷爷节点
                if ((*redNode)->p->p->p == (*redNode)->nil)
                    grandFather = tRoot;
                else if ((*redNode)->p->p == (*redNode)->p->p->p->left)
                    grandFather = &(*redNode)->p->p->p->left;
                else
                    grandFather = &(*redNode)->p->p->p->right;

                // 取父亲
                if ((*redNode)->p == (*redNode)->p->p->left)
                    fatherPtr = &(*redNode)->p->p->left;
                else
                    fatherPtr = &(*redNode)->p->p->right;

                // 取叔叔
                if ((*redNode)->p == (*redNode)->p->p->right) {
                    // 在右侧的情况
                    uncle = (*redNode)->p->p->left;
                    // 情况一
                    if (uncle->color == RED) {
                        // 颜色重置
                        uncle->color = BLACK;
                        (*redNode)->p->color = BLACK;
                        (*redNode)->p->p->color = RED;
                        // 进行下一次迭代
                        redNode = grandFather;
                    } else {
                        // 第二种情况
                        // 检查redNode是否在左侧，是的话需要右旋
                        if (*redNode == (*redNode)->p->left) {
                            rightRotateNode(&(*redNode)->p->p->right);
                            redNode = &(*fatherPtr)->right;
                        }
                        // 最后左旋
                        // 先修正颜色
                        (*grandFather)->color = RED;
                        (*fatherPtr)->color = BLACK;
                        leftRotateNode(grandFather);
                    }
                } else {
                    uncle = (*redNode)->p->p->right;
                    // 情况一
                    if (uncle->color == RED) {
                        // 颜色重置
                        uncle->color = BLACK;
                        (*redNode)->p->color = BLACK;
                        (*redNode)->p->p->color = RED;
                        // 进行下一次迭代
                        redNode = grandFather;
                    } else {
                        // 第二种情况
                        // 检查redNode是否在右侧，是的话需要左旋
                        if (*redNode == (*redNode)->p->right) {
                            leftRotateNode(&(*redNode)->p->p->left);
                            redNode = &(*fatherPtr)->left;
                        }
                        // 最后右旋
                        // 先修正颜色
                        (*grandFather)->color = RED;
                        (*fatherPtr)->color = BLACK;
                        rightRotateNode(grandFather);
                    }
                }
            }
            (*tRoot)->color = BLACK;
            return tRoot;
        }

        static TNode** deleteFixUP(TNode **tRoot, TNode **node) {
            // node为黑色时，且node非根节点时进行循环，由于根节点一定要为黑色，因此node为根时需要结束循环
            while ((*tRoot) != (*node) && (*node)->color == BLACK) {
                /*
                 * 如果node为黑色，则经过node的路径，黑色结点数目都少了一个
                 * 如果node的兄弟节点为红色，则node的父节点一定为黑色，且兄弟节点的子一定为黑色
                 */
            }
        }
    };
};

#endif //BINARYSEARCHTREE_REDBLACKTREE_H
