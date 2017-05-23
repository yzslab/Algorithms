//
// Created by Zhensheng on 2017/5/23.
//

#ifndef HASHSETTEST_MAXIMUMSUBARRAY_H
#define HASHSETTEST_MAXIMUMSUBARRAY_H

#include <cstring>
#include <climits>

namespace Algorithms {
    template <typename dataType>
    class MaximumSubarray {
    public:
        struct result {
            int low, high, sum;
        };

        MaximumSubarray(dataType *dataArray, int length) {
            array = new dataType[length];
            std::memcpy(array, dataArray, sizeof(dataType) * length);
            this->length = length;
        };

        result findMaximumSubarray() {
            return doFindMaximumSubarray(0, length - 1);
        }

        ~MaximumSubarray() {
            delete[] array;
        };
    private:
        dataType *array;
        int length;

        result doFindMaximumSubarray(int low, int high) {
            struct result maximumSubarray;
            if (low == high) {
                maximumSubarray.low = low;
                maximumSubarray.high = high;
                maximumSubarray.sum = array[low];
                return maximumSubarray;
            }
            struct result maxCrossingSubaray, maxLeftSubarray, maxRightSubarray;
            int mid = (high + low) / 2;
            maxCrossingSubaray = doFindMaximumCrossingSubarray(low, mid, high);
            maxLeftSubarray = doFindMaximumSubarray(low, mid);
            maxRightSubarray = doFindMaximumSubarray(mid + 1, high);
            if (maxCrossingSubaray.sum > maxLeftSubarray.sum)
                maximumSubarray = maxCrossingSubaray;
            else
                maximumSubarray = maxLeftSubarray;
            if (maximumSubarray.sum > maxRightSubarray.sum)
                return maximumSubarray;
            return maxRightSubarray;
        }

        result doFindMaximumCrossingSubarray(int low, int mid, int high) {
            struct result result;
            int lowPos = -1, highPos = -1, i, sum, maximum;
            for (i = mid, maximum = sum = 0; i >= low; --i) {
                sum += array[i];
                if (sum > maximum) {
                    lowPos = i;
                    maximum = sum;
                }
            }
            result.sum = 0;
            result.sum += maximum;
            for (i = mid + 1, maximum = sum = 0; i <= high; ++i) {
                sum += array[i];
                if (sum > maximum) {
                    highPos = i;
                    maximum = sum;
                }
            }
            result.sum += maximum;
            result.low = lowPos;
            result.high = highPos;
            return result;
        }
    };
}


#endif //HASHSETTEST_MAXIMUMSUBARRAY_H
