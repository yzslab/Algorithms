//
// Created by Zhensheng on 2017/5/29.
//

#include <iostream>
#include "KMP.h"

namespace Algorithms {
    KMP::KMP(std::string theStr) {
        str = theStr;
        length = theStr.length();
    }

    int KMP::find(std::string theStr, int offset) {
        prefixComputer = new PrefixComputer(theStr);
        int i, j, theLength = theStr.length();
        for (i = offset, j = 0; i < length; ++i) {
            if (str[i] == theStr[j])
                ++j;
            else
                while (j > 0) {
                    j = (*prefixComputer)[j - 1];
                    if (str[i] == theStr[j]) {
                        ++j;
                        break;
                    }
                }
            if (j == theLength) {
                delete prefixComputer;
                return i - theLength + 1;
            }
        }
        delete prefixComputer;
        return -1;
    }
}