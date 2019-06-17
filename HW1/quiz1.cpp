#include <iostream>
using namespace std;

class DisjointSet {
private:
    int size;
    int *parent;
public:
    DisjointSet(int s) {
        size = s;
        parent = new int[size];
        for (int i = 0; i < size; ++i) {
            parent[i] = -1;
        }
    }

    //~DisjointSet() { delete[]parent; }

    void Union(int root1, int root2) {
        if (root1 == root2)return;
        if (parent[root1] > parent[root2]) {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        } else {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }

    int Find(int x) {
        if (parent[x] < 0)return x;
        return parent[x] = Find(parent[x]);
    }
};

class starcraft {
private:
    int N, K;
    int count;
public:
    void input() {
        cin >> N >> K;
        int D, X, Y;
        count = 0;

        int u, v, p, q;
        DisjointSet ds1(N + 1);
        DisjointSet ds2(N + 1);

        int j = 0;

        while (true) {
            if (j >= K)
                break;
            cin >> D >> X >> Y;
            if (X > N || Y > N) {
                count++;
                cout << '*' << endl;
                j++;
                continue;
            } else if (D == 1) {
                if (X != Y) {
                    u = ds1.Find(X - 1);
                    v = ds1.Find(Y - 1);
                    ds1.Union(u, v);
                    j++;
                    break;
                }
            } else if (D == 2) {
                if (X == Y) {
                    count++;

                    cout << '*' << endl;
                    j++;
                    continue;
                } else {
                    p = ds2.Find(X - 1);
                    q = ds2.Find(Y - 1);
                    ds2.Union(p, q);
                    j++;
                    break;
                }
            }
        }

        int i;
        for (i = 0; i < K - j; ++i) {
            cin >> D >> X >> Y;
            if (X > N || Y > N) {
                count++;
                cout << '*' << endl;
                continue;
            }

            if (D == 1) {
                if (X == Y) {
                    continue;
                } else {
                    u = ds1.Find(X - 1);
                    v = ds1.Find(Y - 1);
                    if (u == v) {
                        ds1.Union(u, v);
                    } else {
                        count++;
                        cout << '*' << endl;
                    }
                }
            }
            if (D == 2) {
                if (X == Y) {
                    count++;
                    cout << '*' << endl;
                } else {
                    p = ds2.Find(X - 1);
                    q = ds2.Find(Y - 1);
                    if (p <= q) {
                        ds2.Union(p, q);
                    } else {
                        count++;
                        cout << '*' << endl;
                    }
                }
            }
        }
        cout << count;
    }
};

int main(){
    starcraft s;
    s.input();
}

