#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int n;

string a;

int main(){
    scanf("%d",&n);
    cin >> a;
    for(;;){
        bool f = 1;;
        bool last = 0,nown;
        for(int j = 0;j<a.size();j++){
            nown = (a[j] == 'a' || a[j] == 'e'|| a[j] == 'i'|| a[j] == 'o'|| a[j] == 'u'||a[j] == 'y'); 
            if(nown && last){
                a = a.substr(0,j)+a.substr(j+1,a.size());
                f = 0;
                break;
            }
            last = nown;
        }
        if(f)
            break;
    }
    cout << a << endl;
    return 0;
}