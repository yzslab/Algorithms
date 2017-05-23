//
// Created by Zhensheng on 2017/5/23.
//

#include <iostream>
#include "Algorithms/FibonacciSequenceDynamicProgramming.h"

using namespace std;

int main(void) {
    Algorithms::FibonacciSequenceDynamicProgramming fibonacciSequenceDynamicProgramming(50);
    cout<<fibonacciSequenceDynamicProgramming.topDownWithMemoization()<<endl;
    cout<<fibonacciSequenceDynamicProgramming.bottomUp()<<endl;
    return 0;
}