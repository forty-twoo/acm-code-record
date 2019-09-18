/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-18 15:23:23
 * @Description: 二分图最大独立集+贪心 (Dinic解法)
 * @Source: https://vjudge.net/problem/UVALive-7958
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
const int MAX=70;
const int MAXN=1e6+10;
const int MOD=1e9+7;
using namespace std;
int n,m,S,T,ans,tot,cnt,dis[2000];
char str[MAX][MAX];
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int ins[MAX][MAX],head[2000];
int match[2000],vis[2000];
struct Node{
	int x,y;
};
struct Edge{
	int u,v,w,nxt;
}edge[MAXN];
void addedge(int u,int v,int w){
	edge[++tot].u=u;edge[tot].v=v;edge[tot].w=w;
	edge[tot].nxt=head[u];head[u]=tot;
	edge[++tot].u=v;edge[tot].v=u;edge[tot].w=0;
	edge[tot].nxt=head[v];head[v]=tot;
}
bool dfs(int x){
	vis[x]=1;
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].v;
		if(vis[to]) continue;
		vis[to]=1;
		if(!match[to] || dfs(match[to])){
			match[to]=x;
			return 1;
		}
	}
	return 0;

}
void get_scc(int x,int y){
	queue<Node> Q;
	Node cur;cur.x=x,cur.y=y;
	Q.push(cur);
	ins[cur.x][cur.y]=1;
	while(Q.size()){
		Node cur=Q.front();Q.pop();
		if((cur.x+cur.y)%2==0) addedge(S,(cur.x-1)*m+cur.y,1);
		else addedge((cur.x-1)*m+cur.y,T,1);
		for(int i=1;i<=4;i++){
			int xx=cur.x+dx[i];
			int yy=cur.y+dy[i];
			if(xx<=n && xx>=1 && yy<=m && yy>=1 && str[xx][yy]=='C'){
				Node tmp;tmp.x=xx;tmp.y=yy;
				if((cur.x+cur.y)%2==0)
					addedge((cur.x-1)*m+cur.y,(xx-1)*m+yy,INF);
				else
					addedge((xx-1)*m+yy,(cur.x-1)*m+cur.y,INF);
				if(!ins[xx][yy]){
					Q.push(tmp);
					ins[xx][yy]=1;
				}
			}
		}

	}
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
}

int solve(){
	int maxf=0,flow=0;
	while(bfs()){
		while(flow=dinic(S,INF)) maxf+=flow;
	}
	return maxf;
}
void calL(int x,int y){
	queue<Node> Q;
	Node cur;cur.x=x,cur.y=y;
	Q.push(cur);
	ins[x][y]=1;
	while(Q.size()){
		Node cur=Q.front();Q.pop();
		for(int i=1;i<=4;i++){
			int xx=cur.x+dx[i];
			int yy=cur.y+dy[i];
			if(!ins[xx][yy] && xx<=n && xx>=1 && yy<=m && yy>=1){
				if(str[xx][yy]=='L'){
					Node tmp;tmp.x=xx;tmp.y=yy;
					ins[xx][yy]=1;
					Q.push(tmp);
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",str[i]+1);
	}
	tot=1;ans=0;cnt=0;S=n*m+1,T=n*m+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(str[i][j]=='L'){
				for(int k=1;k<=4;k++){
					int xx=i+dx[k];
					int yy=j+dy[k];
					if(str[xx][yy]=='C') str[xx][yy]='W';
				}

			}
		}
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ins[i][j] || str[i][j]!='L') continue;
			calL(i,j);
			ans++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(str[i][j]!='C' || ins[i][j]) continue;
			get_scc(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(str[i][j]=='C') cnt++;
		}
	}
	ans+=cnt-solve();
	printf("%d\n",ans);
	return 0;
}
