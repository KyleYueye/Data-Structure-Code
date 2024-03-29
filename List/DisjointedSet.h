#ifndef LIST_DISJOINTEDSET_H
#define LIST_DISJOINTEDSET_H

#include <iostream>

using namespace std;


class DisjointSet{
private:
    int size;
    int* parent;
public:
    DisjointSet(int s){
        size = s;
        parent=new int[size];
        for (int i = 0; i < size; ++i) {
            parent[i]=-1;
        }
    }
    ~DisjointSet(){delete []parent;}
    void Union(int root1,int root2){
        if(root1==root2)return;
        if(parent[root1]>parent[root2]){
            parent[root2]+=parent[root1];
            parent[root1] = root2;
        }
        else{
            parent[root1]+=parent[root2];
            parent[root2]=root1;
        }
    }
    int Find(int x){
        if(parent[x]<0)return x;
        return parent[x] = Find(parent[x]);
    }
};





#endif //LIST_DISJOINTEDSET_H