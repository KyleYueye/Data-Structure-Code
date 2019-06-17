#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <iostream>
using namespace std;

template <class elemType>
class list {
public:
    virtual void clear() = 0;

    virtual int length() const = 0;

    virtual void insert(int i, const elemType &x) = 0;

    virtual void remove(int i) = 0;

    virtual int search(const elemType &x) const = 0;

    virtual elemType visit(int i) const = 0;

    virtual void traverse() const = 0;

    virtual ~list() {};
};

class OutOfBound{};
class IllegalSize{};

template <class elemType>
class seqList: public list<elemType> {
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
        }
        --currentLength;

    }

    int search(const elemType &x) const {
        for (int i = 0; i < currentLength && data[i] != x; ++i){}
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

template <class elemType>
class linkList:public list<elemType> {
private:
    struct node {
        elemType data;
        node *prev, *next;

        node(const elemType &x, node *p = NULL, node *n = NULL) {
            data = x;
            next = n;
            prev = p;
        }

        node() : next(NULL), prev(NULL) {}

        ~node() {};
    };

    node *head, *tail;
    int currentLength;

    node *move(int i) const {
        node *p = head->next;
        if (i < 0 || i > currentLength)throw OutOfBound();
        while (i--)p = p->next;
        return p;
    }

public:
    linkList() {
        head = new node;
        head->next = tail = new node;
        tail->prev = head;
        currentLength = 0;
    };

    ~linkList() {
        clear();
        delete head;
        delete tail;
    }

    void clear() {
        node *p = head->next, *q;
        head->next = tail;
        tail->prev = head;
        while (p != tail) {
            q = p->next;
            delete p;
            p = q;
        }
        currentLength = 0;
    }

    int length() const { return currentLength; }

    void insert(int i, const elemType &x) {
        node *pos, *tmp;
        pos = move(i);
        tmp = new node(x, pos->prev, pos);
        pos->prev->next = tmp;
        pos->prev = tmp;

        ++currentLength;
    }

    void remove(int i) {
        node *pos;
        pos = move(i);
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;

        delete pos;
        --currentLength;
    }

    int search(const elemType &x) const {
        node *p = head->next;
        int i = 0;
        while (p != tail && p->data != x) {
            p = p->next;
            ++i;
        }
        if (p == tail)return -1; else return i;
    }

    elemType visit(int i) const {
        node *p = move(i);

        return p->data;
    }

    void traverse() const {
        node *p = head->next;
        cout << endl << '[';
        while (p != tail->prev) {
            cout << p->data << ',';
            p = p->next;
        }
        cout << p->data << ']' << endl;
    }
};



#endif //LIST_LIST_H




