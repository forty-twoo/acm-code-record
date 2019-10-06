/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-06 14:11:04
 * @Description: 线段树区间操作(给一个序列是否满足任意一个连续子序列中至少有一个元素只出现一次)
 * @Source: https://vjudge.net/problem/UVA-1608
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f3f3f
#define eps 1e-8
typedef long long ll;
typedef  unsigned long long ull;
using namespace std;
const int MAX = 2e5+10;
int n,k,a[MAX],pos[MAX];
vector<int> V[MAX];
int dc[MAX],tot;

struct SEGT{
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
#define ls rt<<1
#define rs rt<<1|1

	int lazy[MAX<<2],maxv[MAX<<2];
	void pushup(int rt){
		maxv[rt]=max(maxv[ls],maxv[rs]);
	}
	void pushdown(int rt){
		if(lazy[rt]){
			maxv[ls]+=lazy[rt];
			maxv[rs]+=lazy[rt];
			lazy[ls]+=lazy[rt];
			lazy[rs]+=lazy[rt];
			lazy[rt]=0;
		}
	}
	void build(int rt,int l,int r){
		lazy[rt]=maxv[rt]=0;
		if(l==r) {
			return;
		}
		int m=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void insert(int rt,int l,int r,int L,int R,int v){
		if(L<=l && r<=R){
			maxv[rt]+=v;
			lazy[rt]+=v;
			return;
		}
		int m=(l+r)>>1;
		pushdown(rt);
		if(L<=m) insert(lson,L,R,v);
		if(R>m) insert(rson,L,R,v);
		pushup(rt);
	}
	int query(int rt,int l,int r){
		if(l==r) {
			return l;
		}
		int m=(l+r)>>1;
		pushdown(rt);
		if(maxv[ls]==tot) return query(lson);
		else if(maxv[rs]==tot) return query(rson);
		else return -1;
	}
}T;

int main(){
#ifndef ONLINE_JUDGE
	debug;

#endif // !ONLINE_JUDGE

	int ks;
	scanf("%d",&ks);
	while(ks--){
		tot=0;
		scanf("%d",&n);
		for(int i=0;i<=n;i++) pos[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			dc[++tot]=a[i];
		}
		if(n==1){
			printf("non-boring\n");
			continue;
		}
		sort(dc+1,dc+1+tot);
		tot=unique(dc+1,dc+1+tot)-(dc+1);
		for(int i=1;i<=tot;i++){
			V[i].clear();
			V[i].push_back(0);
		}
		for(int i=1;i<=n;i++){
			int x=lower_bound(dc+1,dc+1+tot,a[i])-dc;
			V[x].push_back(i);
		}
		T.build(1,1,n);
		k=2;
		for(int i=1;i<=tot;i++){
			for(int j=1;j<V[i].size();j++){
				pos[V[i][j]]=j;
			}
		}
		int ans=0;
		bool flg=1;

		for(int i=1;i<=n;i++){
			int x=lower_bound(dc+1,dc+1+tot,a[i])-dc;
			T.insert(1,1,n,i,i,tot-1);
			int prep=V[x][pos[i]-1]+1;
			if(i-1>=prep)
				T.insert(1,1,n,prep,i-1,-1);
			if(pos[i]>=k){
				prep=V[x][pos[i]-k]+1;
				T.insert(1,1,n,prep,V[x][pos[i]-k+1],1);
			}
			int q=T.query(1,1,n);
			if(q!=-1){
				flg=0;
				break;
			}
		}
		if(!flg)
			printf("boring\n");
		else
			printf("non-boring\n");
	}
	return 0;
}

