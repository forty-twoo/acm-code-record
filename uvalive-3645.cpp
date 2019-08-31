/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-31 19:23
 * @Description: 拆点建图 最大流
 * @Source: https://vjudge.net/problem/UVALive-3645
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
const int MAXN = 3e5+100;
const int MOD = 998244353;
int head[MAXN],dis[MAXN],tot=0;
struct Edge{
	int u,v;
	ll w;
	int nxt;
}edge[MAXN];
int n,m,S,T;
map<string,int> mp;
string city;
char t1[10],t2[10];
char etme[10];

void addedge(int u,int v,ll w){
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
}


struct Flight{
	int fr,to;
	int tms,tme;
	ll cap;
}flg[6000];

int main(){
	//debug;
	while(~scanf("%d",&n)){
		int cnt=0;tot=1;
		mp.clear();
		mst(head,0);
		cin>>city;mp[city]=++cnt;
		cin>>city;mp[city]=++cnt;
		scanf("%s",etme+1);
		int endt=((etme[1]-'0')*10+(etme[2]-'0'))*60+(etme[3]-'0')*10+(etme[4]-'0');
		scanf("%d",&m);
		S=2*m+1;T=2*m+2;
		string fc,tc;ll cap;
		for(int i=1;i<=m;i++){
			cin>>fc>>tc;
			if(!mp[fc]) mp[fc]=++cnt;
			if(!mp[tc]) mp[tc]=++cnt;
			scanf("%lld",&cap);
			scanf("%s%s",t1+1,t2+1);
			int ff=((t1[1]-'0')*10+(t1[2]-'0'))*60+(t1[3]-'0')*10+(t1[4]-'0');
			int tt=((t2[1]-'0')*10+(t2[2]-'0'))*60+(t2[3]-'0')*10+(t2[4]-'0');
			flg[i]={mp[fc],mp[tc],ff,tt,cap};
		}
		for(int i=1;i<=m;i++){
			addedge(i,i+m,flg[i].cap);
			if(flg[i].fr==1) addedge(S,i,INF);
			if(flg[i].to==2 && endt>=flg[i].tme) addedge(i+m,T,INF);
		}
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				if(i==j) continue;
				if(flg[i].to==flg[j].fr && flg[i].tme+30<=flg[j].tms) addedge(i+m,j,INF);
			}
		}
		ll maxflow=0,flow=0;
		while(bfs())
			while(flow = dinic(S,INF)) maxflow += flow;
		printf("%lld\n",maxflow);

	}
	return 0;
}
