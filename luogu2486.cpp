/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-25 16:26:56
 * @Description: 树链剖分求树上颜色段(带修改)
 * @Source: https://www.luogu.org/problem/P2486
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
const int MAXN=1e6+10;
const int MOD=1e9+7;
using namespace std;
int n,m,a[MAX],head[MAX],tot;
struct Edge{
	int u,v,nxt;
}edge[MAX<<1];
int top[MAX],son[MAX],fa[MAX],sz[MAX],dep[MAX],id[MAX],cnt,rk[MAX];
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
	int colr[MAX<<2],coll[MAX<<2],num[MAX<<2],lazy[MAX<<2];
	void pushup(int rt){
		num[rt]=num[lc]+num[rc];
		colr[rt]=colr[rc];
		coll[rt]=coll[lc];
		if(colr[lc]==coll[rc]){
			num[rt]-=1;
		}
	}
	void pushdown(int rt){
		if(lazy[rt]){
			coll[lc]=coll[rc]=lazy[rt];
			colr[lc]=colr[rc]=lazy[rt];
			num[lc]=num[rc]=1;
			lazy[lc]=lazy[rc]=lazy[rt];
			lazy[rt]=0;
		}
	}
	void build(int rt,int l,int r){
		if(l==r){
			colr[rt]=coll[rt]=a[rk[l]];
			num[rt]=1;
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void change(int rt,int l,int r,int L,int R,int c){
		if(L<=l && r<=R){
			coll[rt]=colr[rt]=c;
			num[rt]=1;
			lazy[rt]=c;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(L<=mid) change(lson,L,R,c);
		if(R>mid) change(rson,L,R,c);
		pushup(rt);
	}
	int z;
	int query(int rt,int l,int r,int L,int R){
		int ans=0;
		if(L<=l && r<=R){
			if(z==coll[rt]) ans=num[rt]-1;
			else ans=num[rt];
			z=colr[rt];
			return ans;
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(L<=mid) ans+=query(lson,L,R);
		if(R>mid) ans+=query(rson,L,R);
		pushup(rt);
		return ans;
	}
	int Qcol(int rt,int l,int r,int x){
		if(l==r){
			return coll[rt];
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(x<=mid)return Qcol(lson,x);
		else return Qcol(rson,x);
		pushup(rt);
	}

}T;
void solve(int x,int y,int c){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y); //注意比较的是top的dep
		T.change(1,1,n,id[top[x]],id[x],c);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	T.change(1,1,n,id[y],id[x],c);
}
int getans(int x,int y){
	int ans=0;
	int coltmp,colx,tmp;
	while(top[x]!=top[y]){
		T.z=-INF;
		if(dep[top[x]]<dep[top[y]])swap(x,y); //同上
		ans+=T.query(1,1,n,id[top[x]],id[x]);
		tmp=top[x];
		x=fa[top[x]];
		coltmp=T.Qcol(1,1,n,id[tmp]);
		if(x==0)colx=-1;
		else colx=T.Qcol(1,1,n,id[x]);
		if(coltmp==colx)ans--;
	}
	T.z=-INF;
	if(dep[x]<dep[y])swap(x,y);
	ans+=T.query(1,1,n,id[y],id[x]);
	return ans;
}


int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif

	tot=cnt=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	int u,v;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);addedge(v,u);
	}
	dfs1(1,-1);dfs2(1,1);
	fa[1]=1;
	T.build(1,1,n);
	char op;
	int x,y,c;
	for(int i=1;i<=m;i++){
		scanf(" %c",&op);
		if(op=='C'){
			scanf("%d%d%d",&x,&y,&c);
			solve(x,y,c);
		} else{
			scanf("%d%d",&x,&y);
			int ans=getans(x,y);
			printf("%d\n",ans);
		}
	}
	return 0;
}
