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
    
    int joseph(int num,int out,int k){
        int count=0;
        node*p = head->next;
        tail->next = head;
        while(count!=k){

            p = p->next;
        }
    }
};


int Joseph(int num,int out,int k){
    linkList<int> circle;
    for (int i = 0; i < num; ++i) {
        circle.insert(i,i+1);
    }
    circle.joseph();
}


int main(){
    Joseph(4,2,1);
}