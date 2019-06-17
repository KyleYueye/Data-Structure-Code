#include <iostream>
#include <cstring>
#define MAX 127
using namespace std;


int index(const char* str,char x) {
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == x)return i;
        else continue;
    }
}


bool get(char *pre, char *ind, char *Seq, int n, int R){
    int i, root;
    if(n <= 0)
        return true;
    root = index(ind,pre[0]);
    if(root >= n)
        return false;
    Seq[R] = pre[0];
    for(i = 0; i < R; i++)
        if(Seq[i] == 0) Seq[i] = '0';
    bool b1 = get(pre+1,ind,Seq,root,2*R+1);
    bool b2 = get(pre+1+root,ind+root+1,Seq,n-root-1,2*R+2);
    return b1 && b2;
}

int main(){
    char pre[26], ind[26], Seq[MAX],i;
    bool valid;
    cin>>pre>>ind;
    int n = strlen(pre);
    for(i = 0; i < MAX; i++)
        Seq[i] = 0;
    valid = get(pre,ind,Seq,n,0);
    if(valid) {
        for(i = 0; Seq[i]; i++)
            if(Seq[i]=='0')
                cout<<"NULL"<<' ';
            else cout<<Seq[i]<<' ';
    }
    else cout<<endl;
}
