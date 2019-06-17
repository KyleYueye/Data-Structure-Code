#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int int_pow(int n,int x){
    int result=1;
    for (int i = 1; i <= x; ++i) {
        result *= n;
    }
    return result;
}

int getlen(int num){
    int result=2;
    while(result-num<=0){
        result*=2;
    }
    return result;
}

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
};

template <class Type>
class BinaryTree {
private:
    struct Node {
        Node *leftChi, *rightSib;
        Type data;

        Node() : leftChi(NULL), rightSib(NULL) {}

        Node(Type item, Node *L = NULL, Node *R = NULL) : data(item), leftChi(L), rightSib(R) {}

        ~Node() {}
    };

    Node *root;
    Node* list;

public:
    BinaryTree() : root(NULL) {}

    BinaryTree(const Type &value) { root = new Node(value); }

    BinaryTree(const Node *p) { root = p; }

    ~BinaryTree(){/*clear();*/}

    bool isEmpty() const { return root == NULL; }

    void clear() {
        if (root != NULL)clear(root);
        root = NULL;
    }

    void preOrder()const{
        if(root!=NULL){
            cout<<"\n";
            preOrder(root);
        }
    }

    void postOrder()const{
        if(root!=NULL){
            cout<<"\npost:";
            postOrder(root);
        }
    }

    void midOrder()const{
        if(root!=NULL){
            cout<<"\n";
            midOrder(root);
        }
    }

    void levelB()const{
        cout<<"\nlevelB:";
        linkQueue<Node *> que;
        Node *P;
        P = root;
        cout<<P->data<<' ';
        if (P->leftChi) que.enQueue(P->leftChi);
        if (P->rightSib) que.enQueue(P->rightSib);

        while(!que.isEmpty()) {
            P = que.deQueue();
            cout<<P->data<<' ';
            if (P->leftChi) que.enQueue(P->leftChi);
            if (P->rightSib) que.enQueue(P->rightSib);
        }
    }

    void levelO()const{
        cout<<"\n";
        linkQueue<Node *> que;
        Node *P,*Q;
        P = root;
        cout<<P->data<<' ';
        if (P->leftChi) que.enQueue(P->leftChi);
        Q = P;
        while (Q->rightSib){
            Q = Q->rightSib;
            if(Q->leftChi)que.enQueue(Q->leftChi);
            cout<<Q->data<<' ';
        }

        while(!que.isEmpty()) {
            P = que.deQueue();
            cout<<P->data<<' ';
            if (P->leftChi) que.enQueue(P->leftChi);
            Q = P;
            while (Q->rightSib){
                Q = Q->rightSib;
                if(Q->leftChi)que.enQueue(Q->leftChi);
                cout<<Q->data<<' ';
            }

        }
    }

    void createTree() {
        int num;
        cin >> num;
        int len = getlen(num);
        list = new Node[num + 1];


        int check[num+1];
        for (int l = 0; l < num+1; ++l)
            check[l]=-1;
        int p, q, v;
        for (int i = 1; i <= num; ++i) {
            cin >> p >>q >> v;
            check[p]=p;check[q]=q;
            list[i].data = v;
            if (p == 0) {
                list[i].leftChi = NULL;
            } else {
                list[i].leftChi = &list[p];
            }
            if (q == 0) {
                list[i].rightSib = NULL;
            } else {
                list[i].rightSib = &list[q];
            }
        }

        for (int c = 0; c < num+1; ++c) {
            if(check[c]==-1){
                root = &list[c];
                break;
            }
        }

        preOrder();
        midOrder();
        levelO();

        root = NULL;
        delete [] list;

    }


private:
    int height(Node *t) const {
        if (t == NULL)return 0;
        else {
            int lt = height(t->leftChi), rt = height(t->rightSib);
            return 1 + ((lt > rt) ? lt : rt);
        }
    }

    void clear(Node *t) {
        if (t->leftChi != NULL)clear(t->leftChi);
        if (t->rightSib != NULL)clear(t->rightSib);
        delete t;
    }

    int size(Node *t) const {
        if (t == NULL)return 0;
        return 1 + size(t->leftChi) + size(t->rightSib);
    }

    void preOrder(Node*t)const{
        if(t!=NULL){
            cout<<t->data<<' ';
            preOrder(t->leftChi);
            preOrder(t->rightSib);
        }
    }

    void postOrder(Node*t)const{
        if(t!=NULL){
            postOrder(t->leftChi);
            postOrder(t->rightSib);
            cout<<t->data<<' ';
        }
    }

    void midOrder(Node*t)const{
        if(t!=NULL){
            midOrder(t->leftChi);
            cout<<t->data<<' ';
            midOrder(t->rightSib);
        }
    }
};




int main(){
    BinaryTree<int> Tree;
    Tree.createTree();
    //前序=原树前序 中序=原树后序
}
