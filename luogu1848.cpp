/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-27 14:09:03
 * @Description: 单调队列+单调栈+线段树优化dp
 * @Source: https://www.luogu.org/problem/P1848
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
const int MAX=1e5+10;
const int MAXN=1e6+10;
const int MOD=1e9+7;
using namespace std;
int n;
ll lim,w[MAX],h[MAX];
ll f[MAX];
ll hmax[MAX];
int Q[MAX];
int ql,qr;
int sta[MAX],top;
int pre[MAX];
void init(){
	sta[++top]=1;
	for(int i=2;i<=n;i++){
		while(top && h[i]>h[sta[top]])top--;
		if(top)pre[i]=sta[top];
		sta[++top]=i;
	}
}
struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	ll  minv[MAX<<2],hh[MAX<<2],ff[MAX<<2];int lazy[MAX<<2];
	void pushup(int rt){
		hh[rt]=max(hh[lc],hh[rc]);
		ff[rt]=min(ff[lc],ff[rc]);
		minv[rt]=min(minv[lc],minv[rc]);
	}
	void pushdown(int rt){
		if(lazy[rt]){
			hh[lc]=hh[rt];
			hh[rc]=hh[rt];
			minv[lc]=hh[lc]+ff[lc];
			minv[rc]=hh[rc]+ff[rc];
			lazy[lc]=lazy[rc]=1;
			lazy[rt]=0;
		}
	}
	void build(int rt,int l,int r){
		ff[rt]=INF;
		minv[rt]=INF;
		if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
	}
	void change(int rt,int l,int r,int x,ll v){
		if(l==r){
			ff[rt]=v;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(x<=mid)change(lson,x,v);
		else change(rson,x,v);
		pushup(rt);
	}
	void changeH(int rt,int l,int r,int L,int R,ll v){
		if(L>R)return;
		if(L<=l && r<=R){
			hh[rt]=v;
			minv[rt]=v+ff[rt];
			lazy[rt]=1;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(L<=mid)changeH(lson,L,R,v);
		if(R>mid)changeH(rson,L,R,v);
		pushup(rt);
	}
	ll query(int rt,int l,int r,int L,int R){
		ll ans=INF;
		if(L<=l &&r<=R){
			return minv[rt];
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(L<=mid)ans=min(ans,query(lson,L,R));
		if(R>mid)ans=min(ans,query(rson,L,R));
		pushup(rt);
		return ans;
	}
}T;

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%lld",&n,&lim);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&h[i],&w[i]);
		w[i]=w[i-1]+w[i];
	}
	ql=1;qr=0;
	init(); //初始化单调栈

	T.build(1,1,n+1);
	T.change(1,1,n+1,1,0);
	Q[++qr]=1;
	for(int i=2;i<=n+1;i++){
		while(ql<=qr && w[i-1]-w[Q[ql]-1]>lim)ql++; //单调队列限制范围在lim之内
		int prep=max(Q[ql],pre[i-1]+1);
		T.changeH(1,1,n+1,prep,i-1,h[i-1]);
		f[i]=T.query(1,1,n+1,Q[ql],i-1);
		Q[++qr]=i;
		T.change(1,1,n+1,i,f[i]);
	}
	printf("%lld\n",f[n+1]);

	return 0;
}
