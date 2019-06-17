#include <iostream>
#include <cstring>
using namespace std;

template <class Type>
class priorityQueue {
private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSpace() {
        Type *tmp=array;
        maxSize*=2;
        array=new Type[maxSize];
        for (int i = 0; i <= currentSize ; ++i)
            array[i]=tmp[i];
        delete []tmp;
    }

    void buildHeap() {
        for(int i=currentSize/2;i>0;i--)
            percolateDown(i);
    }

    void percolateDown(int hole) {
        int child;
        Type tmp=array[hole];

        for(;hole*2<=currentSize;hole=child){
            child=hole*2;
            if(child!=currentSize&&array[child+1]<array[child])
                child++;
            if(array[child]<tmp)array[hole]=array[child];
            else break;
        }
        array[hole]=tmp;
    }

public:
    priorityQueue(int capacity = 100) {
        array = new Type[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    priorityQueue(const Type data[], int size):maxSize(size+10),currentSize(size) {
        array=new Type[maxSize];
        for (int i = 0; i < size; ++i) array[i+1]=data[i];
        buildHeap();

    }

    ~priorityQueue() { delete[]array; }

    bool isEmpty() const { return currentSize == 0; }

    void enQueue(const Type &x) {
        if(currentSize==maxSize-1)doubleSpace();

        int hole=++currentSize;
        for (; hole>1&&x<array[hole/2]; hole/=2)
            array[hole]=array[hole/2];
        array[hole]=x;
    }

    Type deQueue() {
        Type minItem;
        minItem=array[1];
        array[1]=array[currentSize--];
        percolateDown(1);
        return minItem;
    }

    Type getHead() const { return array[1]; }

    Type getmin(){
        return array[1];
    }

    void find(int x){
        int min = 5000000;
        int result = 0;
        for (int i = 1; i <= currentSize; ++i) {
            if(array[i]>x&&array[i]<min) {
                min = array[i];
                result=i;
            }
        }
        cout<<result<<endl;
    }

    void decrease(int i,int v){
        array[i]-=v;
        buildHeap();
    }

};

int main(){
    priorityQueue<int> queue;
    int lines;
    cin>>lines;
    char operation[10];
    for (int j = 0; j < lines; ++j) {
        cin>>operation;
        if (!strcmp(operation,"insert")){
            int v;
            cin>>v;
            queue.enQueue(v);
        }
        else if(!strcmp(operation,"decrease")){
            int i,v;
            cin>>i>>v;
            queue.decrease(i,v);
        }
        else if(!strcmp(operation,"find")){
            int n;
            cin>>n;
            queue.find(n);
        }
    }
}
