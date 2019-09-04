/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-09-05 00:56
 * @Description: 二分图最大匹配+二分
 * @Source: https://vjudge.net/problem/UVA-1221
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
const int MAX = 3e2;
const int MAXN = 2e5+100;
const int MOD =1e9+9;
int n,m,head[MAXN];
struct Node{
	ll has;
	ll rate;
};
Node peo[MAX],alen[MAX];
ll gra[MAX][MAX];
struct Edge{
	int u,v,nxt;
}edge[MAXN];
int tot=0;
void addedge(int u,int v){
	edge[++tot]={u,v,head[u]};
	head[u]=tot;
	edge[++tot]={v,u,head[v]};
	head[v]=tot;
}
int match[2*MAX],vis[2*MAX];
bool dfs(int x){
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].v;
		if(vis[to]) continue;
		vis[to]=1;
		if(!match[to] || dfs(match[to])){
			match[to]=x;
			return true;
		}
	}
	return false;
}
bool check(ll lim){
	tot=0;mst(head,0);mst(match,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ll tm=gra[i][j];if(tm>lim) continue;
			if(peo[i].rate<=alen[j].rate){
				ll a=tm*alen[j].rate+alen[j].has;
				ll p=peo[i].has;
				if(p>=a) addedge(i,j+n);
			} else{
				ll d=lim-tm;
				ll a=lim*alen[j].rate+alen[j].has;
				ll p=d*peo[i].rate+peo[i].has;
				if(p>=a) addedge(i,j+n);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		mst(vis,0);
		if(dfs(i)) ans++;
	}
	if(ans>=m) return true;
	else return false;
}
int main(){
	//debug;
	while(~scanf("%d%d",&n,&m)){
		if(n==0 || m==0) break;
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&peo[i].has,&peo[i].rate);
		}
		for(int i=1;i<=m;i++){
			scanf("%lld%lld",&alen[i].has,&alen[i].rate);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%lld",&gra[i][j]);
			}
		}
		if(n<m){
			printf("IMPOSSIBLE\n");continue;
		}
		ll l=1,r=1e9;
		while(l<r){
			ll mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		if(l==1e9 && !check(l))
			printf("IMPOSSIBLE\n");
		else printf("%lld\n",l);

	}
	return 0;
}
