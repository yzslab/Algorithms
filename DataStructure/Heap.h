//
// Created by Zhensheng on 2017/7/7.
//

#ifndef KMP_HEAP_H
#define KMP_HEAP_H
#include <iostream>
#include <climits>
#include <utility>
#include <exception>
#include <cstring>
#include "../../../../../cygwin64/lib/gcc/x86_64-pc-cygwin/5.4.0/include/c++/bits/stl_pair.h"

namespace DataStructure {

template<typename dataType>
class Heap {
 public:
  typedef std::pair<dataType, int> HeapNode;
  enum HEAP_TYPE {
    MAX_HEAP,
    MIN_HEAP
  };
  Heap(HEAP_TYPE, int);
  Heap(HEAP_TYPE, int, HeapNode*, int);
  virtual ~Heap();

  void insert(HeapNode);
  void updatePriority(HeapNode, int);
  HeapNode extremum();
  HeapNode extractExtremun();
  HeapNode* heapSort();
  bool isFullHeap();
  bool isEmptyHeap();
  void print();
 private:
  HEAP_TYPE heapType;
  int capacity;
  int length;
  HeapNode *nodes;

  void heapify(int i);
  void buildHeap();
  void updatePriority(int, int);
  void print(int, int = 0);
  static int parent(int i);
  static int left(int i);
  static int right(int i);
};

}

namespace DataStructure {
template <typename dataType>
Heap<dataType>::Heap(HEAP_TYPE heapType, int capacity){
  this->heapType = heapType;
  this->capacity = capacity;
  this->nodes = new HeapNode[capacity];
  length = 0;
}

template <typename dataType>
Heap<dataType>::Heap(HEAP_TYPE heapType, int capacity, HeapNode* nodes, int length) : Heap(heapType, capacity) {
  if (length > capacity)
    throw std::exception();
  memcpy(this->nodes, nodes, sizeof(HeapNode) * length);
  this->length = length;
  buildHeap();
}

template <typename dataType>
void Heap<dataType>::heapify(int i) {
  int leftIndex;
  int rightIndex;
  int extremumIndex;
  HeapNode tmp;
  while (i >= 0 && i < length) {
    leftIndex = left(i);
    rightIndex = right(i);
    extremumIndex = i;
    if (heapType == MAX_HEAP) {
      if (leftIndex < length && nodes[extremumIndex].second < nodes[leftIndex].second)
        extremumIndex = leftIndex;
      if (rightIndex < length && nodes[extremumIndex].second < nodes[rightIndex].second)
        extremumIndex = rightIndex;
    } else {
      if (leftIndex < length && nodes[extremumIndex].second > nodes[leftIndex].second)
        extremumIndex = leftIndex;
      if (rightIndex < length && nodes[extremumIndex].second > nodes[rightIndex].second)
        extremumIndex = rightIndex;
    }
    if (extremumIndex != i) {
      tmp = nodes[i];
      nodes[i] = nodes[extremumIndex];
      nodes[extremumIndex] = tmp;
      i = extremumIndex;
    } else
      break;
  }
}

template <typename dataType>
void Heap<dataType>::buildHeap() {
  for (int i = length / 2 - 1; i >= 0; --i)
    heapify(i);
}

template <typename dataType>
Heap<dataType>::~Heap() {
  delete[] nodes;
}

template <typename dataType>
void Heap<dataType>::insert(HeapNode node) {
  if (length >= capacity)
    throw std::exception();
  nodes[length++] = node;
  updatePriority(length - 1, node.second);
}

template <typename dataType>
void Heap<dataType>::updatePriority(HeapNode node, int newPriority) {
  for (int i = length - 1; i >= 0; --i)
    if (nodes[i] == node)
      updatePriority(i, newPriority);
}

template <typename dataType>
void Heap<dataType>::updatePriority(int i, int newPriority) {
  HeapNode tmp;
  if (i >= length)
    return;
  nodes[i].second = newPriority;
  for (int parentIndex = parent(i); parentIndex >= 0; i = parentIndex, parentIndex = parent(parentIndex)) {
    if (heapType == MAX_HEAP) {
      if (nodes[i].second > nodes[parentIndex].second) {
        tmp = nodes[i];
        nodes[i] = nodes[parentIndex];
        nodes[parentIndex] = tmp;
      } else
        break;
    } else {
      if (nodes[i].second < nodes[parentIndex].second) {
        tmp = nodes[i];
        nodes[i] = nodes[parentIndex];
        nodes[parentIndex] = tmp;
      } else
        break;
    }
  }
}

template <typename dataType>
typename Heap<dataType>::HeapNode Heap<dataType>::extremum() {
  return nodes[0];
}

template <typename dataType>
typename Heap<dataType>::HeapNode Heap<dataType>::extractExtremun() {
  HeapNode extremumNode = extremum();
  nodes[0] = nodes[--length];
  heapify(0);
  return extremumNode;
}

template <typename dataType>
typename Heap<dataType>::HeapNode* Heap<dataType>::heapSort() {
  HeapNode *sortedNodes = new HeapNode[length], *originNodes = nodes, tmp;
  int originLength = length;
  memcpy(sortedNodes, nodes, sizeof(HeapNode) * length);
  nodes = sortedNodes;
  for (int i = length - 1; i > 0; --i) {
    tmp = nodes[0];
    nodes[0] = nodes[i];
    nodes[i] = tmp;
    --length;
    heapify(0);
  }
  nodes = originNodes;
  length = originLength;

  return sortedNodes;
}

template <typename dataType>
bool Heap<dataType>::isFullHeap() {
  return length == capacity;
}

template <typename dataType>
bool Heap<dataType>::isEmptyHeap(){
  return length == 0;
}

template <typename dataType>
void Heap<dataType>::print() {
  print(0);
}

template <typename dataType>
void Heap<dataType>::print(int i, int blankSpace) {
  if (i < 0 || i >= length)
    return;
  for (int space = 0; space < blankSpace; ++space)
    std::cout<<" ";
  std::cout<<"Value: "<<nodes[i].first<<", Priority: "<<nodes[i].second<<std::endl;
  // std::cout<<"Left: "<<std::endl;
  blankSpace += 4;
  print(left(i), blankSpace);
  // std::cout<<"Right: "<<std::endl;
  print(right(i), blankSpace);
}

template <typename dataType>
int Heap<dataType>::parent(int i) {
  return (i + 1) / 2 - 1;
}

template <typename dataType>
int Heap<dataType>::left(int i) {
  return 2 * i + 1;
}

template <typename dataType>
int Heap<dataType>::right(int i) {
  return 2 * i + 2;
}

}
#endif //KMP_HEAP_H
