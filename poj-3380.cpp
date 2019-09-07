/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-07 10:13:42
 * @Description: 贪心 
 * @Source: https://vjudge.net/problem/POJ-3380
 */
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
using namespace std;
const int MAX = 1e4+100;
const int MAXN =8e2+20;
const int MOD =1e9+9;
int n,k,sh,sc;
int has[MAX];
int dfn[MAX];
int cnt=0;
vector<int> G[MAX];
struct Edge{
	ll u,v,w;
	ll val;
	int id;
}edge[MAX];
bool cmp(const Edge&x,const Edge&y){
		return x.val>y.val;
}

int dfs(int x,int ff){
	dfn[x]=++cnt;
	has[x]=1;
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		if(y==ff) continue;
		int t=dfs(y,x);
		has[x]+=t;
	}
	return has[x];
}

int main(){
	//debug;
	scanf("%d%d%d%d",&n,&k,&sh,&sc);
	ll u,v,w;
	for(int i=1;i<n;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		edge[i].id=i,edge[i].u=u,edge[i].v=v,edge[i].w=w;
		G[u].push_back(v);G[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<n;i++){
		u=edge[i].u;
		v=edge[i].v;
		w=edge[i].w;
		if(dfn[u]<dfn[v]) swap(u,v);
		edge[i].val=(ll)has[u]*(ll)(n-has[u])*w;
	}
	sort(edge+1,edge+n,cmp);
	if(sc>sh){
		for(int i=1;i<=k;i++){
			printf("%d ",edge[i].id);
		}
	}else{
		for(int i=n-1;i>=n-k;i--){
			printf("%d ",edge[i].id);
		}
	}
	puts("");
	return 0;
}
