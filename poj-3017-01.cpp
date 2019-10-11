/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-11 13:29:15
 * @Description: 单调栈+线段树优化dp
 * @Source: https://vjudge.net/problem/POJ-3017#author=634579757
 */
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define INF 0x3f3f3f3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 10;
const ll MOD = 998244353;
int n, Q[MAX],l,r;
ll lim,a[MAX],dp[MAX],sum[MAX];
int sta[MAX],top,pre[MAX];
void init(){
    sta[++top]=1;
    pre[1]=1;
    for(int i=2;i<=n;i++){
        while(a[sta[top]]<=a[i] && top ) top--;
		pre[i]=sta[top]+1;
        sta[++top]=i;
    }
}

struct SEGT{
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
#define lc rt<<1
#define rc rt<<1|1

	int lazy[MAX<<2];
	ll dpv[MAX<<2],sv[MAX<<2],minv[MAX<<2];
	void pushup(int rt){
	    dpv[rt]=min(dpv[lc],dpv[rc]);
	    sv[rt]=max(sv[lc],sv[rc]);
		minv[rt]=min(minv[lc],minv[rc]);
	}
	void pushdown(int rt){
		if(lazy[rt]){
            sv[lc]=sv[rt];
            sv[rc]=sv[rt];
            minv[lc]=dpv[lc]+sv[lc];
            minv[rc]=dpv[rc]+sv[rc];
			lazy[lc]=lazy[rc]=1;
			lazy[rt]=0;
		}
	}
	void build(int rt,int l,int r){
		dpv[rt]=minv[rt]=INF;
		if(l==r) {
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
	}
	void changedp(int rt,int l,int r,int x,ll v){
		if(l==r){
		    dpv[rt]=v;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(rt);
		if(x<=mid) changedp(lson,x,v);
		else changedp(rson,x,v);
		pushup(rt);
	}
	void changeV(int rt,int l,int r,int L,int R,ll v){
	    if(L<=l&&r<=R){
	        sv[rt]=v;
	        minv[rt]=v+dpv[rt];
	        lazy[rt]=1;
	        return;
	    }
        int mid=(l+r)>>1;
        pushdown(rt);
        if(L<=mid) changeV(lson,L,R,v);
        if(R>mid) changeV(rson,L,R,v);
        pushup(rt);
	}
	ll query(int rt,int l,int r,int L,int R){
		ll ans=INF;
		if(L<=l && r<=R){
		    return minv[rt];
		}
		pushdown(rt);
		int mid=(l+r)>>1;
		if(L<=mid) ans=min(ans,query(lson,L,R));
		if(R>mid) ans=min(ans,query(rson,L,R));
		return ans;
	}
}T;


int main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.txt","r",stdin);
#endif
    scanf("%d%lld",&n,&lim);
	bool flg=true;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        if(a[i]>lim) flg=false;
        sum[i]=sum[i-1]+a[i];
    }
    if(!flg){
    	puts("-1");
    	return 0;
	}
    init();
    l=1,r=0;
    Q[++r]=0;
    T.build(1,1,n);
    T.changedp(1,1,n,1,0);
    for(int i=1;i<=n;i++){
        while(l<=r && sum[i]-sum[Q[l]]>lim) l++;
        int p=max(pre[i],Q[l]+1);
        T.changeV(1,1,n,p,i,a[i]);
        int ans=T.query(1,1,n,Q[l]+1,i);
        dp[i]=ans;
        T.changedp(1,1,n,i+1,dp[i]);
        Q[++r]=i;
    }
	printf("%lld\n",dp[n]);
    
    return 0;
}
