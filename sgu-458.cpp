/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-09-03 03:46
 * @Description: 线段树优化dp
 * @Source: http://codeforces.com/problemsets/acmsguru/problem/99999/458
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
const int MAX =2e5;
const int MAXN = 2e6;
const int MOD =1e9+9;
const int Lim=1e6;
int n;
int a[MAX];
int usee[MAX];
int dp[MAX];
vector<int> V;
void solve(int p,int n){
	if(dp[p]==1){
		return;
	}
	for(int i=n;i>=1;i--){
		if(dp[i]==dp[p]-1 && a[i]==usee[p]){
			V.push_back(i);
			return solve(i,i-1);
		}
	}
}

struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,m
#define rson rc,m+1,r

	int val[MAXN<<1],pos[MAXN<<1];
	void pushup(int rt){
		if(val[lc]<val[rc]){
			pos[rt]=pos[rc];
		} else{
			pos[rt]=pos[lc];
		}
		val[rt]=max(val[lc],val[rc]);
	}
	void build(int rt,int l,int r){
		if(l==r){
			val[rt]=pos[rt]=0;
			return;
		}
		int m=(l+r)>>1;
		build(lson);build(rson);
		val[rt]=pos[rt]=0;
	}
	void insert(int rt,int l,int r,int x,int v){
		if(l==r){
			val[rt]=v;
			pos[rt]=x;
			return;
		}
		int m=(l+r)>>1;
		if(x<=m) insert(lson,x,v);
		else insert(rson,x,v);
		pushup(rt);
	}
	int maxx=0,poss;
	void query(int rt,int l,int r,int L,int R){
		if(L<=l && r<=R){
			if(maxx<val[rt]){
				maxx=val[rt];
				poss=pos[rt];
			}
			return;
		}
		int m=(l+r)>>1;
		if(L<=m) query(lson,L,R);
		if(R>m) query(rson,L,R);
	}
}T;

int main(){
	//debug;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	T.build(1,0,Lim);
	for(int i=1;i<=n;i++){
		int L,R,ans=-INF;
		L=0,R=a[i]-2;
		T.maxx=-INF;
		if(L<=R){
			T.query(1,0,Lim,L,R);
			if(T.maxx>ans){
				ans=T.maxx;
				usee[i]=T.poss;
			}
		}
		L=a[i]+2,R=1e6;
		if(L<=R){
			T.query(1,0,Lim,L,R);
			if(T.maxx>ans){
				ans=T.maxx;
				usee[i]=T.poss;
			}
		}
		L=a[i],R=a[i];
		T.query(1,0,Lim,L,R);
		if(T.maxx>ans){
			ans=T.maxx;
			usee[i]=T.poss;
		}
		dp[i]=ans+1;
		if(dp[i]==1) usee[i]=i;
		T.insert(1,0,Lim,a[i],dp[i]);
	}
	int maxx=0,p;
	for(int i=1;i<=n;i++){
		if(dp[i]>maxx){
			maxx=dp[i];
			p=i;
		}
	}
	printf("%d\n",n-maxx);
	V.push_back(p);
	solve(p,p-1);
	for(int i=V.size()-1;i>=0;i--){
		printf("%d ",a[V[i]]);
	}
	printf("\n");
	return 0;
}
