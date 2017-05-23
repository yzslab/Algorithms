//
// Created by Zhensheng on 2017/5/23.
//

#include <cstring>
#include <climits>
#include "FibonacciSequenceDynamicProgramming.h"

namespace Algorithms {
    FibonacciSequenceDynamicProgramming::FibonacciSequenceDynamicProgramming(int n) {
        this->n = n;
        this->tmp = new unsigned long long[n + 1];
    }

    FibonacciSequenceDynamicProgramming::~FibonacciSequenceDynamicProgramming() {
        delete[] this->tmp;
    }

    unsigned long long FibonacciSequenceDynamicProgramming::topDownWithMemoization() {
        clear();
        return doTopDownWithMemoization(n);
    }

    unsigned long long FibonacciSequenceDynamicProgramming::bottomUp() {
        return doBottomUp(n);
    }

    void FibonacciSequenceDynamicProgramming::clear() {
        for (int i = 0; i <= n; ++i)
            this->tmp[i] = INT_MIN;
    }

    unsigned long long FibonacciSequenceDynamicProgramming::doTopDownWithMemoization(int n) {
        if (this->tmp[n] != INT_MIN)
            return this->tmp[n];
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        return ((this->tmp[n - 2] = doTopDownWithMemoization(n - 2)) + (this->tmp[n - 1] = doTopDownWithMemoization(n - 1)));
    }

    unsigned long long FibonacciSequenceDynamicProgramming::doBottomUp(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        this->tmp[0] = 0;
        this->tmp[1] = 1;
        for (int i = 2; i <= n; ++i)
            this->tmp[i] = this->tmp[i - 2] + this->tmp[i - 1];
        return this->tmp[n];
    }
}