/* Your code here! */
#pragma once
#include <vector>
#include <queue>
#include <algorithm>

class DisjointSets{
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        std::vector<int>elemArr;
};