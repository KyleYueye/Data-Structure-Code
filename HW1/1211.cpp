#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

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
        Node *left, *right;
        Type data;

        Node() : left(NULL), right(NULL) {}

        Node(Type item, Node *L = NULL, Node *R = NULL) : data(item), left(L), right(R) {}

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

    void createTree() {
        int num;
        cin >> num;
        int len = getlen(num);
        list = new Node[num + 1];
        for (int j = 1; j <= num; ++j) {
            list[j].data = j ;
        }

        int check[num+1];
        for (int l = 0; l < num+1; ++l)
            check[l]=-1;
        int p, q;
        for (int i = 1; i <= num; ++i) {
            cin >> p >> q;
            check[p]=p;check[q]=q;
            if (p == 0) {
                list[i].left = NULL;
            } else {
                list[i].left = &list[p];
            }
            if (q == 0) {
                list[i].right = NULL;
            } else {
                list[i].right = &list[q];
            }
        }

        for (int c = 0; c < num+1; ++c) {
            if(check[c]==-1){
                root = &list[c];
                break;
            }
        }

        linkQueue<Node *> que;
        Node *P;
        P = root;
        if (P->left) que.enQueue(P->left);
        else {
            if(P->data!=-1){
                Node *null;
                null = new Node(-1);
                que.enQueue(null);
            }
        }
        if (P->right) que.enQueue(P->right);
        else {
            if(P->data!=-1){
                Node *null;
                null = new Node(-1);
                que.enQueue(null);
            }
        }

        bool hasnull = false;
        bool follow = false;
        while(!que.isEmpty()) {
            P = que.deQueue();
            if(P->data==-1) hasnull = true;
            if(hasnull)
                if(P->data!=-1){
                    follow = true;
                    break;
                }

            if (P->left) que.enQueue(P->left);
            else {
                if(P->data!=-1){
                    Node *null;
                    null = new Node(-1);
                    que.enQueue(null);
                }
            }
            if (P->right) que.enQueue(P->right);
            else {
                if(P->data!=-1){
                    Node *null;
                    null = new Node(-1);
                    que.enQueue(null);
                }
            }
        }


        if(!follow)
            cout<<'Y';
        else cout<<'N';
        root = NULL;
        delete [] list;

    }


private:
    int height(Node *t) const {
        if (t == NULL)return 0;
        else {
            int lt = height(t->left), rt = height(t->right);
            return 1 + ((lt > rt) ? lt : rt);
        }
    }

    void clear(Node *t) {
        if (t->left != NULL)clear(t->left);
        if (t->right != NULL)clear(t->right);
        delete t;
    }

    int size(Node *t) const {
        if (t == NULL)return 0;
        return 1 + size(t->left) + size(t->right);
    }


};




int main(){
    BinaryTree<int> Tree;
    Tree.createTree();
    //4 4 0 0 0 1 0 2 0
}
