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
//    ~DisjointSet(){delete []parent;}
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

class kruskal {
private:
    struct edge {
        int beg, end;
        int w;

        bool operator<=(const edge &rp) const { return w <= rp.w; }

        bool operator>=(const edge &rp) const { return w >= rp.w; }
    };

    edge *store;
    int n, m;
    int sum;

    template<class T>
    int divide(T a[], int low, int high) {
        T k = a[low];
        do {
            while (low < high && a[high] >= k)--high;
            if (low < high) {
                a[low] = a[high];
                ++low;
            }
            while (low < high && a[low] <= k)++low;
            if (low < high) {
                a[high] = a[low];
                --high;
            }
        } while (low != high);
        a[low] = k;
        return low;
    }

    template<class T>
    void quickSort(T a[], int low, int high) {
        int mid;
        if (low >= high)return;
        mid = divide<T>(a, low, high);
        quickSort<T>(a, low, mid - 1);
        quickSort<T>(a, mid + 1, high);
    }

    template<class T>
    void quickSort(T a[], int size) {
        quickSort<T>(a, 0, size - 1);
    }

public:
    void input() {
        sum = 0;
        cin >> n >> m;
        store = new edge[m];
        for (int i = 0; i < m; ++i) {
            cin >> store[i].beg >> store[i].end >> store[i].w;
        }
    }

    void krus() {
        quickSort<edge>(store, m);

        DisjointSet ds(n);
        int done = 0, u, v, i = 0;
        edge e;
        while (done < n - 1) {
            e = store[i];
            u = ds.Find(e.beg);
            v = ds.Find(e.end);
            if (u != v) {
                done++;
                ds.Union(u, v);
//                cout << '(' << e.beg << ',' << e.end << ") ";
                sum += e.w;
            }
            i++;
        }
        cout << sum;
    }
};

int main(){
    kruskal kruskal1;
    kruskal1.input();
    kruskal1.krus();

}