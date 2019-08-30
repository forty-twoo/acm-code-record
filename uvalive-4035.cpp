/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-30 10:52
 * @Description: 二分 bfs
 * @Source: https://vjudge.net/problem/UVALive-4035
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
const int MAX = 1e4+10;
const int MAXN = 5e2;
const int MOD = 998244353;
int n,m,k,t;
struct Possi{
	int d;
	double p;
	bool operator<(const Possi&x)const{
		return d<x.d;
	}
}dv[MAX];
struct Node{
	int x,y;
}node[MAXN];
int dis[MAXN][MAXN],vis[MAXN];
void initdis(){
	for(int i=1;i<=t;i++){
		for(int j=1;j<=t;j++){
			dis[i][j]=abs(node[i].x-node[j].x)+abs(node[i].y-node[j].y);
		}
	}
}
int getd(int x,int y,int x1,int y1){
	return abs(x-x1)+abs(y-y1);
}
bool check(int d){
	mst(vis,0);
	queue<int> Q;
	for(int i=1;i<=t;i++){
		if(getd(node[i].x,node[i].y,0,node[i].y)<=d||getd(node[i].x,node[i].y,node[i].x,n)<=d){
			Q.push(i);vis[i]=1;
		}
	}
	while(Q.size()){
		int id=Q.front();Q.pop();
		if(getd(node[id].x,node[id].y,node[id].x,0)<=d || getd(node[id].x,node[id].y,n,node[id].y)<=d) return false;

		for(int i=1;i<=t;i++){
			if(!vis[i] && dis[id][i]<=2*d){
				Q.push(i);vis[i]=1;
			}
		}
	}
	return true;
}


int main(){
	//debug;
	int ks;scanf("%d",&ks);
	while(ks--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%lf",&dv[i].d,&dv[i].p);
		}
		int x,y;t=0;
		while(~scanf("%d",&x)&&(x!=-1)){
			scanf("%d",&y);
			node[++t].x=x,node[t].y=y;
		}
		initdis();
		sort(dv+1,dv+1+m);
		int l=1,r=m;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(check(dv[mid].d)){
				l=mid;
			} else{
				r=mid-1;
			}
		}
		double ans=0;
		for(int i=1;i<=l;i++){
			ans+=dv[i].p;
		}
		printf("%lf\n",ans);
	}
	return 0;
}
