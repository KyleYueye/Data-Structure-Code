#include <iostream>
using namespace std;

template <class T>
void Sort(T a[],int size) {
    int i, j, k;
    T tmp;

    for (i = 0; i < size - 1; ++i) {
        k = i;
        for (j = i + 1; j < size; ++j)
            if (a[j] < a[k])
                k = j;
        tmp = a[i];
        a[i] = a[k];
        a[k] = tmp;
    }
}

void calc(){
    int *M;
    int n;
    int point=0,count=1;
    cin>>n;
    M = new int[2*n+1];
    M[0] = 1;
    while(count<2*n){
        M[count] = 2*M[point]+1;
        M[count+1] = 3*M[point]+1;
        point++;
        count+=2;
        Sort<int>(M,point);
    }
    Sort<int>(M,n);
    for (int i = 0; i < n; ++i) {
        cout<<M[i]<<' ';
    }

}

int main() {
    calc();
}

