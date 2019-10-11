/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-11 21:57:22
 * @Description: 网络流求最小割点数(拆点建图转化为最小割边)
 * @Source: https://www.luogu.org/problem/P1345
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 5e2 + 10;
const int MAXN=6e3;
const ll MOD = 998244353;
int n,m;
int S,T;
int head[MAX],dis[MAX],tot=0;
struct Edge{
	int u,v;
	int w;
	int nxt;
}edge[MAXN];

void addedge(int u,int v,int w){
	edge[++tot]={u,v,w,head[u]};
	head[u]=tot;
	edge[++tot]={v,u,0,head[v]};
	head[v]=tot;
}

bool bfs() {
	int s=S;
	queue<int> Q;
	memset(dis,0,sizeof(dis));
	while(Q.size()) Q.pop();
	Q.push(s); dis[s] = 1;
	while(Q.size()) {
		int x = Q.front(); Q.pop();
		for(int i = head[x]; i; i = edge[i].nxt) {
			int v = edge[i].v; int w = edge[i].w;
			if(w && !dis[v]) {
				Q.push(v); dis[v] = dis[x] + 1;
				if(v == T) return 1;
			}
		}
	}
	return 0;
}
int dinic(int x,int flow) {
	if(x == T) return flow;
	int rest = flow,k;
	for(int i = head[x]; i&&rest; i = edge[i].nxt) {
		int w = edge[i].w; int v = edge[i].v;
		if(edge[i].w && dis[v] == dis[x] + 1) {
			k = dinic(v,min(rest,edge[i].w));
			if(!k) dis[v] = 0;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("data.txt","r",stdin);
#endif
	int x,y;
	tot=1;
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		addedge(x+n,y,INF);
		addedge(y+n,x,INF);
	}
	for(int i=1;i<=n;i++){
		addedge(i,i+n,1);
	}
	S=S+n;
	int ans=0,flow;
	while(bfs()){
		while(flow=dinic(S,INF))ans+=flow;
	}
	printf("%d\n",ans);

	return 0;
}

