#include <iostream>
using namespace std;

template <class T>
class hfTree {
private:
    struct Node {
        T data;
        int weight;
        int parent, left, right;
    };

    Node *elem;
    int length;
public:
    struct hfCode {
        T data;
        unsigned long int hflen;
    };

    hfTree(const T *x, const int *w, int size) {
        const long int MAX_INT = 5000000000;
        int min1, min2;
        int z, y;

        length = 2 * size;
        elem = new Node[length];

        for (int i = size; i < length; ++i) {
            elem[i].weight = w[i - size];
            elem[i].data = x[i - size];
            elem[i].parent = elem[i].left = elem[i].right = 0;
        }

        for (int i = size - 1; i >= 0; --i) {
            min1 = min2 = MAX_INT;
            z = y = 0;
            for (int j = i + 1; j < length; ++j)
                if (elem[j].parent == 0)
                    if (elem[j].weight <= min1) {
                        min2 = min1;
                        min1 = elem[j].weight;
                        z = y;
                        y = j;
                    } else if (elem[j].weight <= min2) {
                        min2 = elem[j].weight;
                        z = j;
                    }
            elem[i].weight = min1 + min2;
            elem[i].left = z;
            elem[i].right = y;
            elem[i].parent = 0;
            elem[z].parent = i;
            elem[y].parent = i;
        }
    }

    void get() {
        hfCode result[length];
        int size = length / 2;
        int p, s;
        unsigned long int total = 0;
        for (int i = size; i < length; ++i) {
            result[i - size].data = elem[i].data;
            result[i - size].hflen = 0;
            p = elem[i].parent;
            s = i;
            while (p != 0) {
                result[i - size].hflen = 1 + result[i - size].hflen;
                p = elem[p].parent;
            }
        }
        for (int i = 0; i < size; ++i)
            total += result[i].data * result[i].hflen;
        cout << total << endl;
    }

    ~hfTree() { delete[]elem; }
};

int main() {
    int n;
    int *q, *k;
    int p;
    cin >> n;
    q = new int[n];
    k = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> p;
        q[i] = k[i] = p;
    }
    hfTree<int> hf(q, k, n);
    hf.get();
}