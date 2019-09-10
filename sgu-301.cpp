/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-09 22:23:46
 * @Description: 图论
 * @Source: http://codeforces.com/problemsets/acmsguru/problem/99999/301
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
using namespace std;
typedef pair<ll,int> PI;
const int MAX = 2e3+10;
const int MAXN =2e5+10;
const int MOD =1e9+9;
int n,xx,yy,m,tot=0;
int gra[MAX][MAX];
int vis[MAX],ans[MAX];
struct Edge{
	int u,v,nxt;
	ll w;
}edge[MAXN<<1];
struct Node{
	int id;
	ll dis;
	bool operator<(const Node&x){
		return dis<x.dis;
	}
}node[MAX];
ll disx[MAX],disy[MAX];int head[MAXN<<1];
vector<int> V[MAX];
void addedge(int u,int v,ll w){
	edge[++tot].u=u,edge[tot].v=v,edge[tot].w=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void dijskra(int xx,ll dis[]){
	prique<PI,vector<PI>,greater<PI> > Q;
	PI ss=make_pair(0,xx);
	mst(vis,0);
	dis[xx]=0;
	Q.push(ss);
	while(Q.size()){
		PI cur=Q.top();Q.pop();
		int x=cur.second;
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].nxt){
			int y=edge[i].v;
			if(dis[y]>dis[x]+edge[i].w){
				dis[y]=dis[x]+edge[i].w;
				Q.push(make_pair(dis[y],y));
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d%d",&n,&xx,&yy);
	scanf("%d",&m);
	mst(gra,INF);mst(disx,INF);mst(disy,INF);
	int u,v;ll w;
	for(int i=1;i<=m;i++){
		scanf("%d%d%lld",&u,&v,&w);
		gra[u][v]=gra[v][u]=w;
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dijskra(xx,disx);
	dijskra(yy,disy);
	mst(head,0);tot=0;
	ll D=disx[yy];
	int cnt=0;
	mst(vis,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j || gra[i][j]==INF) continue;
			if(gra[i][j]+disx[i]+disy[j]==D){
				if(disx[i]>disx[j]) swap(i,j);
				vis[i]=vis[j]=1;
				V[i].push_back(disx[j]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		int sz=V[i].size();
		if(sz==0) continue;
		sort(V[i].begin(),V[i].end());
		reverse(V[i].begin(),V[i].end());
		node[i].dis=disx[i];node[i].id=i;
	}
	sort(node+1,node+1+n);
	for(int i=1;i<=n;i++){
		int idx=node[i].id;
		if(!vis[idx]) continue;
		for(int j=1;j<=n;j++){
			int idy=node[j].id;
			if(!vis[idy]) continue;
			if(disx[idy]>=disx[idx]) break;
			if( V[idy][0]<=disx[idx]  ) continue;
			for(auto y:V[idy]){
				if(y>disx[idx]) ans[idx]++;
				else break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(i==xx || i==yy){
			printf("1 ");
			continue;
		}
		if(!vis[i]){
			printf("0 ");
			continue;
		}
		int tot=0;
		for(int j=1;j<=n;j++){
			if(vis[j] && (disx[j]==disx[i]))tot++;
		}
		printf("%d ",ans[i]+tot);
	}
	puts("");
	return 0;
}
