/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-31 19:12
 * @Description: 树形dp LCA 倍增
 * @Source: https://vjudge.net/problem/URAL-1752
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
const int MAX =2e4+10;
vector<int> G[MAX];
int n,Q;
int ch[MAX][3];
int dp[MAX][3]; //down-> 0:max 1:second 
int f[MAX][2];  //up-> 0:max
int cun[MAX][2];
int fcun[MAX][2];
int dep[MAX],fath[MAX];
int F[MAX][30];
void get_dep(int x,int fa){
	fath[x]=fa;dep[x]=dep[fa]+1;
	for(auto y:G[x]){
		if(y==fa) continue;
		get_dep(y,x);
	}
}
void init(){
	for(int i=1;i<=n;i++){
		F[i][0]=fath[i];
	}
	for(int i=1;i<=20;i++){
		for(int j=1;j<=n;j++){
			if(dep[F[j][i-1]]<=0) continue;
			if(dep[F[F[j][i-1]][i-1]]<=0) continue;
			F[j][i]=F[F[j][i-1]][i-1];
		}
	}
}

int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--){
		if(dep[F[x][i]]>=dep[y]) x=F[x][i];
		if(x==y) return x;
	}
	for(int i=20;i>=0;i--){
		if(F[x][i]!=F[y][i]){
			x=F[x][i];y=F[y][i];
		}
	}
	return F[x][0];
}


void dfs1(int x,int fa){
	cun[x][0]=x;
	for(auto y: G[x]){
		if(y==fa) continue;
		dfs1(y,x);
		if(dp[x][0]<=dp[y][0]+1){
			dp[x][1]=dp[x][0];
			dp[x][0]=dp[y][0]+1;
			ch[x][1]=ch[x][0];
			ch[x][0]=y;
			cun[x][1]=cun[x][0];
			cun[x][0]=cun[y][0];
		} else if(dp[x][1]<dp[y][0]+1){
			dp[x][1]=dp[y][0]+1;
			ch[x][1]=y;
			cun[x][1]=cun[y][0];
		}
	}
}

void dfs2(int x,int fa){
	for(auto y: G[x]){
		if(y==fa) continue;
		if(ch[x][0]!=y){
			if(dp[x][0]>f[x][0]){
				f[y][0]=dp[x][0]+1;
				fcun[y][0]=cun[x][0];
			} else{
				f[y][0]=f[x][0]+1;
				fcun[y][0]=fcun[x][0];

			}

		} else{
			if(dp[x][1]>f[x][0]){
				f[y][0]=dp[x][1]+1;
				fcun[y][0]=cun[x][1];
			} else{
				f[y][0]=f[x][0]+1;
				fcun[y][0]=fcun[x][0];
			}
		}
		dfs2(y,x);
	}
}
int get_up_point(int x,int d){
	int y=x;
	int desd=dep[x]-d;
	for(int i=20;i>=0;i--){
		if(dep[x]==desd) return x;
		if(dep[F[x][i]]>=desd){
			x=F[x][i];
		}
	}
	if(dep[x]==desd) return x;
}

int main(){
	//debug;
	scanf("%d%d",&n,&Q);
	int u,v,d;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0);
	get_dep(1,0);
	init();
	int rt,w,len1,len2;
	for(int i=1;i<=Q;i++){
		scanf("%d%d",&v,&d);
		int maxx=max(f[v][0],dp[v][0]);
		if(d>maxx){
			printf("0\n");
		} else{
			int w;
			if(dp[v][0]>=d){
				w=cun[v][0];
				maxx=dp[v][0]; //注意maxx
			} else{
				w=fcun[v][0];
				maxx=f[v][0];
			}
			rt=LCA(v,w);
			len1=dep[v]-dep[rt];
			len2=dep[w]-dep[rt];
			int ans;
			if(len1>=d){
				ans=get_up_point(v,d);
			} else {
				ans=get_up_point(w,maxx-d);
			}
			printf("%d\n",ans);
		}
	}

	return 0;
}
