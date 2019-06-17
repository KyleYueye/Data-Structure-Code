#include <iostream>
using namespace std;

int isin(int node,int list[],int count){
    bool flag = false;
    for (int i = 0; i < count; ++i) {
        if(list[i]==node) {
            flag = true;
        }
    }
    return flag;
}

class lca{
private:
    struct Node {
        Node *left, *right, *parent;
        int data;

        Node() : left(NULL), right(NULL),parent(NULL) {}

        Node(int item, Node *L = NULL, Node *R = NULL,Node *P=NULL)
        : data(item), left(L), right(R),parent(P) {}

        ~Node() {}
    };

    Node *root;
    Node* list;

    int N,X,Y;
    int* storex;
    int* storey;
public:
    lca():root(NULL){}
    void input(){
        int l,r;
        cin>>N>>X>>Y;
        list = new Node[N+1];
        for (int k = 1; k <= N; ++k) {
            cin>>l>>r;
            list[k].data=k;
            if(l!=0){
                list[k].left = &list[l];
                list[l].parent = &list[k];
            }
            else {
                list[k].left = NULL;
            }

            if(r!=0){
                list[k].right = &list[r];
                list[r].parent = &list[k];
            }
            else {
                list[k].right = NULL;
            }
        }

        for (int i = 1; i <= N; ++i) {
            if(list[i].parent==NULL)
                root = &list[i];
        }
    }

    void find(){
        Node* p = &list[X];
        storex = new int[N];
        int countx = 0;
        while (p->parent!=NULL){
            storex[countx] = p->parent->data;
            p = p->parent;
            countx++;
        }

        Node* q = &list[Y];
        storey = new int[N];
        int county = 0;
        while (q->parent!=NULL){
            storey[county] = q->parent->data;
            q = q->parent;
            county++;
        }

//        for (int i = 0; i < countx; ++i) {
//            cout<<storex[i]<<',';
//        }
//        cout<<endl;
//        for (int a = 0; a < county; ++a) {
//            cout<<storey[a]<<',';
//        }
//        cout<<endl;

        for (int j = 0; j < county; ++j) {
            if(isin(storey[j],storex,countx)){
                cout<<storey[j]<<endl;
                break;
            }
        }
    }
};

int main(){
    lca lca1;
    lca1.input();
    lca1.find();
}