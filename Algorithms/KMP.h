//
// Created by Zhensheng on 2017/5/29.
//

#ifndef FIBONACCISEQUENCEDYNAMICPROGRAMMING_KMP_H
#define FIBONACCISEQUENCEDYNAMICPROGRAMMING_KMP_H

#include <string>
#include <cstring>

namespace Algorithms {
    class KMP {
    public:
        KMP(std::string);
        int find(std::string, int = 0);
    private:
        class PrefixComputer{
        public:
            PrefixComputer(std::string &theStr) {
                pi = computePrefix(theStr);
            }
            int operator[] (int index) {
                return pi[index];
            }
            ~PrefixComputer() {
                delete[] pi;
            }
        private:
            int *pi;

            static int *computePrefix(std::string &theStr) {
                int length = theStr.size(), chIndex, prefix;
                int *pi = new int[length];
                memset(pi, 0, length * sizeof(int));
                for (chIndex = 1, prefix = 0; chIndex < length; ++chIndex) {
                    if (theStr[prefix] == theStr[chIndex])
                        ++prefix;
                    else {
                        while (prefix > 0) {
                            prefix = pi[prefix];
                            if (theStr[prefix] == theStr[chIndex]) {
                                ++prefix;
                                break;
                            }
                        }
                    }
                    pi[chIndex] = prefix;
                }
                return pi;
            }
        };

        std::string str;
        int length;
        PrefixComputer *prefixComputer;
    };
}


#endif //FIBONACCISEQUENCEDYNAMICPROGRAMMING_KMP_H
