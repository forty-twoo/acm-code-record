/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-04 23:18:13
 * @Description: tarjan找桥(无向图边双连通分量)
 * @Source: https://codeforces.com/contest/701/problem/F
 */

/*
给一个n个点m条边的无向图，每条边都有边权，有重边，可最多删除2条边使得给定的S，T两点不连通，问删除的边的
最小权值和是多少，并输出该权值和下的删边方案。
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
const int MAX=1e3+10;
const int MAXN=6e4+100;
const int MOD=1e9+7;
using namespace std;
int n,m,S,T;
struct Node{
	int id,u,v,w;
}cun[MAXN];
Node cun2[MAXN];int t2;
struct Edge{
	int u,v,w,nxt,id;
}edge[MAXN];
int ansv;
vector<int> vv;
int head[MAX],tot,dfn[MAX],low[MAX],num, ungo[MAXN],spl[MAXN];
int tans;
void add(int u,int v,int w,int id){
	edge[++tot]={u,v,w,head[u],id};head[u]=tot;
}
int vis[MAX],in[MAXN];

/*
先dfs一遍找到一条S到T的路径，如果存在答案，答案中至少一条边在这条路径上，因此把枚举一条边m的复杂度
降低到n
*/
bool check(int u,int ff){
	if(u==T){
		return 1;
	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff || vis[v])continue;
		vis[v]=1;
		if(check(v,u)){
			cun2[++t2]=cun[edge[i].id];
			return 1;
		}
	}
	return 0;
}
void dfs(int x,int ide){
 
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].v;
		int w=edge[i].w;
		int id=edge[i].id;
		if(!dfn[y]){
			dfs(y,i);
			low[x]=min(low[x],low[y]);
			int yy=y,xx=x;
			if(low[y]>dfn[x]){

				//从S到T的桥
				if(dfn[T]>=dfn[y]){
					spl[id]=1;
					if(w<ansv){
						ansv=w;
						vv.clear();
						vv.pb(id);
					}
				}
			}
		}else{
			//前向星会存一对边，判断是否为反边，这段代码可以处理重边问题
			if(i!=(ide^1))
				low[x]=min(low[x],dfn[y]);
		}
	}
}
void dfs2(int x,int ide,int val,int iid){
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].v;
		int w=edge[i].w;
		int id=edge[i].id;
		if(ungo[id])continue; //被枚举删除的那条边
		if(!dfn[y]){
			dfs2(y,i,val,iid);
			low[x]=min(low[x],low[y]);
			int yy=y,xx=x;
			if(low[y]>dfn[x]){
				if(dfn[T]>=dfn[y]){
					if(w+val<ansv){
						ansv=w+val;
						vv.clear();
						if(id>iid)swap(iid,id);
						vv.pb(id);vv.pb(iid);
					}
				}
			}
		}else{
			if(i!=(ide^1))
				low[x]=min(low[x],dfn[y]);
		}
	}
}
 
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	scanf("%d%d",&S,&T);
	tot=1;
	ansv=2e9+10;
	int u,v,w;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		cun[i]={i,u,v,w};
		add(u,v,w,i);add(v,u,w,i);
	}
	if(!check(S,0)){
		printf("0\n0\n");
		return 0;
	}
	num=0;
	//只删一条边
	dfs(S,0);
	//删两条边
	for(int i=1;i<=t2;i++){
		if(spl[cun2[i].id])continue;
		ungo[cun2[i].id]=1;
		mst(low,0);mst(dfn,0);num=0;
		dfs2(S,0,cun2[i].w,cun2[i].id);
		ungo[cun2[i].id]=0;
	}
	if(ansv==2000000010){
		printf("-1\n");
		return 0;
	}
	printf("%d\n",ansv);
	printf("%d\n",vv.size());
	for(auto x:vv){
		printf("%d ",x);
	}
	puts("");
	return 0;
}
 
