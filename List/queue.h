#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <iostream>
using namespace std;

template <class elemType>
class queue {
public:
    virtual bool isEmpty() = 0;

    virtual void enQueue(const elemType &x) = 0;

    virtual elemType deQueue() = 0;

    virtual elemType getHead() = 0;

    virtual ~queue() {}
};





template <class elemType>
class seqQueue:public queue<elemType> {
private:
    elemType *elem;
    int maxSize;
    int head,rear;

    void doubleSpace() {
        elemType *tmp = elem;
        elem = new elemType[2 * maxSize];
        for (int i = 1; i < maxSize; i++)
            elem[i] = tmp[(i + head) % maxSize];
        head = 0;
        rear = maxSize - 1;
        maxSize *= 2;
        delete[]tmp;
    }

public:
    seqQueue(int initSize = 10) {
        elem = new elemType[initSize];
        maxSize = initSize;
        head = rear = 0;
    }

    ~seqQueue() {
        delete[]elem;
    }

    bool isEmpty() {
        return rear == head;
    }

    void enQueue(const elemType &x) {
        if ((rear + 1) % maxSize == head)
            doubleSpace();
        rear = (rear + 1) % maxSize;
        elem[rear] = x;
    }

    elemType deQueue() {
        head = (head + 1) % maxSize;
        return elem[head];
    }

    elemType getHead() {
        return elem[(head + 1) % maxSize];
    }
};


template <class elemType>
class linkQueue:public queue<elemType> {
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

    node *front, *rear;

public:
    linkQueue() { front = rear = 0; }

    ~linkQueue() {
        node *tmp;
        while (front != NULL) {
            tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    bool isEmpty() { return front == NULL; }

    void enQueue(const elemType &x) {
        if (rear == NULL)
            front = rear = new node(x);
        else {
            rear->next = new node(x);
            rear = rear->next;
        }
    }

    elemType deQueue() {
        node *tmp = front;
        elemType value = front->data;
        front = front->next;
        if (front == NULL)rear = NULL;
        delete tmp;
        return value;
    }

    elemType getHead() { return front->data; }
};


#endif //LIST_QUEUE_H