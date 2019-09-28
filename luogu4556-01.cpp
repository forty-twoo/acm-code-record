/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-28 22:05:10
 * @Description: 树链剖分+树上差分+离线处理
 * @Source: https://www.luogu.org/problem/P4556
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
int ans[MAX];
struct Edge{
	int u,v,nxt;
}edge[MAX<<1];
int top[MAX],son[MAX],fa[MAX],sz[MAX],dep[MAX],id[MAX],cnt,rk[MAX];
int dc[MAX*2],dct;
struct Node{
	int z,k;
};
vector<Node> V[MAX];

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
	int maxid[MAX<<2],sum[MAX<<2];
	void build(int rt,int l,int r){
		sum[rt]=0;
		if(l==r){
			maxid[rt]=l;
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		return;
	}
	void pushup(int rt){
		sum[rt]=max(sum[lc],sum[rc]);
		if(sum[lc]>=sum[rc]){
			maxid[rt]=maxid[lc];
		} else{
			maxid[rt]=maxid[rc];
		}
	}
	void insert(int rt,int l,int r,int x,int v){
		if(l==r){
			sum[rt]+=v;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)insert(lson,x,v);
		else insert(rson,x,v);
		pushup(rt);
	}
}T;

void solve(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Node tmp;
		tmp={z,1};
		V[id[top[x]]].push_back(tmp);
		tmp={z,-1};
		V[id[x]+1].push_back(tmp);

		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	Node tmp;
	tmp={z,1};
	V[id[y]].push_back(tmp);
	tmp={z,-1};
	V[id[x]+1].push_back(tmp);
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif

	tot=cnt=0;
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);addedge(v,u);
	}
	dfs1(1,0);dfs2(1,1);
	int x,y,z;

	//离线差分:把一次(x,y)的修改分成(a,b+1),(b,c+1)...这种形式
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		solve(x,y,z);
	}
	T.build(1,1,MAX);
	//必须按dfs序遍历, 因为包含一个点的段，要么以它为开头，要么dfs序在它之前
	for(int i=1;i<=n;i++){
		for(auto it:V[i]){
			T.insert(1,1,MAX,it.z,it.k);
		}
		ans[rk[i]]=T.sum[1]?T.maxid[1]:0;
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
