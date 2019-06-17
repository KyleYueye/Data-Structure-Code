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

    int average(int n){
        int sum = 0,avg=0;
        node* p=front;
        for (int i = 0; i < n; ++i) {
            sum += p->data;
            p = p->next;
        }
        avg = sum/n;
        return avg;
    }
};







int main(){
    linkQueue<int> queue;

    int n,m,x;
    int *store;
    store = new int[m];
    cin>>n>>m;
//    for (int i = 0; i < m; ++i) {
//        cin>>x;
//        store[i] = x;
//    }
//
//    int num_enqueue=0;
//    for (int j = 0; j < m; ++j) {
//        queue.enQueue(store[j]);
//        num_enqueue++;
//
//        if (num_enqueue>n){
//            queue.deQueue();
//        }
//
//        if(num_enqueue<n){
//            cout<<queue.average(num_enqueue)<<endl;
//        } else{
//            cout<<queue.average(n)<<endl;
//        }
//    }
//    delete []store;
    int num_enqueue=0;
    for (int j = 0; j < m; ++j) {
        cin>>x;
        queue.enQueue(x);
        num_enqueue++;

        if (num_enqueue>n){
            queue.deQueue();
        }

        if(num_enqueue<n){
            cout<<queue.average(num_enqueue)<<endl;
        } else{
            cout<<queue.average(n)<<endl;
        }
    }
    delete []store;
}
