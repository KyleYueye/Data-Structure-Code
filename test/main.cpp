#include <iostream>
#include <cstring>
using namespace std;

class OutOfBound{};
class IllegalSize{};

template <class elemType>
class seqList {
private:
    elemType *data;
    int currentLength;
    int maxSize;

    void doubleSpace() {
        elemType *tmp = data;
        maxSize *= 2;
        data = new elemType[maxSize];
        for (int i = 0; i < currentLength; ++i) {
            delete[] tmp;
        }
    };

public:
    seqList(int initSize = 10) {
        if (initSize <= 0) throw IllegalSize();
        data = new elemType[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~seqList() { delete[]data; }

    void clear() { currentLength = 0; }

    int length() const { return currentLength; }

    void insert(int i, const elemType &x) {
        if (i < 0 || i > currentLength)throw OutOfBound();
        if (currentLength == maxSize)doubleSpace();
        for (int j = currentLength; j > i; --j) {
            data[j] = data[j - 1];
        }
        data[i] = x;
        ++currentLength;
    };

    void remove(int i) {
        if (i < 0 || i > currentLength)throw OutOfBound();
        for (int j = i; j < currentLength - 1; ++j) {
            data[j] = data[j + 1];
            --currentLength;
        }
    }

    int search(const elemType &x) const {
        int i;
        for ( i = 0; i < currentLength && data[i] != x; ++i) ;
        if (i == currentLength)return -1; else return i;

    };

    elemType visit(int i) const {
        if (i < 0 || i > currentLength - 1)throw OutOfBound();
        return data[i];
    }

    void traverse() const {
        cout << endl << '[';
        for (int i = 0; i < currentLength - 1; ++i) cout << data[i] << ',';
        cout << data[currentLength - 1] << ']' << endl;
    };
};


int main() {
    seqList<int> seqList1;
    seqList1.insert(0,1);
    seqList1.insert(0,2);
    seqList1.traverse();
    cout<<seqList1.search(2)<<' ';
    cout<<seqList1.search(1);
}