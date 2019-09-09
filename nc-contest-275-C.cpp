/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-09 14:40:14
 * @Description: 线段树 区间异或求和
 * @Source: https://ac.nowcoder.com/acm/contest/275/C
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 5;
const ll MOD = 998244353;
const int DIG=21;
int a[MAX];
struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,m
#define rson rc,m+1,r
    int cal[DIG][MAX<<2],lazy[DIG][MAX<<2];
    void pushup(int rt){
        for(int i=0;i<DIG;i++){
            cal[i][rt]=cal[i][lc]+cal[i][rc];
        }
    }
    void pushdown(int rt,int l,int r){
        for(int i=0;i<DIG;i++){
            if(lazy[i][rt]==0) continue;
            int mid=(l+r)>>1;
            lazy[i][lc]^=1;
            lazy[i][rc]^=1;
            cal[i][lc]=mid-l+1-cal[i][lc];
            cal[i][rc]=r-mid-cal[i][rc];
            lazy[i][rt]=0;
        }
    }
 
    void build(int rt,int l,int r){
        if(l==r){
            int v=a[l];
            for(int i=0;i<DIG;i++){
                int x=(v>>i)&1;
                if(x) cal[i][rt]++;
            }
            return;
        }
        int m=(l+r)>>1;
        build(lson);build(rson);
        pushup(rt);
    }
    void insert_XOR(int rt,int l,int r,int L,int R,int v){
        if(L<=l && r<=R){
            for(int i=0;i<DIG;i++){
                int x=(v>>i)&1;
                if(x==0) continue;
                lazy[i][rt]^=1;
                cal[i][rt]=r-l+1-cal[i][rt];
            }
            return;
        }
        int m=(l+r)>>1;
        pushdown(rt,l,r);
        if(L<=m) insert_XOR(lson,L,R,v);
        if(R>m) insert_XOR(rson,L,R,v);
        pushup(rt);
    }
    ll query(int rt,int l,int r,int L,int R){
        ll ans=0;
        if(L<=l && r<=R){
            for(int i=0;i<DIG;i++){
                ll x=1ll<<i;
                ans+=x*(ll)cal[i][rt];
            }
            return ans;
        }
        int m=(l+r)>>1;
        pushdown(rt,l,r);
        if(L<=m) ans+=query(lson,L,R);
        if(R>m) ans+=query(rson,L,R);
        pushup(rt);
        return ans;
    }
}T;
 
int main(){
    //debug;
    int n,Q,op,L,R,v;
    scanf("%d%d",&n,&Q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    T.build(1,1,n);
    for(int i=1;i<=Q;i++){
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d",&L,&R);
            ll ans=T.query(1,1,n,L,R);
            printf("%lld\n",ans);
        } else{
            scanf("%d%d%d",&L,&R,&v);
            T.insert_XOR(1,1,n,L,R,v);
        }
    }
 
    return 0;
}
