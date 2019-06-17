#include <iostream>
using namespace std;

class DisjointSet
{
private:
    int size;
    int *parent;

public:
    DisjointSet(int s);
    ~DisjointSet() {delete [] parent;}
    void Union(int root1, int root2);
    int find(int x);
};

DisjointSet::DisjointSet(int s):size(s)
{
    parent = new int[s];
    for (int i = 0;i < size;++i)
        parent[i] = i;
}

void DisjointSet::Union(int root1, int root2)
{
    if (root1 == root2)
        return;
    int f1 = find(root1), f2 = find(root2);
    if (f1!=f2)
        parent[f1] = f2;
}

int DisjointSet::find(int x)
{
    if (x == parent[x])
        return x;
    return parent[x]=find(parent[x]);
}

int main()
{
    int n, k;
    cin>>n>>k;
    int type, p1, p2;
    int count = 0;
    int out = n;
    DisjointSet s(3*out+1);
    for (int i = 0;i < k;++i)
    {
        cin>>type>>p1>>p2;
        if ((p1 > n || p2 > n) || (type == 2 && p1 == p2)) {
            ++count;
            continue;
        }
        if (type == 1) {
            if (s.find(p1) == s.find(p2+out) || s.find(p1) == s.find(p2+2*out))
                ++count;
            else {
                s.Union(p1, p2);
                s.Union(p1+out, p2+out);
                s.Union(p1+2*out, p2+2*out);
            }
        }
        else {
            if (s.find(p1) == s.find(p2+2*out) || s.find(p1) == s.find(p2))
                ++count;
            else {
                s.Union(p1, p2+out);
                s.Union(p1+out, p2+2*out);
                s.Union(p1+2*out, p2);
            }
        }
    }
    cout<<count;
    return 0;
}


