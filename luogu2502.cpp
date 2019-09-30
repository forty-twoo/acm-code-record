/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-01 00:43:22
 * @Description: 并查集+枚举+排序
 * @Source: https://www.luogu.org/problem/P2502
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
const int MAX=5e2+10;
const int MAXN=5e3+10;
const int MOD=1e9+7;
using namespace std;
struct Edge{
	int u,v,w;
	bool operator<(const Edge&x)const{
		return w<x.w;
	}
}edge[MAXN];
int fa[MAX];
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int n,m,u,v,w,S,T;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		edge[i]={u,v,w};
		int fu=find(u),fv=find(v);
		if(fu!=fv)fa[fv]=fu;
	}
	scanf("%d%d",&S,&T);
	if(find(S)!=find(T) ){
		puts("IMPOSSIBLE");
		return 0;
	}
	sort(edge+1,edge+1+m);
	for(int i=1;i<=n;i++)fa[i]=i;
	double ans=INF;
	int a,b;
	for(int i=1;i<=m;i++){
		int fu=find(edge[i].u),fv=find(edge[i].v);
		if(fu!=fv)fa[fv]=fu;
		if(find(S)==find(T)){
			a=b=edge[i].w;
			break;
		}
		for(int j=i+1;j<=m;j++){
			int fu=find(edge[j].u),fv=find(edge[j].v);
			if(fu!=fv)fa[fv]=fu;
			if(find(S)==find(T)){
				if((double)edge[j].w/(double)edge[i].w<ans){
					ans=(double)edge[j].w/(double)edge[i].w;
					a=edge[j].w;b=edge[i].w;
				}
			}
		}
		for(int i=1;i<=n;i++)fa[i]=i;
	}
	int x=gcd(a,b);
	if(b/x==1)printf("%d\n",a/b);
	else printf("%d/%d\n",a/x,b/x);
	return 0;
}
