//
// Created by Zhensheng on 2017/5/19.
//

#ifndef REDBLACKTREE_HASHSET_H
#define REDBLACKTREE_HASHSET_H

#include <cstring>

namespace DataStructure {

    template<typename dataType>
    class HashSet {
    public:
        HashSet(int bucketNum = 513) {
            this->bucketNum = bucketNum;
            buckets = new Bucket[bucketNum];
            memset(buckets, 0, sizeof(Bucket) * bucketNum);
        }

        bool addElement(dataType data) {
            int bucketPos = getElementBucket(data);
            Node *newNode =
        }

        int getElementBucket(dataType data) {
            return hashElement(data) % bucketNum;
        }

        static int hashElement(dataType data) {
            size_t dataSize = sizeof(data);
            int i, num = 0;
            for (i = 0; i < dataSize; ++i)
                num += (*(((unsigned char *)&data) + i));
            return num;
        }
    private:
        int bucketNum;

        struct Node {
            dataType data;
            Node *next;
        };

        struct Bucket {
            Node *node;
        };

        Bucket *buckets;
    };

}

#endif //REDBLACKTREE_HASHSET_H
