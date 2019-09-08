/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-08 11:01:52
 * @Description:
 * @Source: 银川网络赛重赛A
 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 5;
const ll MOD = 998244353;
const int DIG=26;
int a[MAX];
struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,m
#define rson rc,m+1,r
	int cal[DIG][MAX<<2],lazy[MAX<<2],tag[DIG][MAX<<2];
	void pushup(int rt){
		for(int i=0;i<DIG;i++){
			cal[i][rt]=cal[i][lc]+cal[i][rc];
		}
	}
	void pushdown(int rt,int l,int r,int op){
		int w=r-l+1;
		if(lazy[rt]){
			for(int i=0;i<DIG;i++){
				if(op==2){
					tag[i][lc]^=tag[i][rt];
					tag[i][rc]^=tag[i][rt];
					if(tag[i][lc]==1) cal[i][lc]=w-cal[i][lc];
					if(tag[i][rc]==1) cal[i][rc]=w-cal[i][rc];
				} else if(op==3){
					tag[i][lc]|=tag[i][rt];
					tag[i][rc]|=tag[i][rt];
					if(tag[i][lc]==1) cal[i][lc]=w;
					if(tag[i][rc]==1) cal[i][rc]=w;
				} else{
					tag[i][lc]&=tag[i][rt];
					tag[i][rc]&=tag[i][rt];
					if(tag[i][lc]==0) cal[i][lc]=0;
					if(tag[i][rc]==0) cal[i][rc]=0;
				}
			}
			lazy[lc]=lazy[rc]=lazy[rt];
			lazy[rt]=1;
		}
	}

	void build(int rt,int l,int r){
		if(l==r){
			int v=a[l];
			for(int i=0;i<DIG;i++){
				int x=v>>i;
				if(x&1) cal[i][rt]++;
			}
			return;
		}
		int m=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void insert_AND(int rt,int l,int r,int L,int R,int v){
		if(L<=l && r<=R){
			for(int i=0;i<DIG;i++){
				int x=v>>i;
				x&=1;
				tag[i][rt]&=x;
				if(tag[i][rt]==0) cal[i][rt]=0;
			}
			lazy[rt]=4;
			return;
		}
		int m=(l+r)>>1;
		pushdown(rt,l,r,lazy[rt]);
		if(L<=m) insert_AND(lson,L,R,v);
		if(R>m) insert_AND(rson,L,R,v);
		pushup(rt);
	}
	void insert_OR(int rt,int l,int r,int L,int R,int v){
		if(L<=l && r<=R){
			for(int i=0;i<DIG;i++){
				int x=v>>i;
				x&=1;
				tag[i][rt]|=x;
				if(tag[i][rt]==1) cal[i][rt]=r-l+1;
			}
			lazy[rt]=3;
			return;
		}
		int m=(l+r)>>1;
		pushdown(rt,l,r,lazy[rt]);
		if(L<=m) insert_OR(lson,L,R,v);
		if(R>m) insert_OR(rson,L,R,v);
		pushup(rt);
	}
	void insert_XOR(int rt,int l,int r,int L,int R,int v){
		if(L<=l && r<=R){
			for(int i=0;i<DIG;i++){
				int x=v>>i;
				x&=1;
				tag[i][rt]^=x;
				if(tag[i][rt]==1) cal[i][rt]=r-l+1-cal[i][rt];
			}
			lazy[rt]=2;
			return;
		}
		int m=(l+r)>>1;
		pushdown(rt,l,r,2);
		if(L<=m) insert_XOR(lson,L,R,v);
		if(R>m) insert_XOR(rson,L,R,v);
		pushup(rt);
	}
	ll query(int rt,int l,int r,int L,int R){
		ll ans=0;
		if(L<=l && r<=R){
			for(int i=0;i<DIG;i++){
				ll x=1ll<<i;
				ans+=(ll)(cal[i][rt])*x;
			}
			return ans;
		}
		int m=(l+r)>>1;
		pushdown(rt,l,r,lazy[rt]);
		if(L<=m) ans+=query(lson,L,R);
		if(R>m) ans+=query(rson,L,R);
		return ans;
	}
}T;

int main(){
	debug;
	int n,Q,op,L,R,v;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	T.build(1,1,n);
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&L,&R);
			ll ans=T.query(1,1,n,L,R);
			printf("%lld\n",ans);
		} else{
			scanf("%d%d%d",&L,&R,&v);
			if(op==2){
				T.insert_XOR(1,1,n,L,R,v);
			} else if(op==3){
				T.insert_OR(1,1,n,L,R,v);
			} else{
				T.insert_AND(1,1,n,L,R,v);
			}
		}
	}


	return 0;
}
