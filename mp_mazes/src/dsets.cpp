/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++){
        elemArr.push_back(-1);
    }
    return;
}

int DisjointSets::find(int elem){
    if(elemArr[elem] < 0){
        return elem;
    }
    elemArr[elem] = find(elemArr[elem]);
    return elemArr[elem];
}

void DisjointSets::setunion(int a, int b){
    int rootA = find(a);
    int rootB = find(b);
    if(rootA == rootB){
        return;
    }
    if(elemArr[rootA] <= elemArr[rootB]){
        elemArr[rootA] = elemArr[rootA] + elemArr[rootB];
        elemArr[rootB] = rootA;
    }
    else{
        elemArr[rootB] = elemArr[rootA]+elemArr[rootB];
        elemArr[rootA] = rootB;
    }

}

int DisjointSets::size(int elem){
    if(elem < 0){
        return -elem;
    }
    return size(elemArr[elem]);
}