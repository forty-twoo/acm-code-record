/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-03 21:29:24
 * @Description: 严格次小生成树(树链剖分)
 * @Source: https://www.luogu.org/problem/P4180
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
const int MAX=3e5+10;
const int MOD=1e9+7;
using namespace std;
int n,m;
int ufa[MAX],vis[MAX],a[MAX],head[MAX];
typedef pair<int,int> PI;
int tot;
struct Node{
	int u,v,w;
	bool operator<(const Node&x)const{
		return w<x.w;
	}
}cun[MAX];
struct Edge{
	int u,v,w,nxt;
}edge[MAX<<1];
int top[MAX],son[MAX],fa[MAX],sz[MAX],dep[MAX],id[MAX],cnt,rk[MAX];
void addedge(int u,int v,int w){
	edge[++tot].u=u;edge[tot].v=v;
	edge[tot].w=w;
	edge[tot].nxt=head[u];head[u]=tot;
}
int dfs1(int u,int ff){
	sz[u]=1;dep[u]=dep[ff]+1;fa[u]=ff;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		int w=edge[i].w;
		if(v==ff) continue;
		a[v]=w;
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
	int maxv[MAX<<2],smaxv[MAX<<2];
	void pushup(int rt){
		maxv[rt]=max(maxv[lc],maxv[rc]);
		smaxv[rt]=max(smaxv[lc],smaxv[rc]);
		if(maxv[lc]!=maxv[rt] && maxv[lc]>smaxv[rt]) smaxv[rt]=maxv[lc];
		if(maxv[rc]!=maxv[rt] && maxv[rc]>smaxv[rt]) smaxv[rt]=maxv[rc];
	}
	void build(int rt,int l,int r){
		if(l==r){
			maxv[rt]=a[rk[l]];
			smaxv[rt]=-INF;
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	PI querymax(int rt,int l,int r,int L,int R){
		if(L>R){
			return make_pair(-INF,-INF);
		}
		int mv=-INF;
		int smv=-INF;
		if(L<=l && r<=R){
			mv=maxv[rt];
			smv=smaxv[rt];
			return make_pair(mv,smv);
		}
		int mid=(l+r)>>1;
		if(L<=mid){
			PI cur=querymax(lson,L,R);
			mv=max(mv,cur.first);
			smv=max(smv,cur.second);
			if(cur.first!=mv && cur.first>smv)smv=cur.first;

		}
		if(R>mid){
			PI cur=querymax(rson,L,R);
			mv=max(mv,cur.first);
			smv=max(smv,cur.second);
			if(cur.first!=mv && cur.first>smv)smv=cur.first;
		}

		return make_pair(mv,smv);
	}

}T;
PI getmax(int x,int y){
	int v1=-INF,v2=-INF;
	int tx=top[x],ty=top[y];
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);

		PI pi=T.querymax(1,1,n,id[top[x]],id[x]);
		v1=max(v1,pi.first);
		v2=max(v2,pi.second);
		if(v1!=pi.first && pi.first>v2){
			v2=pi.first;
		}
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	PI pi=T.querymax(1,1,n,id[y]+1,id[x]);
	v1=max(v1,pi.first);
	v2=max(v2,pi.second);
	if(v1!=pi.first && pi.first>v2){
		v2=pi.first;
	}
	return make_pair(v1,v2);
}

int find(int x){
	if(ufa[x]==x)return x;
	return ufa[x]=find(ufa[x]);
}
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		cun[i]={u,v,w};
	}
	for(int i=1;i<=n;i++)ufa[i]=i;
	ll all=0;
	sort(cun+1,cun+1+m);
	for(int i=1;i<=m;i++){
		int u=cun[i].u,v=cun[i].v;
		int fu=find(u),fv=find(v);
		if(fu==fv)continue;
		ufa[fv]=fu;
		addedge(u,v,cun[i].w);
		addedge(v,u,cun[i].w);
		all+=(ll)cun[i].w;
		vis[i]=1;
	}
	dfs1(1,0);dfs2(1,1);

	a[1]=-INF;
	T.build(1,1,n);

	ll minn=1e18;
	for(int i=1;i<=m;i++){
		if(vis[i])continue;
		ll ans=1e18;
		int u=cun[i].u;
		int v=cun[i].v;
		PI tmp=getmax(u,v);

		if(tmp.first==cun[i].w){
			if(tmp.second!=-INF&&tmp.second!=-1&& tmp.second!=tmp.first){
				ans=all-tmp.second+cun[i].w;
			}
		} else{
			ans=all-tmp.first+cun[i].w;
		}

		minn=min(ans,minn);
	}
	printf("%lld\n",minn);

	return 0;
}

