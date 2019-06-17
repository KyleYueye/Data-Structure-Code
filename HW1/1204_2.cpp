#include <iostream>
#include <cstring>
using namespace std;

class Linklist{
private:
    struct node{
        char letter;
        node* next;
    }*p;
public:
    Linklist(){p = NULL;};
    ~Linklist(){
        node* q;
        if(p == NULL)
            return;
        while (p != NULL){
            q = p->next;
            delete p;
            p = q;
        }
    };
    void split(Linklist* &y,int* line,int pose){
        node* q=p,*s;
        for (int i = 0; i < pose; ++i) {
            while(q->letter!='\n'&&q!= NULL){
                y[i].append(q->letter);
                q = q->next;
            }
            y[i].append('\n');
            q = q->next;
        }

    }
    void append(char element){
        node *q=p,*s;
        s = new node;
        if(p == NULL){
            s->letter = element;
            s->next = q;
            p = s;
        }
        else{
            while(q->next != NULL){
                q=q->next;
            }
            s->letter = element;
            q->next = s;
            s->next = NULL;
        }
    }
    void add_after(node* headB,int location){
        if(p!= NULL){
            node* q = p;
            node* s = headB;
            int i=1;
            while(q!= NULL&&i<location-1){
                q = q->next;
                ++i;
            }
            if(i<location-1)cout<<"Error!"<<endl;
            else{
                while (s->next!=NULL)
                    s = s->next;
                s->next = q->next;
                q->next = headB;
            }
        }
    }
    void del_after(int location,int step){
        if(p!= NULL){
            node* q = p;
            int i=1;
            while(q!= NULL&&i<location-1){
                q = q->next;
                ++i;
            }
            node* count = q;
            if(i<location-1)cout<<"Error!"<<endl;
            for (int j = 0; j < step; ++j) {
                count = count->next;
            }
            q->next = count->next;
        }
    }
    void print_all(){
        node* q=p;
        while(q!=NULL){
            cout<<q->letter;
            q = q->next;
        }
    }
    int size(){
        int size=0;
        node* q = p;
        while(q != NULL) {
            size++;
            q = q->next;
        }
        return size;
    }
    node* head(){ return p;}
};

void list(Linklist*&x,int n1,int n2){
    if((n2-n1)>=0){
        for (int i = n1-1; i <= n2-1; ++i) {
            x[i].print_all();
        }
    }
    else cout<<"Error!"<<endl;
}

void ins(Linklist*&x,int row,int pos,char* str){
    Linklist temp;
    int l = strlen(str);
    for (int i = 1; i < l; ++i) {
        temp.append(str[i]);
    }
    x[row-1].add_after(temp.head(),pos);

}

void del(Linklist*&x,int row,int pos,int step){
    x[row-1].del_after(pos,step);
}

int main() {
    Linklist origin;
    char ch;
    int count=0;
    int line[100]={0},pose=0;//pose = lines i the text
    while((ch = cin.get()) != '*'){
        origin.append(ch);
        count++;
        if(ch=='\n'){
            line[pose] = count;
            pose++;
        }
    }
    cin.sync();
    Linklist* List;
    List = new Linklist[pose];
    origin.split(List,line,pose);

    char* operation;
    operation = new char[5];
    while(true){
        //cin.sync();
        //cin.get(operation,5,' ');
        cin>>operation;
        if(!strcmp(operation,"quit")) break;
        else if(!strcmp(operation,"list")){
            int n1,n2;
            cin>>n1>>n2;
            if(n1>pose||n2>pose||n1<0||n2<0)cout<<"Error!"<<endl;
            else list(List,n1,n2);
        }
        else if(!strcmp(operation,"ins")){
            int row,pos;
            cin>>row>>pos;
            char* str;
            str = new char[100];
            cin.get(str,100,'\n');
            if(row<0||row>pose||pos>List[row-1].size())cout<<"Error!"<<endl;
            else ins(List,row,pos,str);
        }
        else if(!strcmp(operation,"del")){
            int row,pos,step;
            cin>>row>>pos>>step;
            if(row<0||row>pose||pos>List[row-1].size())cout<<"Error!"<<endl;
            else del(List,row,pos,step);
        }
    }
    for (int k = 0; k < pose; ++k) {
        List[k].print_all();
    }
    return 0;


}