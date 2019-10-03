/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-03 14:02:19
 * @Description: 大根堆启发式合并(使用STL)
 * @Source: https://www.luogu.org/problem/P1552
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
int n;
ll m;
vector<int> G[MAX];
ll ld[MAX],cost[MAX];
ll sum[MAX];
int sz[MAX];
prique<ll> Q[MAX];
struct Edge{
	int u,v,nxt;
}edge[MAXN];
int fa[MAX],head[MAX];
ll ans=0;
int tot;
void add(int u,int v){
	edge[++tot].u=u;edge[tot].v=v;
	edge[tot].nxt=head[u];head[u]=tot;

}

void dfs(int u){
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		dfs(v);
		if(Q[fa[v]].size()>Q[fa[u]].size()){
			swap(fa[v],fa[u]);
		}
		while(Q[fa[v]].size()){
			ll cur=Q[fa[v]].top();
			Q[fa[u]].push(cur);
			Q[fa[v]].pop();
			sum[fa[u]]+=cur;
			while(sum[fa[u]]>m){
				ll mv=Q[fa[u]].top();
				Q[fa[u]].pop();
				sum[fa[u]]-=mv;
			}
		}
		ans=max(ans,ld[u]*(ll)Q[fa[u]].size());
	}
}


int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%lld",&n,&m);
	for(int i=2;i<=n+1;i++){
		int f;
		scanf("%d%lld%lld",&f,&cost[i],&ld[i]);
		f++;
		add(f,i);
	}
	fa[1]=1;
	for(int i=2;i<=n+1;i++){
		fa[i]=i;
		if(cost[i]<=m){
			sum[i]=cost[i];
			Q[i].push(cost[i]);
			ans=max(ans,ld[i]);
		}
	}
	for(int i=head[1];i;i=edge[i].nxt){
		int v=edge[i].v;
		dfs(v);
	}
	printf("%lld\n",ans);
	return 0;
}
