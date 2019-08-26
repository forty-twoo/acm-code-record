/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-26 14:51
 * @Description: 判断最小割是否唯一
 * @Source: https://zoj.pintia.cn/problem-sets/91827364500/problems/91827366086
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
const int MAX = 1e3+10;
const int MAXN = 3e4+10;
const int MOD = 998244353;
int S,T,n,m;
int head[MAXN],dis[MAX],tot=0;
int vis[MAX];
struct Edge{
	int u,v;
	ll w;
	int nxt;
}edge[MAXN];

void addedge(int u,int v,ll w){
	edge[++tot]={u,v,w,head[u]};
	head[u]=tot;
	edge[++tot]={v,u,w,head[v]};
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
			int v = edge[i].v; ll w = edge[i].w;
			if(w && !dis[v]) {
				Q.push(v); dis[v] = dis[x] + 1;
				if(v == T) return 1;
			}
		}
	}
	return 0;
}
ll dinic(int x,ll flow) {
	if(x == T) return flow;
	ll rest = flow,k;
	for(int i = head[x]; i&&rest; i = edge[i].nxt) {
		ll w = edge[i].w; int v = edge[i].v;
		if(edge[i].w && dis[v] == dis[x] + 1) {
			k = dinic(v,min(rest,edge[i].w));
			if(!k) dis[v] = 0;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			rest -= k;
		}
	}
	return flow - rest;
};

void bfs2(int ss){
	queue<int> Q;
	Q.push(ss);
	vis[ss]=1;
	while(Q.size()){
		int u=Q.front();Q.pop();
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;ll w=edge[i].w;
			if(w>0 && !vis[v]){
				vis[v]=1;
				Q.push(v);
			}
		}
	}
}
void bfs3(int ss){
	queue<int> Q;
	Q.push(ss);
	vis[ss]=1;
	while(Q.size()){
		int u=Q.front();Q.pop();
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;ll w=edge[i^1].w;
			if(w>0 && !vis[v]){
				vis[v]=1;
				Q.push(v);
			}
		}
	}
}


int main(){
	//debug;
	while(~scanf("%d%d%d%d",&n,&m,&S,&T) && n){
		int u,v;ll w;tot=1;mst(head,0);mst(vis,0);
		for(int i=1;i<=m;i++){
			scanf("%d%d%lld",&u,&v,&w);
			addedge(u,v,w);
		}
		ll maxflow=0,flow=0;
		while(bfs()){
			while(flow=dinic(S,INF)) maxflow+=flow;
		}
		bool f=true;
		bfs2(S);bfs3(T);
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				f=false;break;
			}
		}
		if(f){
			printf("UNIQUE\n");
		} else{
			printf("AMBIGUOUS\n");
		}

	}

	return 0;
}
