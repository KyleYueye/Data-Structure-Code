#include <iostream>
#include <cstring>
using namespace std;

class Linklist {
private:
    struct node {
        char letter;
        node *next;
        node(char c=NULL,node* n=NULL){letter=c;next=n;}
    } *head;
public:
    Linklist() { head = NULL; };
    Linklist(char *str) {
        head = NULL;
        int l = strlen(str);
        for (int i = 1; i < l; ++i) {
            this->append(str[i]);
        }
    }
    ~Linklist() {
        node *q;
        if (head == NULL)
            return;
        while (head != NULL) {
            q = head->next;
            delete head;
            head = q;
        }
    };
    void split(Linklist *&y, int *line, int pose) {
        node *q = head, *s;
        for (int i = 0; i < pose; ++i) {
            while (q->letter != '\n' && q->next != NULL) {
                y[i].append(q->letter);
                q = q->next;
            }
            y[i].append('\n');
            q = q->next;
        }

    }
    void append(char element) {
        node *q = head, *s;
        s = new node;
        if (head == NULL) {
            s->letter = element;
            s->next = q;
            head = s;
        } else {
            while (q->next != NULL) {
                q = q->next;
            }
            s->letter = element;
            q->next = s;
            s->next = NULL;
        }
    }
    void add_element_after(char c,int location) {
        node* q=head;
        if(head!=NULL){
            node *q=head,*s;
            s = new node;
            int i=1;
            while(q!=NULL&&i<location-1){
                q = q->next;
                ++i;
            }
            s->letter = c;
            s->next = q->next;
            q->next=s;
        }
        else cout<<"Error!"<<endl;
    }




    void del_after(int location,int step) {
        if(head!=NULL){
            node *q = head;
            if(location==1){
                for (int m = 0; m < step; ++m) {
                    head = head->next;
                }
            } else{
                int i = 1;
                while (q != NULL && i < location - 1) {
                    q = q->next;
                    ++i;
                }
                node *count = q;
                for (int j = 0; j < step; ++j) {
                    count = count->next;
                }
                q->next = count->next;
            }
        }
        else cout<<"Error!"<<endl;
    }
    void print_all(){
        node* q=head;
        while(q!=NULL&&((q->letter>=32&&q->letter<=126)||q->letter=='\n')){
            cout<<q->letter;
            q = q->next;
        }
    }
    int size(){
        int size=0;
        node* q = head;
        while(q != NULL) {
            size++;
            q = q->next;
        }
        return size;
    }
};

void list(Linklist*&x,int n1,int n2){
    for (int i = n1-1; i <= n2-1; ++i) {
        x[i].print_all();
    }
}

void ins(Linklist*&x,int row,int pos,char* str,int*line){
    for (int i = 1; i < strlen(str); ++i) {
        x[row-1].add_element_after(str[i],pos);
        pos++;
    }
    line[row-1]+=strlen(str);
}

void del(Linklist*&x,int row,int pos,int step,int*line){
    x[row-1].del_after(pos,step);
    line[row-1]-=step;

}

int main(){
    Linklist origin;
    //char ch;
    int count=0;
    int line[100]={0},pose=0;//pose = lines in the text
//    while((ch = cin.get()) != '*'){
//        origin.append(ch);
//        count++;
//        if(ch=='\n'){
//            line[pose] = count;
//            pose++;
//        }
//    }
    char* eachline;
    eachline = new char[2000];
    while(true){
        cin.getline(eachline,2000);
        if(eachline[0]=='*'&&eachline[1]=='*'&&eachline[2]=='*'&&eachline[3]=='*'
        &&eachline[4]=='*'&&eachline[5]=='*'&&eachline[6]=='\0'){break;}
        else{
            for (int i = 0; i < strlen(eachline); ++i) {
                origin.append(eachline[i]);
                count++;
            }
            origin.append('\n');
            line[pose]=count;
            pose++;
        }
    }

    //cin.sync();
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
            if(n1>pose||n2>pose||n1<0||n2<0||n2<n1)cout<<"Error!"<<endl;
            else list(List,n1,n2);
        }
        else if(!strcmp(operation,"ins")){
            int row,pos;
            char* str;
            str = new char[500];
            cin>>row>>pos;
            cin.get(str,500);
            if(row<0||row>pose||pos>List[row-1].size())cout<<"Error!"<<endl;
            else ins(List,row,pos,str,line);
        }
        else if(!strcmp(operation,"del")){
            int row,pos,step;
            cin>>row>>pos>>step;
            if(row<0||row>pose||pos+step>List[row-1].size())cout<<"Error!"<<endl;
            else del(List,row,pos,step,line);
        }
    }
    for (int k = 0; k < pose; ++k) {
        List[k].print_all();
    }
    return 0;
}
