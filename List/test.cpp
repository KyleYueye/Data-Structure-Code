#include<iostream>
#include<cstring>
using namespace std;

class Plane
{
private:
    int bc,ed,sj;
    char* jx;
public:
    void set(char *jx1,int bc1,int ed1,int sj1)
    {
        strcpy(jx,jx1);
        bc=bc1;
        ed=ed1;
        sj=sj1;
    }
    void display()
    {
        cout<<"jx:"<<jx<<endl;
        cout<<"bc:"<<bc<<endl;
        cout<<"edzks:"<<ed<<endl;
        cout<<"sjzks:"<<sj<<endl;
    }
    void xl()
    {
        double e;
        e = double(sj)/ed;
        cout<<"zkxl:"<<e<<endl;
    }
};
int main()
{
    int a,b,c;
    char d[20];
    cout<<"jx,bc,edzks,sjzks:"<<endl;
    cin>>d>>a>>b>>c;
    Plane s;
    s.set(d,a,b,c);
    s.display();
    s.xl();
    system("pause");
}
