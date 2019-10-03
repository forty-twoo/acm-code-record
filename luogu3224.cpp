/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-03 14:02:19
 * @Description: 线段树合并
 * @Source: https://www.luogu.org/problem/P3224
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
const int MAX=1e5+10;
const int MAXN=MAX*20;
const int MOD=1e9+7;
using namespace std;
int n,m,Q;
int mp[MAX];
int fa[MAX],sz[MAX],a[MAX],rt[MAX];
int find(int x){
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}

struct SEGT{
	int cnt;int sum[MAXN],lc[MAXN],rc[MAXN];
	inline void insert(int &o,int l,int r,int x){
		if(!o)o=++cnt;
		if(l==r){
			sum[o]+=1;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)insert(lc[o],l,mid,x);
		else insert(rc[o],mid+1,r,x);
		sum[o]=sum[lc[o]]+sum[rc[o]];
	}
	inline int merge(int u,int v,int l,int r){
		if(!u||!v)return u|v;
		if(l==r){
			sum[u]+=sum[v];
			return u;
		}
		int mid=(l+r)>>1;
		lc[u]=merge(lc[u],lc[v],l,mid);
		rc[u]=merge(rc[u],rc[v],mid+1,r);
		sum[u]=sum[lc[u]]+sum[rc[u]];
		return u;
	}
	//find the kth val
	inline int query(int o,int l,int r,int k){
		if(l==r)return l;
		int mid=(l+r)>>1;
		if(sum[lc[o]]>=k)return query(lc[o],l,mid,k);
		else return query(rc[o],mid+1,r,k-sum[lc[o]]);
	}
}T;
char op[2];
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		T.insert(rt[i],1,n,a[i]);
		mp[a[i]]=i;
	}
	for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);
		if(sz[fx]<sz[fy])swap(fy,fx);
		if(fx==fy)continue;
		fa[fy]=fx;
		sz[fx]+=sz[fy];
		rt[fx]=T.merge(rt[fx],rt[fy],1,n);
	}
	int Q;
	scanf("%d",&Q);
	while(Q--){
		scanf("%s",op);
		if(op[0]=='B'){
			scanf("%d%d",&x,&y);
			if(x==0 || y==0)continue;
			int fx=find(x),fy=find(y);
			if(sz[fx]<sz[fy])swap(fy,fx);
			if(fx==fy)continue;
			fa[fy]=fx;
			sz[fx]+=sz[fy];
			rt[fx]=T.merge(rt[fx],rt[fy],1,n);
		}else{
			int k;
			scanf("%d%d",&x,&k);
			if(x>n || x==0){
				printf("-1\n");
				continue;
			}
			int fx=find(x);
			if(sz[fx]<k){
				printf("-1\n");
				continue;
			}
			int ans=T.query(rt[fx],1,n,k);
			printf("%d\n",mp[ans]);
		}
	}
	return 0;
}
