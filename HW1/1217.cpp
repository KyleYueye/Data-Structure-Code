#include <iostream>
using namespace std;

class search{
private:
    int length;
    int times;
    int* storage;
public:
    void input(){
        cin>>length;
        storage = new int[length];
        for (int i = 0; i < length; ++i) {
            cin>>storage[i];
        }
    }
    void find(){
        int each;
        cin>>times;
        for (int i = 0; i < times; ++i) {
            cin>>each;
            get(each);
        }

    }
    void get(int x){
        for (int i = 0; i < length; ++i) {
            if(x==storage[i]) {
                cout<<'Y'<<endl;
                return;
            }
        }
        cout<<'N'<<endl;
    }
    void run(){
        input();
        find();
    }
};

int main(){
    search search1;
    search1.run();
}