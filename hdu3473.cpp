/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-27 21:18:13
 * @Description: 主席树找中位数及区间前/后半部分的值
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=3473
 */
//！！！！！！本份代码由于MLE无法通过，正解为划分树
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
const int MAX=1e5+10;
const int MAXN=2e6+10;
const int MOD=1e9+7;
using namespace std;
int n;
ll a[MAX],dc[MAX],tot,spre[MAX];
int rt[MAX];
struct Chairman{
	int cnt,lc[MAX*20],rc[MAX*20],num[MAX*20];
	ll sum[MAX*20];
	inline void build(int &o,int l,int r){
		o=++cnt;num[o]=lc[o]=rc[o]=sum[o]=0;
		if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		build(lc[o],l,mid);build(rc[o],mid+1,r);
	}
	inline void insert(int &o,int pre,int l,int r,int x){
		o=++cnt;lc[o]=lc[pre],rc[o]=rc[pre],num[o]=num[pre]+1,sum[o]=sum[pre]+dc[x];
		int mid=(l+r)>>1;
		if(l==r)return;
		if(x<=mid)insert(lc[o],lc[pre],l,mid,x);
		else insert(rc[o],rc[pre],mid+1,r,x);
	}
	ll val;
	int has;
	int lstnum;
	inline int queryx(int o,int pre,int l,int r,int x){
		if(l==r){
			has=num[o]-num[pre];
			return l;
		}
		int mid=(l+r)>>1;
		if(num[lc[o]]-num[lc[pre]]>=x){
			val+=sum[rc[o]]-sum[rc[pre]];
			lstnum+=num[rc[o]]-num[rc[pre]];
			return queryx(lc[o],lc[pre],l,mid,x);
		} else {
			return queryx(rc[o],rc[pre],mid+1,r,x-(num[lc[o]]-num[lc[pre]]));
		}
	}
}T;

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int ks;scanf("%d",&ks);
	int cks=0;
	while(ks--){
		tot=0;
		cks++;
		printf("Case #%d:\n",cks);
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			spre[i]=spre[i-1]+a[i];
			dc[++tot]=a[i];
		}
		sort(dc+1,dc+1+tot);
		tot=unique(dc+1,dc+1+tot)-(dc+1);
		T.cnt=0;
		T.build(rt[0],1,tot);
		for(int i=1;i<=n;i++){
			int x=lower_bound(dc+1,dc+1+tot,a[i])-dc;
			T.insert(rt[i],rt[i-1],1,tot,x);
		}
		int m,l,r;
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&l,&r);
			l++,r++;
			T.val=0;T.has=0;T.lstnum=0;int k;
			ll hou,pre,ans;
			ll all=spre[r]-spre[l-1];
			if((r-l+1)%2==1){
				k=(r-l+1)/2+1;
				int kp=T.queryx(rt[r],rt[l-1],1,tot,k);
				hou=T.val;
				if(T.lstnum!=k-1){
					hou+=(ll)(k-1-T.lstnum)*dc[kp];
				}
				pre=all-hou-dc[kp];
			} else{
				k=(r-l+1)/2;
				int kp=T.queryx(rt[r],rt[l-1],1,tot,k);
				hou=T.val;
				if(T.lstnum!=k){
					hou+=(ll)(k-T.lstnum)*dc[kp];
				}
				pre=all-hou;
			}
			ans=hou-pre;
			printf("%lld\n",ans);
		}
		puts("");

	}
	return 0;
}
