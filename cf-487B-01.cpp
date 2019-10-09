/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-09 22:28:10
 * @Description: 单调队列预处理+单调队列优化dp(O(n)做法)
 * @Source: https://codeforces.com/contest/487/problem/B
 */

/*给你一个数组，问最少能划分成几段，每段长度至少为Len，每段中最大最小值之差不超过lim*/
#include<bits/stdc++.h>
#include <algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 10;
const ll MOD = 998244353;
int n,Len;
int lim,a[MAX],dp[MAX];
int qmax[MAX],qmin[MAX];
int Q[MAX];
int pre[MAX];
void init(){
	int tmp=-1;
	int l1=1,r1=0,l2=1,r2=0;
	for(int i=1;i<=n;i++){
		while(l1<=r1 && a[qmax[r1]]<a[i])r1--;
		while(l2<=r2 && a[qmin[r2]]>a[i])r2--;
		qmax[++r1]=i;
		qmin[++r2]=i;
		while(l1<=r1 && l2<=r2 && a[qmax[l1]]-a[qmin[l2]]>lim){
			if(qmax[l1]<qmin[l2]){
				tmp=qmax[l1];l1++;
			} else{
				tmp=qmin[l2];l2++;
			}
		}
		pre[i]=tmp+1;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	debug;

#endif // !ONLINE_JUDGE
	scanf("%d%d%d",&n,&lim,&Len);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	init();
	mst(dp,INF);
	dp[0]=0;
	int l=1,r=0;
	Q[++r]=0;
	int tmp=0;
	for(int i=1;i<=n;i++){
		while(l<=r && Q[l]<pre[i]-1){
			l++;
		}
		if(i-Q[l]>=Len && l<=r){
			dp[i]=dp[Q[l]]+1;
			Q[++r]=i;
		}
	}
	if(dp[n]==INF){
		printf("-1\n");
	} else{
		printf("%d\n",dp[n]);
	}
	return 0;
}


