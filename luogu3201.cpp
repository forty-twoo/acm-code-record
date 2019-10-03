/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-03 10:51:09
 * @Description: set启发式合并
 * @Source: https://www.luogu.org/problem/P3201
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
set<int> S[MAXN];
int n,m,ans=0;
int a[MAX],fa[MAXN],in[MAX];
void unionset(int x,int y){
	for(auto i:S[x]){
		in[i]=1;
	}
	for(auto v:S[x]){
		if(v!=1&&a[v-1]==y && !in[v-1])ans--;
		if(v<n&&a[v+1]==y && !in[v+1])ans--;
		S[y].insert(v);
	}
	for(auto v:S[x]){
		a[v]=y;
		in[v]=0;
	}
	S[x].clear();  //注意！
}
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	for(int i=1;i<=MAXN;i++)fa[i]=i;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]!=a[i-1]){
			ans++;
		}
		S[a[i]].insert(i);
	}
	int op;
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==2){
			printf("%d\n",ans);
		} else{
			int s,t;
			scanf("%d%d",&s,&t);
			if(s==t)continue;
			if(S[fa[s]].size()>S[fa[t]].size()) swap(fa[s],fa[t]);
			unionset(fa[s],fa[t]);
		}
	}
	return 0;
}
