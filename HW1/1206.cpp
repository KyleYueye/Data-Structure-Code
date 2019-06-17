#include <iostream>
#include <cstring>
using namespace std;

class Stack{
private:
    char** elem;
    int top_p;
    int max_size;
    void doubleSpace(){
        char**tmp=elem;
        elem = new char*[2*max_size];
        for (int i = 0; i < max_size; ++i) {
            elem[i] = tmp[i];
        }
        max_size*=2;
        delete[]tmp;
    }
public:
    Stack(int initSize=10){
        elem = new char*[initSize];
        max_size = initSize;
        top_p = -1;
    }
    ~Stack(){delete []elem;}
    bool isEmpty()const{return top_p==-1;}
    void push(char*&x){
        if(top_p==max_size-1)doubleSpace();
        elem[++top_p]=x;
    }
    char* pop(){ return elem[top_p--];}
};

int main(){
    int focus;
    char* pascal;
    Stack stack(5000);
    pascal = new char[500];
    while(cin>>pascal){
        if (strcmp(pascal,"begin")==0||strcmp(pascal,"if")==0){
            stack.push(pascal);
            pascal = new char[100];
            continue;
        }

        else if(strcmp(pascal,"end")==0){
            if(stack.isEmpty()){
                cout<<"Error!";
                return 0;
            }
            else{
                if(strcmp(stack.pop(),"begin")!=0){
                    cout<<"Error!";
                    return 0;
                }
                else{
                    delete []pascal;
                    pascal = new char[100];
                    continue;
                }
            }
        }
        else if(strcmp(pascal,"else")==0){
            if(stack.isEmpty()){
                cout<<"Error!";
                return 0;
            }
            else{
                if(strcmp(stack.pop(),"then")!=0){
                    cout<<"Error!";
                    return 0;
                }
                else{
                    delete []pascal;
                    pascal = new char[100];
                    continue;
                }
            }
        }
        else if(strcmp(pascal,"then")==0){
            if(stack.isEmpty()){
                cout<<"Error!";
                return 0;
            }
            else{
                if(strcmp(stack.pop(),"if")!=0){
                    cout<<"Error!";
                    return 0;
                }
                else{
                    stack.push(pascal);
                    pascal = new char[100];
                    continue;
                }
            }
        }
        else{
            delete []pascal;
            pascal = new char[100];
            continue;
        }
    }
    if(!stack.isEmpty()){
        cout<<"Error!";
        //cin>>focus;
        return 0;
    }
    else{
        cout<<"Match!";
        //cin>>focus;
        return 0;
    }
}
