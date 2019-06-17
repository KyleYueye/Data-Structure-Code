#include <iostream>
using namespace std;


class DisjointSet{
private:
    int size;
    int* parent;
public:
    DisjointSet(int s){
        size = s;
        parent=new int[size+1];
        for (int i = 1; i <= size; ++i) {
            parent[i]=-1;
        }
    }
    ~DisjointSet(){delete []parent;}
    void Union(int root1,int root2){
        if(root1==root2)return;
        if(parent[root1]>parent[root2]){
            parent[root2]+=parent[root1];
            parent[root1] = root2;
        }
        else{
            parent[root1]+=parent[root2];
            parent[root2]=root1;
        }
    }
    int Find(int x){
        if(parent[x]<0)return x;
        return parent[x] = Find(parent[x]);
    }
};


class maze{
public:
    bool check(int n,int row,int col){
        if(row>n||col>n)return false;
        if(col==1||row==col||row==n)return true;
        return false;
    }
    void createPuzzle(int n,int startRow,int startCol,int endRow,int endCol){
        if(!check(n,startRow)||!check(n,endRow,endCol))
    }
};

int main(){
    maze maze1;
    maze1.create();
}



//    void create() {
//        int num1, num2;
//        int A, B;
//        cin >> height >> A >> B;
//        int size = (1 + height) * height / 2;
//        store = new int[2*size];
//        DisjointSet ds(size);
//
//        for (int j = 1; j < 2*size; ++j) {
//            store[j] = -1;
//        }
//        int max, min, floor = 1, pos = 1, P, Q, R,Pmax=0;
//        while (ds.Find(A) != ds.Find(B)) {
//            R = -1;
//            cin >> P >> Q;
//            if(P>Pmax)
//                Pmax = P;
//            for (int n = 1; n <= height; ++n) {
//                max = n * (n + 1) / 2;
//                if (n == 1) {
//                    min = 1;
//                } else
//                    min = n * (n - 1) / 2 + 1;
//                if (P >= min && P <= max)
//                    floor = n;
//                pos = P - min + 1;
//            }
//
//
//            switch (Q) {
//                case 0:
//                    if (pos == 1)
//                        break;
//                    else
//                        R = P - floor;
//                    break;
//                case 1:
//                    if (pos == floor)
//                        break;
//                    else
//                        R = P - floor + 1;
//                    break;
//                case 2:
//                    if(floor==height)
//                        break;
//                    R = P + floor;
//                    break;
//                case 3:
//                    if(floor==height)
//                        break;
//                    R = P + floor + 1;
//                    break;
//            }
//            if(R>Pmax)
//                Pmax = R;
//            if(R==-1)
//                continue;
//            ds.Union(ds.Find(P), ds.Find(R));
//            // cout << '(' << P << ',' << R << "),";
//            store[P] = R;
//        }
//
//        int tmp,len;
//        for (int k = 1; k < 2*size; ++k) {
//            if(store[k]==-1)
//                len = k;
//        }
//
//        cout<<A<<' '<<store[A]<<' ';
//        tmp = store[A];
//
//        for (int i = 1; i < len; ++i) {
//            cout<<store[tmp]<<' ';
//            tmp = store[tmp];
//            if(tmp==Pmax)
//                break;
//        }
//        //cout<<Pmax;
//
//    }