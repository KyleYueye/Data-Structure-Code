#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char* type;
    type = new char[10];
    int n=0,m=0;
    cin.getline(type,10);
    cin >> n >> m;
    // cout<<n<<" "<<m<<endl;
    if (!strcmp(type,"int")){
        int* line1;
        line1 = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> line1[i];
        }

        int* line2;
        line2 = new int[m];
        for (int j = 0; j < m; ++j) {
            cin >> line2[j];
        }

        int* unite;
        unite = new int[n+m];
        for (int k = 0; k < n; ++k) {
            unite[k] = line1[k];
        }
        for (int l = 0; l < m; ++l) {
            unite[l+n] = line2[l];
        }

        for (int i1 = 0; i1 < n+m; ++i1) {
            cout << unite[i1] << " ";
        }
    }
    else if (!strcmp(type,"char")){
        char* line1;
        line1 = new char[n];
        for (int i = 0; i < n; ++i) {
            cin >> line1[i];
        }

        char* line2;
        line2 = new char[m];
        for (int j = 0; j < m; ++j) {
            cin >> line2[j];
        }

        char* unite;
        unite = new char[n+m];
        for (int k = 0; k < n; ++k) {
            unite[k] = line1[k];
        }
        for (int l = 0; l < m; ++l) {
            unite[l+n] = line2[l];
        }

        for (int i1 = 0; i1 < n+m; ++i1) {
            cout << unite[i1] << " ";
        }
    }
    else if (!strcmp(type,"double")) {
        double *line1;
        line1 = new double[n];
        for (int i = 0; i < n; ++i) {
            cin >> line1[i];
        }

        double *line2;
        line2 = new double[m];
        for (int j = 0; j < m; ++j) {
            cin >> line2[j];
        }

        double *unite;
        unite = new double[n + m];
        for (int k = 0; k < n; ++k) {
            unite[k] = line1[k];
        }
        for (int l = 0; l < m; ++l) {
            unite[l+n] = line2[l];
        }

        for (int i1 = 0; i1 < n+m; ++i1) {
            cout << unite[i1] << " ";
        }
    }

}