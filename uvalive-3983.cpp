/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-10 01:32:57
 * @Description: 单调队列优化dp
 * @Source: https://vjudge.net/problem/UVALive-3983
 */
#include<bits/stdc++.h>
#include <algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 2e5 + 10;
const ll MOD = 998244353;
int n,C;
struct Node{
	int x,y,w;
}node[MAX];
int dp[MAX];
int sum[MAX];
int dis[MAX];
int cntw[MAX];
int Q[MAX];
void init(){
	for(int i=1;i<=n;i++){
		dis[i]=abs(node[i].x)+abs(node[i].y);
		sum[i]=abs(node[i].x-node[i-1].x)+abs(node[i].y-node[i-1].y)+sum[i-1];
		cntw[i]=node[i].w+cntw[i-1];
	}
}

int main() {
#ifndef ONLINE_JUDGE
	debug;
#endif // !ONLINE_JUDGE
	int ks;
	scanf("%d",&ks);
	while(ks--){
		scanf("%d%d",&C,&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&node[i].x,&node[i].y,&node[i].w);
		}
		init();
		int l=1,r=0;
		dp[0]=0;
		Q[++r]=0;
		for(int i=1;i<=n;i++){
			while(l<=r&&cntw[i]-cntw[Q[l]]>C)l++;

			dp[i]=(dis[i]+sum[i])-sum[Q[l]+1]+dis[Q[l]+1]+dp[Q[l]];

			//!!!注意比较的是什么
			while(l<=r && dp[Q[r]]+dis[Q[r]+1]-sum[Q[r]+1]>=dp[i]+dis[i+1]-sum[i+1])r--;
			Q[++r]=i;
		}
		printf("%d\n",dp[n]);
		if(ks>0)
			puts("");

	}
	return 0;
}

