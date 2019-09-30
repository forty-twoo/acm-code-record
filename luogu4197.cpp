/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-30 22:22:19
 * @Description: 线段树合并+幷查集(离线处理)
 * @Source: https://www.luogu.org/problem/P4197
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
int dc[MAX],h[MAX],tot=0;
int rt[MAX],fa[MAX],sz[MAX],ans[MAX*5];
struct Edge{
	int u,v,w;
	bool operator<(const Edge&x){
		return w<x.w;
	}
}edge[MAX*5];
struct Query{
	int u;
	int lim;
	int k;
	int id;
	bool operator<(const Query&x)const{
		return lim<x.lim;
	}
}node[MAX*5];
int find(int x){
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[fa[x]]);
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
	inline int query(int o,int l,int r,int k){
		if(l==r)return l;
		int mid=(l+r)>>1;
		if(sum[rc[o]]>=k)return query(rc[o],mid+1,r,k);
		else return query(lc[o],l,mid,k-sum[rc[o]]);
	}
}T;

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=n;i++){
		scanf("%d",&h[i]);
		dc[++tot]=h[i];
	}
	sort(dc+1,dc+1+tot);
	tot=unique(dc+1,dc+1+tot)-(dc+1);
	for(int i=1;i<=n;i++){
		int x=lower_bound(dc+1,dc+1+tot,h[i])-dc;
		T.insert(rt[i],1,tot,x);
	}
	int u,v,w,x,k;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		edge[i]={u,v,w};
	}
	sort(edge+1,edge+1+m);
	for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	for(int i=1;i<=Q;i++){
		scanf("%d%d%d",&v,&x,&k);
		node[i]={v,x,k,i};
	}
	sort(node+1,node+1+Q);
	int et=0;
	for(int i=1;i<=Q;i++){
		int lim=node[i].lim;
		while(edge[et+1].w<=lim && et<=m){
			++et;
			int fu=find(edge[et].u);
			int fv=find(edge[et].v);
			if(fu==fv)continue;
			fa[fv]=fu;
			sz[fu]+=sz[fv];
			rt[fu]=T.merge(rt[fu],rt[fv],1,tot);
		}
		int fu=find(node[i].u);
		if(sz[fu]<node[i].k)ans[node[i].id]=-1;
		else ans[node[i].id]=dc[T.query(rt[fu],1,tot,node[i].k)];
	}
	for(int i=1;i<=Q;i++)printf("%d\n",ans[i]);

	return 0;
}
