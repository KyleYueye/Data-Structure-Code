#include <iostream>
using namespace std;

class Joseph {
private:
    int n;
    int m;
    int k;
public:
    Joseph(int n,int m,int k):n(n),m(m),k(k){};
    void simulate();
};

void Joseph::simulate() {
    int time=0;
    int *a;
    a = new int[n];
    int i = 0,count = 0;
    int num = 0;
    for(i = 1; i <= n; i++) {
        a[i] = i;
    }
    while(count < n-1) {
        for(i = 1; i <= n; i++ ){
            if (a[i]==i){
                num++;
                if(num == m){
                    time++;
                    if(time==k)
                        cout<<i<<' ';
                    count++;
                    a[i] = 0;
                    num = 0;
                }
                if(count == n-1)break;
            }
        }
    }

}

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    Joseph key(n,m,k);
    key.simulate();
}