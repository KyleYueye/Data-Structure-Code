#ifndef LIST_SORT_H
#define LIST_SORT_H

#include <iostream>
#include <cstring>
using namespace std;

//插入排序
template <class T>
void simpleInsertSort(T a[],int size) {
    int k;
    T tmp;

    for (int j = 1; j < size; ++j) {
        tmp = a[j];
        for (k = j - 1; tmp < a[k] && k >= 0; --k)
            a[k + 1] = a[k];
        a[k + 1] = tmp;
    }
}

//希尔排序
template <class T>
void shellSort(T a[],int size) {
    int step, i, j;
    T tmp;

    for (step = size / 2; step > 0; step /= 2) {
        for (i = step; i < size; ++i) {
            tmp = a[i];
            for (j = i - step; j >= 0 && a[j] > tmp; j -= step)
                a[j+step]=a[j];
            a[j+step]=tmp;
        }
    }
}

//选择排序
template <class T>
void simpleSelectSort(T a[],int size) {
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

//堆排序
template <class T>
void percolateDown(T a[],int hole,int size){
    int child;
    T tmp=a[hole];

    for (;hole*2+1<size;hole=child) {
        child=hole*2+1;
        if(child!=size-1&&a[child+1]<a[child])
            child++;
        if(a[child]<tmp)
            a[hole]=a[child];
        else break;
    }
    a[hole]=tmp;
}

template <class T>
void heapSort(T a[],int size){
    int i;
    T tmp;

    for (i = size/2-1; i>=0 ; i--)
        percolateDown<T>(a,i,size);

    for (i = size-1; i>0 ; --i) {
        tmp=a[0];a[0]=a[i];a[i]=tmp;
        percolateDown<T>(a,0,i);
    }
}


//冒泡排序
template <class T>
void bubbleSort(T a[],int size) {
    int i, j;
    T tmp;
    bool flag;

    for (i = 1; i < size; ++i) {
        flag = false;
        for (j = 0; j < size - i; ++j) {
            if (a[j + 1] < a[j]) {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                flag = true;
            }
        }
        if (!flag)
            break;
    }
}

//快速排序
template <class T>
int divide(T a[],int low,int high) {
    T k = a[low];
    do {
        while (low < high && a[high] >= k)--high;
        if (low < high) {
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low] <= k)++low;
        if (low < high) {
            a[high] = a[low];
            --high;
        }
    } while (low != high);
    a[low] = k;
    return low;
}

template <class T>
void quickSort(T a[],int low,int high){
    int mid;
    if(low>=high)return;
    mid=divide<T>(a,low,high);
    quickSort<T>(a,low,mid-1);
    quickSort<T>(a,mid+1,high);
}

template <class T>
void quickSort(T a[],int size){
    quickSort<T>(a,0,size-1);
}

//归并排序
template <class T>
void merge(T a[],int left,int mid,int right) {
    T *tmp = new T[right - left + 1];
    int i = left, j = mid, k = 0;

    while (i < mid && j <= right)
        if (a[i] < a[j])
            tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    while (i < mid) tmp[k++] = a[i++];
    while (j <= right)tmp[k++] = a[j++];

    for (i = 0, k = left; k <= right;) a[k++] = tmp[i++];
    delete[]tmp;
}

template <class T>
void mergeSort(T a[],int left,int right){
    int mid =(left+right)/2;

    if(left==right)return;
    mergeSort<T>(a,left,mid);
    mergeSort<T>(a,mid+1,right);
    merge<T>(a,left,mid+1,right);
}

template <class T>
void mergeSort(T a[],int size){
    mergeSort<T>(a,0,size-1);
}



#endif //LIST_SORT_H
