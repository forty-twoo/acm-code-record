/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-18 14:27:58
 * @Description: 线段树+单调栈
 * @Source: https://vjudge.net/problem/HYSBZ-5011
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
const int MAX=3e5+100;
const int MAXN=200;
const int MOD=1e9+7;
using namespace std;
int n,a[MAX],fir[MAX],lst[MAX];
int S[MAX],Sp[MAX];
struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	int num[MAX<<2],lazy[MAX<<2];
	void pushup(int rt){ num[rt]=num[lc]+num[rc]; }
	void pushdown(int rt){
		if(lazy[rt]){
			num[lc]=0;num[rc]=0;
			lazy[lc]=lazy[rc]=lazy[rt];
			lazy[rt]=0;
		}

	}
	void build(int rt,int l,int r){
		num[rt]=r-l+1;
		lazy[rt]=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lson);build(rson);
		//pushup(rt);
	}
	void change(int rt,int l,int r,int L,int R){
		if(L<=l && r<=R){
			lazy[rt]=1;
			num[rt]=0;
			return;
		}
		pushdown(rt);
		int mid=(l+r)>>1;
		if(L<=mid)change(lson,L,R);
		if(R>mid)change(rson,L,R);
		pushup(rt);
	}
	ll query(int rt,int l,int r,int L,int R){
		ll ans=0;
		if(L<=l && r<=R){
			return num[rt];
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(L<=mid)ans+=query(lson,L,R);
		if(R>mid) ans+=query(rson,L,R);
		return ans;
	}
}T;
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int ks;
	scanf("%d",&ks);
	while(ks--){
		int t=0;
		mst(fir,0);
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(!fir[a[i]])
				fir[a[i]]=i;
			lst[a[i]]=i;
		}
		T.build(1,1,n);
		ll ans=0;
		for(int i=1;i<=n;i++){
			if(lst[a[i]]==i && lst[a[i]]!=fir[a[i]]){
				T.change(1,1,n,fir[a[i]]+1,lst[a[i]]);
			} else{
				S[++t]=a[i];Sp[t]=i;
			}
			while(t && lst[S[t]]<=i)t--;
			int l=(t?Sp[t]:0);
			if(l!=i) ans+=(ll)T.query(1,1,n,l+1,i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
