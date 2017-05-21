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
            (*tree)->p = originRoot->p; // �̳�ԭ�����ĸ�
            originRoot->right = right->left; // ʹԭ�����ӹ���������������
            right->left = originRoot; // ԭ������Ϊ��������������
            originRoot->p = right; // ԭ�����ĸ�ָ��������
            // �޸����������������ĸ�ָ��
            originRoot->right->p = originRoot;
            return tree;
        }

        static TNode** rightRotateNode(TNode **tree) {
            TNode *originRoot = (*tree), *left = (*tree)->left;
            *tree = left; // ʹ��������Ϊ������
            (*tree)->p = originRoot->p; // �̳�ԭ�����ĸ�
            originRoot->left = (*tree)->right; // ԭ�����ӹ���������������
            (*tree)->right = originRoot; // ʹԭ������Ϊ��������������
            originRoot->p = *tree; // ԭ��������Ϊ������
            // �޸����������������ĸ�ָ��
            originRoot->left->p = originRoot;
            return tree;
        }

        static TNode** insertFixUP(TNode **tRoot, TNode **redNode) {
            // newNode���µ�RED�ڵ㣬��ζ���丸�ڵ㲻��ΪRED����˵����ڵ�ΪREDʱ��Ҫ���е���
            TNode *uncle, **grandFather, **fatherPtr;
            while ((*redNode)->p->color == RED) {
                /*
                 * ��һ�������redNode������ڵ��Ǻ�ɫ��
                 * ���redNode������ڵ��Ǻ�ɫ�ģ���ô������͸��ڵ��Ϊ��ɫ��үү��Ϊ��ɫ���򲻻��ƻ�����·����nil������ɫ�ڵ�����ͬ�������
                 * ������үү�ڵ�ĳ��˺�ɫ��үү�ĸ��׿���Ҳ�Ǻ�ɫ�ģ������Ҫ��redNodeָ��үү��������һ�ε���
                 *
                 * �ڶ��������redNode�������Ǻ�ɫ��
                 * ��ʱһ���ڵ㵽nil�ĸ�·�������ĺ�ɫ�ڵ���һ����ͬ
                 * ���ֱ�Ӱ�redNode�ĸ��ڵ��ú�ɫ������һ��·����������һ����ɫ�ڵ㣬үү�ڵ㵽nil�ĸ�·�������ĺ�ɫ�ڵ������ڸ��ڵ㴦�����˲���
                 * Ҫ�޸����������������ֱ���޸ĸ��ڵ����ɫ
                 * ����redNode�ĸ��ڵ���үү�ڵ�֮�������(��)��
                 * ��(��)����ԭ���ĸ��׵���ԭ��үү��λ�ã�үү��Ϊ�˸��׵�����һ����
                 * ԭүү�Ǻ�ɫ�ģ������Ǻ�ɫ��redNode�Ǻ�ɫ�����Ը��׵�үү��nil��·���ȸ��׵�redNode��nil��·������һ����ɫ�ڵ㣬�����Ҫ������ɫ���ã��Ѹ��׸�Ϊ��ɫ��үү��redNode��Ϊ��ɫ������
                 * ���������������������ﻹ�ÿ����������½ڵ��ڿ��ڲ�������Ҫ���ж������ת�����ڲ�ת���ⲿ
                 */

                // ȡүү�ڵ�
                if ((*redNode)->p->p->p == (*redNode)->nil)
                    grandFather = tRoot;
                else if ((*redNode)->p->p == (*redNode)->p->p->p->left)
                    grandFather = &(*redNode)->p->p->p->left;
                else
                    grandFather = &(*redNode)->p->p->p->right;

                // ȡ����
                if ((*redNode)->p == (*redNode)->p->p->left)
                    fatherPtr = &(*redNode)->p->p->left;
                else
                    fatherPtr = &(*redNode)->p->p->right;

                // ȡ����
                if ((*redNode)->p == (*redNode)->p->p->right) {
                    // ���Ҳ�����
                    uncle = (*redNode)->p->p->left;
                    // ���һ
                    if (uncle->color == RED) {
                        // ��ɫ����
                        uncle->color = BLACK;
                        (*redNode)->p->color = BLACK;
                        (*redNode)->p->p->color = RED;
                        // ������һ�ε���
                        redNode = grandFather;
                    } else {
                        // �ڶ������
                        // ���redNode�Ƿ�����࣬�ǵĻ���Ҫ����
                        if (*redNode == (*redNode)->p->left) {
                            rightRotateNode(&(*redNode)->p->p->right);
                            redNode = &(*fatherPtr)->right;
                        }
                        // �������
                        // ��������ɫ
                        (*grandFather)->color = RED;
                        (*fatherPtr)->color = BLACK;
                        leftRotateNode(grandFather);
                    }
                } else {
                    uncle = (*redNode)->p->p->right;
                    // ���һ
                    if (uncle->color == RED) {
                        // ��ɫ����
                        uncle->color = BLACK;
                        (*redNode)->p->color = BLACK;
                        (*redNode)->p->p->color = RED;
                        // ������һ�ε���
                        redNode = grandFather;
                    } else {
                        // �ڶ������
                        // ���redNode�Ƿ����Ҳ࣬�ǵĻ���Ҫ����
                        if (*redNode == (*redNode)->p->right) {
                            leftRotateNode(&(*redNode)->p->p->left);
                            redNode = &(*fatherPtr)->left;
                        }
                        // �������
                        // ��������ɫ
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
            // nodeΪ��ɫʱ����node�Ǹ��ڵ�ʱ����ѭ�������ڸ��ڵ�һ��ҪΪ��ɫ�����nodeΪ��ʱ��Ҫ����ѭ��
            while ((*tRoot) != (*node) && (*node)->color == BLACK) {
                /*
                 * ���nodeΪ��ɫ���򾭹�node��·������ɫ�����Ŀ������һ��
                 * ���node���ֵܽڵ�Ϊ��ɫ����node�ĸ��ڵ�һ��Ϊ��ɫ�����ֵܽڵ����һ��Ϊ��ɫ
                 */
            }
        }
    };
};

#endif //BINARYSEARCHTREE_REDBLACKTREE_H
