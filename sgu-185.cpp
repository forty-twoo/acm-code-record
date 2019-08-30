/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-30 19:27
 * @Description: 图重构 最短路 最大流
 * @Source: http://codeforces.com/problemsets/acmsguru/problem/99999/185
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f
#define eps 1e-8
typedef long long ll;
typedef  unsigned long long ull;
using namespace std;
const int MAX = 4e2+5;
const int MAXN=2e5+100;
const int MOD = 998244353;
int n,m,S,T,dis[MAX],vis[MAX],gra[MAX][MAX];
vector<int> ans[3];
int head[MAXN],tot=1;
struct Edge{
	int u,v;
	int w;
	int nxt;
	int used;
}edge[MAXN];

void addedge(int u,int v,int w){
	edge[++tot]={u,v,w,head[u],0};
	head[u]=tot;
	edge[++tot]={v,u,0,head[v],1};
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

void dijskra(){
	mst(dis,INF);
	vis[S]=1;
	dis[S]=0;
	int p=S;
	for(int i=1;i<n;i++){
		for(int j=1;j<=n;j++){
			if(dis[j]>dis[p]+gra[p][j]){
				dis[j]=dis[p]+gra[p][j];
			}
		}
		int minn=INF;
		for(int j=1;j<=n;j++){
			if(dis[j]<minn && !vis[j]){
				minn=dis[j];p=j;
			}
		}
		vis[p]=1;
	}
}
void build(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j || gra[i][j]==INF) continue;
			if(dis[i]+gra[i][j]==dis[j]){
				addedge(i,j,1);
			}
		}
	}
}
void dfs(int x,int id){
	if(x==T){
		ans[id].push_back(T);return;
	}
	ans[id].push_back(x);
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].v;
		int w=edge[i].w;
		if(w==0 &&(i%2==0) && edge[i].used==0){
			edge[i].used=1;
			dfs(to,id);
			return;
		}
	}
}
bool check(){
	int maxf=0;
	S=n+1;
	addedge(S,1,2);
	while(bfs()) maxf+=dinic(S,INF);
	if(maxf<2) return false;
	else return true;
}

int main(){
	//	debug;
	scanf("%d%d",&n,&m);
	int u,v,w;
	tot=1;S=1,T=n;mst(gra,INF);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		gra[u][v]=gra[v][u]=w;
	}
	dijskra();
	build();
	if(!check()){
		printf("No solution\n");
	} else{
		dfs(1,1);dfs(1,2);
		for(int i=0;i<ans[1].size();i++){
			printf("%d ",ans[1][i]);
		}
		puts("");
		for(int i=0;i<ans[2].size();i++){
			printf("%d ",ans[2][i]);
		}
		puts("");
	}
	return 0;
}

