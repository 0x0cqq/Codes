ll sumn[MAXN<<2],addn[MAXN<<2];

inline void init(){
    scanf("%d %d",&n,&q);
    for(M = 1;M<n+2;M<<=1);
    for(int i = 1;i<=n;i++)
        scanf("%lld",&sumn[M+i]);
    for(int i = M-1;i;i--)
        sumn[i] = sumn[i<<1]+sumn[i<<1|1];
}

inline void update(int l,int r,ll d){
    int i=1,L=0,R=0;
    for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
        sumn[l]+=L*d,sumn[r]+=R*d;
        if(~l&1) addn[l^1]+=d,sumn[l^1]+=d*i,L+=i;
        if(r&1) addn[r^1]+=d,sumn[r^1]+=d*i,R+=i;
    }
    sumn[l]+=L*d,sumn[r]+=R*d;
    while(l>>=1) sumn[l]+=(L+R)*d;
}

ll query(int l,int r){
    ll ans = 0;int i=1,L=0,R=0;
    for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
        ans+=addn[l]*L,ans+=addn[r]*R;
        if(~l&1) ans+=sumn[l^1],L+=i;
        if(r&1) ans+=sumn[r^1],R+=i;
    }
    ans+=addn[l]*L,ans+=addn[r]*R;
    while(l>>=1) ans+=addn[l]*(L+R);
    return ans;
}