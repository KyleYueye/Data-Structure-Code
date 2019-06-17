#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
    FILE *fp;
    fp=fopen("chaos.txt","w");
    double k=0.001,x=5.0;
    int i;
    for (k = 0.1; k <=2.0 ; k=k+0.001) {
        for(i=0;i<500;i++)
            for(i=1;i<=500;i++){
                x=1-k*x*x;
                fprintf(fp,"%lf %lf\n",k,x);
            }

    }
}