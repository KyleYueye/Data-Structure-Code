#ifndef LIST_HASH_H
#define LIST_HASH_H

#include <iostream>
using namespace std;

template <class Type>
class hashTable {
public:
    virtual bool find(const Type &x) const = 0;

    virtual bool insert(const Type &x) = 0;

    virtual bool remove(const Type &x) = 0;

protected:
    int (*key)(const Type &x);

    static int defaultKey(const int &k) { return k; }
};

template <class Type>
class closeHashTable:public hashTable<Type> {
private:
    struct node {
        Type data;
        int state;

        node() { state = 0; }
    };

    node *array;
    int size;

    int (*key)(const Type &x);

    static int defaultKey(const int &k) { return k; }

public:
    closeHashTable(int length = 101, int(*f)(const Type &x) = defaultKey) {
        size = length;
        array = new node[size];
        key = f;
    }

    ~closeHashTable() { delete[]array; }

    bool find(const Type &x) const {
        int initPos, pos;

        initPos = pos = key(x) % size;
        do {
            if (array[pos].state == 0)return false;
            if (array[pos].state == 1 && array[pos].data == x)return true;
            pos = (pos + 1) % size;
        } while (pos != initPos);

        return false;
    }

    bool insert(const Type &x) {
        int initPos, pos;

        initPos = pos = key(x) % size;
        do {
            if (array[pos].state != 1) {
                array[pos].data = x;
                array[pos].state = 1;
                return true;
            }
            if (array[pos].state == 1 && array[pos].data == x)
                return true;
            pos = (pos + 1) % size;
        } while (pos != initPos);

        return false;
    }

    bool remove(const Type &x) {
        int initPos, pos;

        initPos = pos = key(x) % size;
        do {
            if (array[pos].state == 0)
                return false;
            if (array[pos].state == 1 && array[pos].data == x) {
                array[pos].state = 2;
                return true;
            }
            pos = (pos + 1) % size;
        } while (pos != initPos);

        return false;
    }

    void rehash() {
        node *tmp = array;

        array = new node[size];
        for (int i = 0; i < size; ++i) {
            if (tmp[i].state == 1)
                insert(tmp[i].data);
        }
        delete[]tmp;
    }
};

template <class Type>
class openHashTable:public hashTable<Type> {
private:
    struct node {
        Type data;
        struct node *next;

        node(const Type &d) {
            data = d;
            next = NULL;
        }

        node() { next = NULL; }
    };

    node **array;
    int size;

    int (*key)(const Type &x);

    static int defaultKey(const int &k) { return k; }

public:
    openHashTable(int length = 101, int(*f)(const Type &x)) {
        size = length;
        array = new node *[size];
        key = f;
        for (int i = 0; i < size; ++i) {
            array[i] = new node;
        }
    }

    ~openHashTable() {
        node *p, *q;
        for (int i = 0; i < size; ++i) {
            p = array[i];
            do {
                q = p->next;
                delete p;
                p = q;
            }
            while (p != NULL);
        }
        delete[]array;
    }

    bool find(const Type &x) const {
        int pos;
        node *p;

        pos = key(x) % size;
        p = array[pos];
        while (p->next != NULL && !(p->next->data == x))
            p = p->next;
        return p->next != NULL;
    }

    bool insert(const Type &x) {
        int pos;
        node *p;

        pos = key(x) % size;
        p = array[pos]->next;
        while (p != NULL && !(p->data == x))
            p = p->next;
        if (p == NULL) {
            p = new node(x);
            p->next = array[pos]->next;
            array[pos]->next = p;
            return true;
        }
        return false;
    }

    bool remove(const Type &x) {
        int pos;
        node *p, *q;

        pos = key(x) % size;
        p = array[pos];
        while (p->next != NULL && !(p->next->data == x))
            p = p->next;
        if (p->next == NULL)
            return false;
        else {
            q = p->next;
            p->next = q->next;
            delete q;
            return true;
        }
    }
};

#endif //LIST_HASH_H
