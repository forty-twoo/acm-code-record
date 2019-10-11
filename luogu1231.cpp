/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-11 19:20:28
 * @Description: 网络流
 * @Source: https://www.luogu.org/problem/P1231
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 5e5 + 10;
const int MAXN=5e5+10;
const ll MOD = 998244353;
int n1,n2,n3,m1,m2;
int S,T;
int head[MAXN],dis[MAX],tot=0;
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
	scanf("%d%d%d",&n1,&n2,&n3);
	scanf("%d",&m1);
	tot=1;
	/*注意书必须拆点，否则会被重复使用*/
	for(int i=1;i<=m1;i++){
		scanf("%d%d",&x,&y);
		addedge(y+2*n1,x,1);
	}
	scanf("%d",&m2);
	for(int i=1;i<=m2;i++){
		scanf("%d%d",&x,&y);
		addedge(x+n1,y+2*n1+n2,1);
	}
	S=2*n1+n2+n3+2;T=S+1;
	for(int i=1;i<=n1;i++){
		addedge(i,i+n1,1);
	}
	for(int i=2*n1+1;i<=2*n1+n2;i++){
		addedge(S,i,1);
	}
	for(int i=2*n1+n2+1;i<=2*n1+n2+n3;i++){
		addedge(i,T,1);
	}

	int ans=0,flow;
	while(bfs()){
		while(flow=dinic(S,INF))ans+=flow;
	}
	printf("%d\n",ans);

	return 0;
}

