//
// Created by Zhensheng on 2017/5/29.
//

#include <iostream>
#include "Algorithms/KMP.h"

using namespace std;
using namespace Algorithms;

int main(void) {
    KMP kmp("abcabbab");
    cout<<kmp.find("abbab")<<endl;
    return 0;
}