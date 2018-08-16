#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 210000;

namespace SegTree{
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
struct Line{
    int l,r,s;
    Line operator + (const Line &_l)const{
        //if(l == 0) return *this;
        //if(_l.l == 0) return _l;
        return (Line){l,_l.r,s+_l.s};
    }
    bool operator < (const Line &_l)const{
        return s < _l.s;
    }
};
struct Node{
    Line Lmin,Lmax,Rmin,Rmax,Vmin,Vmax,V;
    int rev;
    Node(int l = 0,int r = 0,int s = 0){
        Lmin = Lmax = Rmin = Rmax = Vmin = Vmax = V = (Line){l,r,s};
        rev = 0;
    }
}T[MAXN<<2];
Node merge(const Node &_l,const Node &_r){
    Node ans;
    ans.Lmin = min(_l.Lmin,_l.V+_r.Lmin);
    ans.Lmax = min(_l.Lmax,_l.V+_r.Lmax);
    ans.Rmax = min(_l.Rmax + _r.V,_r.Rmax);
    ans.Rmin = min(_l.Rmin + _r.V,_r.Rmin);
    ans.Vmin = min(min(_l.Vmin,_r.Vmin),_l.Rmin + _r.Lmin);
    ans.Vmax = min(min(_l.Vmax,_r.Vmax),_l.Rmax + _r.Lmax);
    ans.V = _l.V +_r.V;
    return ans;
}
void push_up(int nown){
    T[nown] = merge(T[lson],T[rson]);
}
void push_down(int nown){
    if(T[nown].rev){

        T[nown].rev = 0;
    }
}
#undef lson
#undef rson
#undef mid
}

int main(){
    return 0;
}