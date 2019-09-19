
/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-19 23:29:12
 * @Description: 主席树判断是否有区间众数(并输出这个数)
 * @Source: https://www.luogu.org/problem/P3567
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
const int MAX=5e5+10;
const int MAXN=1e6+10;
const int MOD=1e9+7;
using namespace std;
int n,m;
int a[MAX],dc[MAX],tot,rt[MAX];
struct Node{
	int l,r,h;
}node[MAX];
struct ChairmanT{
	int num[MAX*20],lc[MAX*20],rc[MAX*20],cnt;
	void init(){
		cnt=0;mst(num,0);mst(lc,0);mst(lc,0);
	}
	void build(int &o,int l,int r){
		o=++cnt;lc[o]=rc[o]=num[o]=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lc[o],l,mid);
		build(rc[o],mid+1,r);
	}
	void insert(int &o,int pre,int l,int r,int x){
		o=++cnt;lc[o]=lc[pre];rc[o]=rc[pre];num[o]=num[pre]+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(x<=mid) insert(lc[o],lc[pre],l,mid,x);
		else insert(rc[o],rc[pre],mid+1,r,x);
	}
	int tms;
	int query(int o,int pre,int l,int r,int inito,int initpre){
		if(l==r){
			tms=num[o]-num[pre];
			return l;
		}
		int mid=(l+r)>>1;
		int numl=num[lc[o]]-num[lc[pre]];
		int numr=num[rc[o]]-num[rc[pre]];
		if(numl>numr) return query(lc[o],lc[pre],l,mid,inito,initpre);
		else if(numr>numl) return query(rc[o],rc[pre],mid+1,r,inito,initpre);
		else return -1;
	}

}T;
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	tot=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		dc[++tot]=a[i];
	}
	sort(dc+1,dc+1+tot);
	tot=unique(dc+1,dc+1+tot)-(dc+1);
	T.build(rt[0],1,tot);
	for(int i=1;i<=n;i++){
		int x=lower_bound(dc+1,dc+1+tot,a[i])-dc;
		T.insert(rt[i],rt[i-1],1,tot,x);
	}
	int l,r;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		int ans=T.query(rt[r],rt[l-1],1,tot,r,l-1);
		int len=r-l+1,lim;
		if(len%2==0)  lim=len/2+1;
		else lim=(len+1)/2;

		if(ans!=-1 && T.tms>=lim) {
			printf("%d\n",dc[ans]);
		} else{
			printf("0\n");
		}
	}
	return 0;
}
