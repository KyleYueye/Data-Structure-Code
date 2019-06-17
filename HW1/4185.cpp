#include <iostream>
using namespace std;

class hfTree {
private:
    struct node {
        int weight;
        int parent, left, right;
    };

    node *elem;
    int length;
    int* wt;
    int num;
public:


    hfTree() {
        input();
        int size = num;
        int*w=wt;

        const long int MAX_INT = 5000000000000;
        int min1, min2;
        int x, y;

        length = 2 * size;
        elem = new node[length];
        for (int i = size; i < length; ++i) {
            elem[i].weight = w[i - size];
            elem[i].parent = elem[i].left = elem[i].right = 0;
        }

        for (int i = size - 1; i > 0; --i) {
            min1 = min2 = MAX_INT;
            x = y = 0;
            for (int j = i + 1; j < length; ++j) {
                if (elem[j].parent == 0) {
                    if (elem[j].weight < min1) {
                        min2 = min1;
                        min1 = elem[j].weight;
                        x = y;
                        y = j;
                    } else if (elem[j].weight < min2) {
                        min2 = elem[j].weight;
                        x = j;
                    }
                }
            }
            elem[i].weight = min1 + min2;
            elem[i].left = x;
            elem[i].right = y;
            elem[i].parent = 0;
            elem[x].parent = i;
            elem[y].parent = i;
        }


    }

    unsigned long int getsum() {
        unsigned long int sum=0;
        int size=length/2;
        for (int i = 1; i < length; ++i) {
            if(elem[i].left==0&&elem[i].right==0){
                //cout<<"* "<<getheight(i)<<' '<<elem[i].weight<<endl;
                sum += getheight(i)*elem[i].weight;
            }
        }
        return sum;
    }

    unsigned long int getheight(int i){
        int loop = elem[i].parent;
        unsigned long int height=0;
        while(loop!=0){
            loop = elem[loop].parent;
            height += 1;
        }
        return height;
    }

    void input(){
        cin>>num;
        wt = new int[num];
        for (int i = 0; i < num; ++i) {
            cin>>wt[i];
        }
    }

    ~hfTree() { delete[]elem; }
};


int main(){
    hfTree hfTree1;
    cout<<hfTree1.getsum()<<endl;

}