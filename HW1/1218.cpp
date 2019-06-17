#include <iostream>
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
            data[i] = tmp[i];
        }
        //delete[] tmp;
    };

public:
    seqList(int initSize = 100) {
        if (initSize <= 0) throw IllegalSize();
        data = new elemType[initSize];
        maxSize = initSize;
        currentLength = 0;
    }

    ~seqList() { /*delete[]data;*/ }

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
        if (i == 0 && currentLength == 1) {
            currentLength = 0;
            return;
        }
        if (i == currentLength - 1) {
//            int*tmp;
//            tmp=new int[maxSize];
//            for (int j = 0; j < currentLength-1; ++j) {
//                tmp[j]=data[j];
//            }
//            data = tmp;
            currentLength--;
            return;
        }
        if (i < 0 || i > currentLength)throw OutOfBound();
        for (int j = i; j < currentLength - 1; ++j)data[j] = data[j + 1];
        --currentLength;

    }

    int search(const elemType &x) const {
        int i;
        for (i = 0; i < currentLength && data[i] != x; ++i);
        if (i == currentLength)return -1; else return i;

    };

    elemType visit(int i) const {
        if (i < 0 || i > currentLength - 1)throw OutOfBound();
        return data[i];
    }

    void traverse() const {
        if (currentLength == 0) {
            cout << endl;
        } else {
            for (int i = 0; i < currentLength; ++i)
                cout << data[i] << ' ';
            cout << endl;
        }
    };

    void sort() {
        int temp;
        int k;

        for (int i = 0; i < currentLength; i++) {
            temp = data[i];
            k = i;
            for (int j = i; j < currentLength; j++) {
                if (temp > data[j]) {
                    temp = data[j];
                    k = j;
                }
            }
            data[k] = data[i];
            data[i] = temp;
        }
    }

    void modify(int *&x, int len, int count) {
        this->data = x;
        maxSize = len;
        currentLength = count;
        //delete [] data;
    }
};

class settest {
private:
    int n;
    int *tmpstore;
    seqList<int> storage;
public:
    void plus(int num) {
        for (int i = 0; i < num; ++i) {
            int in;
            cin >> in;
            if (storage.search(in) == -1 || storage.length() == 0)
                storage.insert(storage.length(), in);
        }
    }

    void minus(int num) {
        for (int i = 0; i < num; ++i) {
            int in;
            cin >> in;
            int index = storage.search(in);
            if (index != -1)
                storage.remove(index);
        }
    }

    void times(int num) {
        int count = 0;
        tmpstore = new int[num];
        for (int i = 0; i < num; ++i) {
            int in;
            cin >> in;
            if (storage.search(in) != -1) {
                tmpstore[count] = in;
                count++;
            }
        }
        this->storage.modify(tmpstore, num, count);
    }

    void operate() {
        int mi;
        char operation;
        cin >> operation;
        cin >> mi;
        switch (operation) {
            case '+':
                plus(mi);
                break;
            case '-':
                minus(mi);
                break;
            case '*':
                times(mi);
                break;
        }
        storage.sort();
        storage.traverse();

    }

    void run() {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            operate();
        }
    }
};

int main(){
    settest settest1;
    settest1.run();
}