/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-16 20:52:28
 * @Description: 主席树
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6278
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
const int MAX=1e5+100;
const int MAXN=200;
const int MOD=1e9+7;
using namespace std; 
int rt[MAX],a[MAX];
struct ChairmanTree{
	int num[MAX*20],cnt=0,lc[MAX*20],rc[MAX*20];
	inline void build(int &o,int l,int r){
		o=++cnt;num[o]=lc[o]=rc[o]=0;
		if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		build(lc[o],l,mid);build(rc[o],mid+1,r);
	}
	inline void insert(int &o,int pre,int l,int r,int x){
		o=++cnt;lc[o]=lc[pre],rc[o]=rc[pre],num[o]=num[pre]+1;
		int mid=(l+r)>>1;
		if(l==r)return;
		if(x<=mid)insert(lc[o],lc[pre],l,mid,x);
		else insert(rc[o],rc[pre],mid+1,r,x);
	}
	inline int query(int o,int pre,int l,int r,int L,int R){
		int ans=0;
		if((L<=l && r<=R)){
			return num[o]-num[pre];
		}
		int mid=(l+r)>>1;
		if(L<=mid) ans+=query(lc[o],lc[pre],l,mid,L,R);
		if(R>mid) ans+=query(rc[o],rc[pre],mid+1,r,L,R);
		return ans;
	}
}T;
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int n,Q;
	while(~scanf("%d%d",&n,&Q)){
		T.cnt=0;
		T.build(rt[0],1,n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			T.insert(rt[i],rt[i-1],1,n,a[i]);
		}
		int lb,rb;
		while(Q--){
			scanf("%d%d",&lb,&rb);
			int l=1,r=rb-lb+1;
			int len=rb-lb+1;
			while(l<r){
				int mid=(l+r+1)>>1;
				int num=T.query(rt[rb],rt[lb-1],1,n,mid,n);
				if(num>=mid) l=mid;
				else r=mid-1;
			}
			printf("%d\n",l);
		}
	}
	return 0;
}
