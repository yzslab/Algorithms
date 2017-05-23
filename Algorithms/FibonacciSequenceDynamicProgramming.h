//
// Created by Zhensheng on 2017/5/23.
//

#ifndef MAXIMUMSUBARRAY_FIBONACCISEQUENCEDYNAMICPROGRAMMING_H
#define MAXIMUMSUBARRAY_FIBONACCISEQUENCEDYNAMICPROGRAMMING_H

namespace Algorithms {
    class FibonacciSequenceDynamicProgramming {
    public:
        FibonacciSequenceDynamicProgramming(int);
        ~FibonacciSequenceDynamicProgramming();
        unsigned long long topDownWithMemoization();
        unsigned long long bottomUp();

    private:
        int n;
        unsigned long long *tmp;

        void clear();
        unsigned long long doTopDownWithMemoization(int);
        unsigned long long doBottomUp(int);
    };
}


#endif //MAXIMUMSUBARRAY_FIBONACCISEQUENCEDYNAMICPROGRAMMING_H
