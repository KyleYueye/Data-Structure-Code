#include <iostream>
#include <cstring>
using namespace std;

class sss {
private:
    int *store;
    int len;
    int times;
    int select;

    //堆排序
    void percolateDown(int a[], int hole, int size) {
        int child;
        int tmp = a[hole];

        for (; hole * 2 + 1 < size; hole = child) {
            times++;
            child = hole * 2 + 1;
            if (child != size - 1 && a[child + 1] > a[child]){
                child++;
                //times++;
            }
            if (a[child] > tmp) {
                //times++;
                a[hole] = a[child];
            } else break;
        }
        a[hole] = tmp;
        //times++;
    }

    void heapSort(int a[], int size) {
        int i;
        int tmp;

        for (i = size / 2 - 1; i >= 0; i--){
            percolateDown(a, i, size);
        }


        for (i = size - 1; i > 0; --i) {
            tmp = a[0];
            a[0] = a[i];
            a[i] = tmp;
            percolateDown(a, 0, i);
        }
    }

//快速排序

    int divide(int a[], int low, int high) {
        int k = a[low];
        do {
            while (low < high && a[high] >= k){
                --high;
                times++;
            }

            if (low < high) {
                a[low] = a[high];
                ++low;
                times++;
            }
            while (low < high && a[low] <= k){
                ++low;
                times++;
            }

            if (low < high) {
                a[high] = a[low];
                --high;
                times++;
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

//归并排序

    void merge(int a[], int left, int mid, int right) {
        int *tmp = new int[right - left + 1];
        int i = left, j = mid, k = 0;

        while (i < mid && j <= right){

            if (a[i] < a[j]){
                tmp[k++] = a[i++];
                times++;
            }
            else{
                tmp[k++] = a[j++];
            }

        }
        while (i < mid)
            tmp[k++] = a[i++];
        while (j <= right)
            tmp[k++] = a[j++];

        for (i = 0, k = left; k <= right;)
            a[k++] = tmp[i++];
        delete[]tmp;
    }

    void mergeSort(int a[], int left, int right) {
        int mid = (left + right) / 2;

        if (left == right)return;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid + 1, right);
    }

    void mergeSort(int a[], int size) {
        mergeSort(a, 0, size - 1);
    }

public:
    void input() {
        cin >> len >> select;
        times = 0;
        store = new int[len];
        for (int i = 0; i < len; ++i) {
            cin >> store[i];
        }
        switch (select) {
            case 1:
                heapSort(store, len);
                break;
            case 2:
                mergeSort(store, len);
                break;
            case 3:
                quickSort(store, len);
                break;
        }
        cout << times << endl;
    }


};


int main(){
    sss s;
    s.input();
}

