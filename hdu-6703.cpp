/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-17 00:37:22
 * @Description: 权值线段树
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6703
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
const int MAX=1e5+100;
const int MAXN=200;
const int MOD=1e9+7;
using namespace std;
int n,m,a[MAX];
struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	int pos[MAX<<2];
	void pushup(int rt){
		pos[rt]=max(pos[lc],pos[rc]);
	}
	void build(int rt,int l,int r){
		pos[rt]=0;
		if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
	}
	void insert(int rt,int l,int r,int x,int p){
		if(l==r){
			pos[rt]=p;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) insert(lson,x,p);
		else insert(rson,x,p);
		pushup(rt);
	}
	//(k~n+1)
	int query(int rt,int l,int r,int L,int R,int p){
		int ans=INF;
		if(l==r){
			if(pos[rt]>p)ans=min(ans,l);
			return ans;
		}
		if(L<=l && r<=R){
			if(pos[rt]>p){
				int mid=(l+r)>>1;
				if(pos[lc]>p)
					ans=min(ans,query(lson,L,R,p));
				else if(pos[rc]>p)
					ans=min(ans,query(rson,L,R,p));
			}
			return ans;
		}
		int mid=(l+r)>>1;
		if(L<=mid)ans=min(ans,query(lson,L,R,p));
		if(R>mid)ans=min(ans,query(rson,L,R,p));
		return ans;
	}
}T;


int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int ks;scanf("%d",&ks);
	while(ks--){
		scanf("%d%d",&n,&m);
		int lastans=0;
		T.build(1,1,n+1);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			T.insert(1,1,n+1,a[i],i);
		}
		T.insert(1,1,n+1,n+1,n+1);
		int op,r,k,x;
		for(int i=1;i<=m;i++){
			scanf("%d",&op);
			if(op==1){
				scanf("%d",&x);
				x^=lastans;
				T.insert(1,1,n+1,a[x],n+1);
			} else{
				scanf("%d%d",&r,&k);
				r^=lastans,k^=lastans;
				int ans=T.query(1,1,n+1,k,n+1,r);
				printf("%d\n",ans);
				lastans=ans;
			}
		}
	}

	return 0;
}
