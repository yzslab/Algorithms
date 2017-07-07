//
// Created by Zhensheng on 2017/7/7.
//
#include <iostream>
#include "DataStructure/Heap.h"

using namespace std;
using namespace DataStructure;

int main(int argc, char *argv[]) {
  int length;
  cout<<"Lenght: ";
  cin>>length;
  Heap<int>::HeapNode nodes[length];
  int priority, value;
  cout<<endl<<"Value Priority"<<endl;
  for (int i = 0; i < length; ++i) {
    cin>>value>>priority;
    nodes[i] = Heap<int>::HeapNode(value, priority);
  }
  Heap<int> heap(Heap<int>::MAX_HEAP, length, nodes, length);
  heap.print();
  auto sortedHeap = heap.heapSort();
  for (int i = 0; i < length; ++i)
    cout<<sortedHeap[i].first<<' ';
  cout<<endl;
  cin.get();
  cin.get();
  return 0;
}