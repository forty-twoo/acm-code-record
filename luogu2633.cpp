/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-28 15:33:21
 * @Description: 主席树求树上路径第k小(树形关系主席树+LCA)
 * @Source: https://www.luogu.org/problem/P2633
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
int n,m,head[MAX],tot,rt[MAX];
int f[MAX][25];
struct Edge{
	int u,v,nxt;
}edge[MAX<<1];

int fa[MAX],dep[MAX],cnt,dct;
ll dc[MAX],a[MAX];
void addedge(int u,int v){
	edge[++tot].u=u;edge[tot].v=v;
	edge[tot].nxt=head[u];head[u]=tot;
}
void dfs1(int u,int ff){
	dep[u]=dep[ff]+1;fa[u]=ff;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff) continue;
		dfs1(v,u);
	}
	return;
}
void pre(){
	for(int i=1;i<=n;i++){
		f[i][0]=fa[i];
	}
	for(int i=1;i<=20;i++){
		for(int j=1;j<=n;j++){
			if(dep[f[j][i-1]]<=0) continue;
			if(dep[f[j][i-1]]-(1<<(i-1))<=0) continue;
			f[j][i]=f[f[j][i-1]][i-1];
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--){
		if(dep[f[x][i]]>=dep[y])x=f[x][i];
		if(x==y)return x;
	}
	for(int i=20;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];y=f[y][i];
		}
	}
	return f[x][0];
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
		o=++ct;lc[o]=lc[pre];rc[o]=rc[pre];
		sum[o]=sum[pre]+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(x<=mid)insert(lc[o],lc[pre],l,mid,x);
		else insert(rc[o],rc[pre],mid+1,r,x);
	}
	int query(int u,int v,int lca,int flca,int l,int r,int k){
		if(l==r){
			return l;
		}
		int mid=(l+r)>>1;
		int sz=sum[lc[u]]+sum[lc[v]]-sum[lc[lca]]-sum[lc[flca]];
		if(k<=sz) return query(lc[u],lc[v],lc[lca],lc[flca],l,mid,k);
		else return query(rc[u],rc[v],rc[lca],rc[flca],mid+1,r,k-sz);
	}

}T;

//建树形关系主席树
void buildtree(int u,int ff){
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff) continue;
		int x=lower_bound(dc+1,dc+1+dct,a[v])-dc; //discrete
		T.insert(rt[v],rt[u],1,dct,x);
		buildtree(v,u);
	}
}


int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif

	tot=cnt=0;
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		dc[++dct]=a[i];
	}
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);addedge(v,u);
	}
	dfs1(1,0);pre();
	int x,y,c;
	sort(dc+1,dc+1+dct);
	dct=unique(dc+1,dc+1+dct)-(dc+1);
	T.build(rt[0],1,dct);
	v=lower_bound(dc+1,dc+1+dct,a[1])-dc;
	T.insert(rt[1],rt[0],1,dct,v);
	buildtree(1,0);
	int k,ans;
	int lst=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&k);
		x^=lst;
		ans=dc[T.query(rt[x],rt[y],rt[LCA(x,y)],rt[fa[LCA(x,y)]],1,dct,k)];
		lst=ans;
		printf("%lld\n",ans);
	}
	return 0;
}
