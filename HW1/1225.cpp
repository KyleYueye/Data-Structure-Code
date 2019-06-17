#include <iostream>

using namespace std;

class distinct{
    int* store;
    int len;

    int divide(int a[], int low, int high) {
        int k = a[low];
        do {
            while (low < high && a[high] >= k){
                --high;
            }

            if (low < high) {
                a[low] = a[high];
                ++low;
            }
            while (low < high && a[low] <= k){
                ++low;
            }

            if (low < high) {
                a[high] = a[low];
                --high;
            }
        } while (low != high);
        a[low] = k;
        return low;
    }
    void quickSort(int a[], int low, int high) {
        int mid;
        if (low >= high)return;
        mid = divide(a, low, high);
        quickSort(a, low, mid - 1);
        quickSort(a, mid + 1, high);
    }
    void quickSort(int a[], int size) {
        quickSort(a, 0, size - 1);
    }

public:
    void input(){
        cin>>len;
        store = new int[len];
        for (int i = 0; i < len; ++i) {
            cin>>store[i];
        }
        quickSort(store,len);
    }

    int count(){
        int tmp=store[0],result=0;
        for (int i = 0; i < len; ++i) {
            if(store[i]!=tmp){
                tmp = store[i];
                result++;
            }
        }
        return result+1;
    }
};


int main(){
    distinct distinct1;
    distinct1.input();
    cout<<distinct1.count();
}