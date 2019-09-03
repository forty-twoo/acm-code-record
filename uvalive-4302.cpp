/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-09-03 11:05
 * @Description: 树形dp
 * @Source: https://vjudge.net/problem/UVALive-4302
 */

#include<bits/stdc++.h>
#include <unordered_map>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
using namespace std;
const int MAX =2e5+100;
const int MAXN = 2e6;
const int MOD =1e9+9;
const int Lim=1e6;
int m,tot=0,head[MAX<<2];
struct Edge{
	int u,v;ll w;int nxt;
}edge[MAX<<2];
void addedge(int u,int v,ll w){
	edge[++tot]={u,v,w,head[u]};
	head[u]=tot;
}
ll dp[MAX];
ll ans=-INF;
ll dfs(int u,int fa){
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		ll w=edge[i].w;
		if(v==fa) continue;
		ll curs=dfs(v,u);
		if(curs+w>0){
			dp[u]+=(curs+w);
			ans=max(ans,dp[u]);
		}
	}
	ans=max(ans,dp[u]);
	return dp[u];
}

int main(){
	//debug;
	int spoint;
	while(~scanf("%d",&m)&&m){
		ans=-INF;
		int u,v;ll w;tot=0;
		mst(dp,0);mst(head,0);
		for(int i=1;i<=m;i++){
			scanf("%d%d%lld",&u,&v,&w);
			spoint=u;
			addedge(u,v,w);
			addedge(v,u,w);
		}
		dfs(spoint,0);
		printf("%lld\n",ans);
	}
	return 0;
}
