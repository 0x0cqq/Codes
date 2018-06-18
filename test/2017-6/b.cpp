#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin >> T;
    for(int i = 1;i<=T;i++){
        int x , y;
        cin >> x >> y;
        if(x == y)
            cout<<'='<<'\n';
        else if(min(x,y)== 1)
            x==1?cout<<'<'<<'\n':cout<<'>'<< '\n';
        else if(min(x,y)==2){
            if(y==4 || x==4) 
                cout<<'=' << '\n';
            else if(x==2 && y==3) 
                cout<<'<' << '\n';
            else if(x==3 && y==2) 
                cout<<'>' << '\n';
            else
                x < y ? cout<<'>' << '\n' : cout<<'<'<< '\n';
        }
        else
            x < y ? cout<<'>' << '\n' : cout<<'<'<< '\n';
    }
    return 0;
}