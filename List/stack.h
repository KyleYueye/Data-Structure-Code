#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <iostream>
using namespace std;

template <class elemType>
class stack {
public:
    virtual bool isEmpty() const = 0;

    virtual void push(const elemType &x) = 0;

    virtual elemType pop() = 0;

    virtual elemType top() const = 0;

    virtual ~stack() {};
};


template <class elemType>
class seqStack:public stack<elemType> {
private:
    elemType *elem;
    int top_p;
    int maxSize;

    void doubleSpace() {
        elemType *tmp = elem;
        elem = new elemType[2 * maxSize];
        for (int i = 0; i < maxSize; ++i)
            elem[i] = tmp[i];
        maxSize *= 2;
        delete[] tmp;
    }

public:
    seqStack(int initSize = 10) {
        elem = new elemType[initSize];
        maxSize = initSize;
        top_p = -1;
    }

    ~seqStack() { delete[] elem; }

    bool isEmpty() const { return top_p == -1; }

    void push(const elemType &x) {
        if (top_p == maxSize - 1)doubleSpace();
        elem[++top_p] = x;
    }

    elemType pop() { return elem[top_p--]; }

    elemType top() const { return elem[top_p]; }
};


template <class elemType>
class linkStack:public stack<elemType> {
private:
    struct node {
        elemType data;
        node *next;

        node(const elemType &x, node *N = NULL) {
            data = x;
            next = N;
        }

        node() : next(NULL) {}

        ~node() {}
    };

    node *elem;

public:
    linkStack() { elem = NULL; }

    ~linkStack() {
        node *tmp;
        while (elem != NULL) {
            tmp = elem;
            elem = elem->next;
            delete tmp;
        }
    }

    bool isEmpty() const { return elem == NULL; }

    void push(const elemType &x) {
        node *tmp = new node(x, elem);
        elem = tmp;
    }

    elemType pop() {
        node *tmp = elem;
        elemType x = tmp->data;
        elem = elem->next;
        delete tmp;
        return x;
    }

    elemType top() const { return elem->data; }
};


#endif //LIST_STACK_H