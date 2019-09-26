/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-26 14:07:22
 * @Description: 树链剖分+主席树
 * @Source: https://nanti.jisuanke.com/t/38229
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
const int MAXN=1e6+10;
const int MOD=1e9+7;
using namespace std;
int n,m,a[MAX],head[MAX],tot,rt[MAX];
struct Edge{
	int u,v,nxt,w;
}edge[MAX<<1];
struct Node{
	int l,r,k;
}Q[MAX];
int top[MAX],son[MAX],fa[MAX],sz[MAX],dep[MAX],id[MAX],cnt,rk[MAX];
int dc[MAX*2],dct;
void addedge(int u,int v,int w){
	edge[++tot].u=u;edge[tot].v=v;edge[tot].w=w;
	edge[tot].nxt=head[u];head[u]=tot;
}
int dfs1(int u,int ff){
	sz[u]=1;dep[u]=dep[ff]+1;fa[u]=ff;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff) continue;
		a[v]=edge[i].w;
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

struct Chairman{
	int ct,sum[MAX*20],lc[MAX*20],rc[MAX*20];
	void build(int &o,int l,int r){
		o=++ct;lc[o]=rc[o]=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lc[o],l,mid);build(rc[o],mid+1,r);
	}
	void insert(int &o,int pre,int l,int r,int x){
		o=++ct;lc[o]=lc[pre];rc[o]=rc[pre];sum[o]=sum[pre]+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(x<=mid)insert(lc[o],lc[pre],l,mid,x);
		else insert(rc[o],rc[pre],mid+1,r,x);
	}
	int query(int o,int pre,int l,int r,int x){
		int ans=0;
		if(l==r){
			return sum[o]-sum[pre];
		}
		int mid=(l+r)>>1;
		if(x>mid)ans+=sum[lc[o]]-sum[lc[pre]]+query(rc[o],rc[pre],mid+1,r,x);
		else ans+=query(lc[o],lc[pre],l,mid,x);
		return ans;
	}

}T;

int getans(int x,int y,int k){
	int ans=0;
	int tx=top[x],ty=top[y];
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=T.query(rt[id[x]],rt[id[top[x]]-1],1,dct,k);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ans+=T.query(rt[id[x]],rt[id[y]],1,dct,k);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif

	tot=cnt=0;
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);addedge(v,u,w);
		dc[++dct]=w;
	}
	dfs1(1,-1);dfs2(1,1);
	int x,y,c;
	sort(dc+1,dc+1+dct);
	dct=unique(dc+1,dc+1+dct)-(dc+1);
	T.build(rt[0],1,dct);
	T.build(rt[1],1,dct);
	for(int i=2;i<=n;i++){
		int x=lower_bound(dc+1,dc+1+dct,a[rk[i]])-dc;
		T.insert(rt[i],rt[i-1],1,dct,x);
	}
	int k,ans;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&k);
		int v=upper_bound(dc+1,dc+1+dct,k)-dc;
		v--;
		if(dc[v]>k || v==0)ans=0;
		else ans=getans(x,y,v);
		printf("%d\n",ans);
	}
	return 0;
}
