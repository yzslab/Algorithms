//
// Created by Zhensheng on 2017/5/23.
//

#include <iostream>
#include "Algorithms/MaximumSubarray.h"

int main(void) {
    int intArray[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7}; // intArray[7..10], sum = 43
    Algorithms::MaximumSubarray<int> maximumSubarray(intArray, 16);
    Algorithms::MaximumSubarray<int>::result theResult = maximumSubarray.findMaximumSubarray();
    std::cout << "Max Subarray: intArray[" << theResult.low << ".." << theResult.high << "], Sum: " << theResult.sum << std::endl;
    return 0;
}