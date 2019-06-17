#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

template <class elemtype>
class linkList
{
private:
    struct node
    {
        elemtype data;
        node *next;

        node(const elemtype &x, node *n = NULL)
        {
            data = x;
            next = n;
        }
        node():next(NULL){}
        ~node() {}
    };

    node *head;
    int currentlength;

    node *move(int i) const
    {
        node *p = head;
        while(i-- >=0) p = p->next;
        return p;
    }

public:
    linkList()
    {
        head = new node;
        currentlength =0;
    }
    ~linkList() {clear();  delete head;}

    void clear()
    {
        node *p = head->next, *q;
        head->next = NULL;
        while(p)
        {
            q = p->next;
            delete p;
            p = q;
        }
        currentlength = 0;
    }
    int length() const {return currentlength;}
    void insert(int i, const elemtype &x)
    {
        node *p;
        p = move(i-1);
        p->next = new node(x, p->next);
        currentlength++;
    }
    void remove(int i)
    {
        node *p,*q;
        p = move(i-1);
        q = p->next;
        p->next = q->next;
        delete q;
        currentlength--;
    }
    int search(const elemtype &x) const
    {
        node *p = head->next;

        int i= 0;
        while(p != NULL && p->data != x){p = p->next; ++i;}
        if(!p) return -1;   else return i;

    }
    elemtype visit(int i) const
    {
        return move(i)->data;
    }

    void traverse() const
    {
        node *p = head->next;
        while(p){
            cout<<p->data<<'\t';
            p = p->next;
        }
        cout<<endl;
    }
};
int main()
{
    int n,m,k,i,j=-1,count=0;
    cin>>n>>m>>k;
    linkList<int> Joseph;
    for (i=0;i<n;i++)
        Joseph.insert(i,i+1);
    while (count<k-1)
    {
        for (i=1;i<m;i++)
        {
            j++;
            j=j%Joseph.length();
        }
        Joseph.remove((j+1)%Joseph.length());
        if ((j+1)%(Joseph.length()+1)==0) {j--;}
        count++;
    }
    for (i=1;i<m;i++)
    {
        j++;
        j=j%Joseph.length();
    }
    cout<<Joseph.visit((j+1)%Joseph.length());


    return 0;
}
