#include <iostream>
#include <cstring>
using namespace std;

class OutOfBound{};

template <class elemType>
class linkList {
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


template <class Type>
class BinarySearchTree{
private:
    struct BinaryNode{
        Type data;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Type&thedata,BinaryNode*lt,BinaryNode*rt)
        :data(thedata),left(lt),right(rt){}
    };


    linkList<Type> mid;

    BinaryNode* root;

    void midOrder(BinaryNode*t){
        if(t!=NULL){
            midOrder(t->left);
            mid.insert(mid.length(),t->data);
            //cout<<t->data<<' ';
            midOrder(t->right);
        }
    }
    void insert(const Type&x,BinaryNode*&t){
        if(t==NULL)
            t = new BinaryNode(x,NULL,NULL);
        else if(x<=t->data)
            insert(x,t->left);
        else if(t->data<x)
            insert(x,t->right);
    }
    void remove(const Type&x,BinaryNode*&t){
        if(t==NULL)return;
        if(x<t->data) remove(x,t->left);
        else if(t->data<x) remove(x,t->right);
        else if(t->left!=NULL&&t->right!=NULL){
            BinaryNode*tmp=t->right;
            while(tmp->left!=NULL)tmp=tmp->left;
            t->data=tmp->data;
            remove(t->data,t->right);
        }
        else{
            BinaryNode* oldNode=t;
            t=(t->left!=NULL)?t->left:t->right;
            delete oldNode;
        }

    }

    bool find(const Type&x,BinaryNode*t)const{
        if(t==NULL)
            return false;
        else if(x<t->data)
            return find(x,t->left);
        else if(t->data<x)
            return find(x,t->right);
        else return true;
    }

    void makeEmpty(BinaryNode*&t){
        if (t == NULL) return;
        if (t->left)
            makeEmpty(t->left);
        if (t->right)
            makeEmpty(t->right);
        delete t;
        t = NULL;

    }

public:
    BinarySearchTree(BinaryNode*t=NULL){root=t;}
    ~BinarySearchTree(){
        makeEmpty(root);
    }
    void midOrder(int x){
        if(root!=NULL){
            mid.clear();
            midOrder(root);
            if(mid.length()>x)
                cout<<mid.visit(x)<<endl;
            else cout<<'N'<<endl;
        }

    }
    bool find(const Type&x)const {
        return find(x,root);
    }
    void insert(const Type&x){
        insert(x,root);
    }
    void remove(const Type&x){
        remove(x,root);
    }

    void operate(){
        int all,x,y,max=-1,min=99999999;
        char operation[30];
        cin>>all;
        for (int i = 0; i < all; ++i) {
            cin>>operation;
            if(!strcmp(operation,"insert")){
                cin>>x;
                if(x>=max)max=x;
                if(x<=min)min=x;
                insert(x);
            }
            else if(!strcmp(operation,"find")){
                cin>>x;
                if(find(x))cout<<'Y'<<endl;
                else cout<<'N'<<endl;
            }
            else if(!strcmp(operation,"delete")){
                cin>>x;
                remove(x);
            }
            else if(!strcmp(operation,"delete_less_than")){
                cin>>x;
                for (int j = x-1; j >=min ; --j) {
                    remove(j);
                }
            }
            else if(!strcmp(operation,"delete_greater_than")){
                cin>>x;
                for (int j = x+1; j <= max ; ++j) {
                    remove(j);
                }
            }
            else if(!strcmp(operation,"delete_interval")){
                cin>>x>>y;
                for (int j = x+1; j < y ; ++j) {
                    remove(j);
                }
            }
            else if(!strcmp(operation,"find_ith")){
                cin>>x;
                midOrder(x-1);
            }
        }
    }

};



int main(){
    BinarySearchTree<int> tree;
    tree.operate();



}
