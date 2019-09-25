/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-25 19:53:08
 * @Description: 离线处理+树链剖分+LCA转化为区间求和
 * @Source: https://www.luogu.org/problem/P4211
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
const int MAX=5e4+100;
const int MAXN=2e5;
const int MOD=201314;
using namespace std;
int n,m,a[MAX],head[MAX],tot;
struct Edge{
	int u,v,nxt;
}edge[MAXN];
struct Node{
	int id;
	int op; //1:L 2:R
	int r;
	int z;
	bool operator<(const Node&x){
		return r<x.r;
	}
}node[MAXN];
int top[MAX],son[MAX],fa[MAX],sz[MAX],dep[MAX],id[MAX],cnt,rk[MAX];
ll ans[MAX];
void addedge(int u,int v){
	edge[++tot].u=u;edge[tot].v=v;
	edge[tot].nxt=head[u];head[u]=tot;
}
int dfs1(int u,int ff){
	sz[u]=1;dep[u]=dep[ff]+1;fa[u]=ff;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff) continue;
		sz[u]+=dfs1(v,u);
		if(sz[v]>sz[son[u]]){
			son[u]=v;
		}
	}
	return sz[u];
}
void dfs2(int u,int ff){
	top[u]=ff;
	id[u]=++cnt;
	rk[cnt]=u;
	if(son[u]){
		dfs2(son[u],ff);
	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v!=son[u] && v!=fa[u])
			dfs2(v,v);
	}
}

struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	int sum[MAX<<2],lazy[MAX<<2];
	void pushup(int rt){
		sum[rt]=(sum[lc]+sum[rc])%MOD;
	}
	void pushdown(int rt,int l,int r){
		int mid=(l+r)>>1;
		if(lazy[rt]){
			sum[lc]=(sum[lc]+(ll)(mid-l+1)*lazy[rt]%MOD)%MOD;
			sum[rc]=(sum[rc]+(ll)(r-mid)*lazy[rt]%MOD)%MOD;
			lazy[rc]+=lazy[rt];
			lazy[lc]+=lazy[rt];
			lazy[rt]=0;
		}
	}
	void build(int rt,int l,int r){
		if(l==r){
			sum[rt]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void change(int rt,int l,int r,int L,int R){
		if(L<=l && r<=R){
			sum[rt]=(r-l+1+sum[rt])%MOD;
			lazy[rt]+=1;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(rt,l,r);
		if(L<=mid) change(lson,L,R);
		if(R>mid) change(rson,L,R);
		pushup(rt);
	}
	int query(int rt,int l,int r,int L,int R){
		ll ans=0;
		if(L<=l && r<=R){
			return sum[rt];
		}
		int mid=(l+r)>>1;
		pushdown(rt,l,r);
		if(L<=mid) ans=(ans+query(lson,L,R))%MOD;
		if(R>mid) ans=(ans+query(rson,L,R))%MOD;
		pushup(rt);
		return ans;
	}
}T;

void solve(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		T.change(1,1,n,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	T.change(1,1,n,id[y],id[x]);
}
int queryans(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=(ans+T.query(1,1,n,id[top[x]],id[x]))%MOD;
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	ans=(ans+T.query(1,1,n,id[y],id[x]))%MOD;
	return ans;

}
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	tot=cnt=0;
	scanf("%d%d",&n,&m);
	int u;
	for(int i=1;i<n;i++){
		scanf("%d",&u);
		u++;
		addedge(u,i+1);addedge(i+1,u);
	}
	int l,r,z;int cn=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l,&r,&z);
		l++,r++,z++;
		node[++cn]={i,1,l-1,z};
		node[++cn]={i,2,r,z};
	}
	dfs1(1,-1);dfs2(1,1);
	sort(node+1,node+1+cn);
	T.build(1,1,n);
	int t=1;
	for(int i=1;i<=cn;i++){
		while(node[i].r>=t){
			solve(1,t);
			t++;
		}
		if(node[i].op==1)ans[node[i].id]=(-1)*queryans(1,node[i].z)%MOD;
		else ans[node[i].id]=(ans[node[i].id]+queryans(1,node[i].z)+MOD)%MOD;
	}
	for(int i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}

	return 0;
}
