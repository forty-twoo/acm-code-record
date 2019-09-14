/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-14 19:50:20
 * @Description: 树形dp+计数
 * @Source: https://nanti.jisuanke.com/t/41403 沈阳网络赛D
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
const int MAX=1e4+100;
const int MAXN=5e4+10;
const int MOD=1e9+7;
using namespace std;
struct Edge{
	int u,v,w,nxt;
}edge[MAX<<1];
int tot,head[MAX<<1];
int n;
ll f[MAX][3],ans[4];
ll cnt[MAX][3];
ll dis[MAX][3];
void addedge(int u,int v,int w){
	edge[++tot].u=u;
	edge[tot].v=v;
	edge[tot].w=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void dfs(int x,int fa){
	cnt[x][0]=1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].v;
		int w=edge[i].w;
		if(v==fa) continue;
		dfs(v,x);
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				int t=(w+j+k)%3;
				ans[t]=(ans[t]+cnt[x][j]*cnt[v][k]%MOD*(ll)w*2ll%MOD)%MOD;
				ans[t]=(ans[t]+cnt[x][j]*dis[v][k]%MOD*2ll%MOD)%MOD;
				ans[t]=(ans[t]+cnt[v][k]*dis[x][j]%MOD*2ll%MOD)%MOD;
			}
		}
		for(int j=0;j<3;j++){
			int t=(w+j)%3;
			if(cnt[v][j]!=0){
				dis[x][t]=(dis[x][t]+(dis[v][j]+cnt[v][j]*w))%MOD;
			}
			cnt[x][t]=(cnt[x][t]+cnt[v][j])%MOD;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	while(~scanf("%d",&n)){
		tot=0;
		mst(head,0);
		mst(dis,0);
		mst(ans,0);
		mst(cnt,0);
		int u,v,w;
		for(int i=1;i<n;i++){
			scanf("%d%d%d",&u,&v,&w);
			u++;v++;
			addedge(u,v,w);
			addedge(v,u,w);
		}
		dfs(1,0);
		printf("%lld %lld %lld\n",ans[0],ans[1],ans[2]);

	}
	return 0;
}

