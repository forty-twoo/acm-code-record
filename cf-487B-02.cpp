/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-09 22:30:08
 * @Description: ST表预处理+线段树优化dp(O(nlogn)做法)
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
int stmax[MAX][25],stmin[MAX][25];
int Querymax(int l,int r){
	int k=log2(r-l+1);
	return max(stmax[l][k],stmax[r-(1<<k)+1][k]);
}
int Querymin(int l,int r){
	int k=log2(r-l+1);
	return min(stmin[l][k],stmin[r-(1<<k)+1][k]);
}
 
void init(){
	for(int i=1;i<=n;i++)
		stmax[i][0]=stmin[i][0]=a[i];
 
	for(int j=1;j<=21;j++){
		for(int i=1;i+(1<<j)-1<=n; i++){
			stmin[i][j] = min(stmin[i][j - 1],stmin[i + (1 << (j - 1))][j - 1]);
			stmax[i][j] = max(stmax[i][j - 1],stmax[i + (1 << (j - 1))][j - 1]);
		}
	}
}
struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	int minv[MAX<<2];
	void pushup(int rt){
		minv[rt]=min(minv[lc],minv[rc]);
	}
	void build(int rt,int l,int r){
		minv[rt]=INF;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lson);build(rson);
	}
	void change(int rt,int l,int r,int x,int v){
		if(l==r){
			minv[rt]=v;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)change(lson,x,v);
		else change(rson,x,v);
		pushup(rt);
	}
	int query(int rt,int l,int r,int L,int R){
		int minn=INF;
		if(L<=l && r<=R){
			return minv[rt];
		}
		int mid=(l+r)>>1;
		if(L<=mid)minn=min(query(lson,L,R),minn);
		if(R>mid) minn=min(query(rson,L,R),minn);
		return minn;
	}
}T;
 
 
 
int main() {
#ifndef ONLINE_JUDGE
	debug;
 
#endif // !ONLINE_JUDGE
	scanf("%d%d%d",&n,&lim,&Len);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	init();
	T.build(1,1,n);
	T.change(1,1,n,1,0);
 
	mst(dp,INF);
	for(int i=1;i<=n;i++){
		int l=1,r=i;
		while(l<r){
			int mid=(l+r)>>1;
			if(Querymax(mid,i)-Querymin(mid,i)>lim){
				l=mid+1;
			} else{
				r=mid;
			}
		}
		if(i-Len+1>=l){
			int x=T.query(1,1,n,l,i-Len+1);
			if(x==INF)continue;
			dp[i]=x+1;
			T.change(1,1,n,i+1,dp[i]);
 
		}
	}
	if(dp[n]==INF){
		printf("-1\n");
	} else{
		printf("%d\n",dp[n]);
	}
	return 0;
}
