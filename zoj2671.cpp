/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-29 18:24:19
 * @Description: 线段树维护矩阵乘法
 * @Source: https://zoj.pintia.cn/problem-sets/91827364500/problems/91827366170
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
const int MAX=3e4+10;
const int MOD=1e9+7;
using namespace std;
int n,m,Q;
struct mat{
	int a[3][3];
};
int lim;
mat Mat[MAX];
mat cun[MAX<<2];
mat matmul(mat A,mat B){
	mat ans;
	mst(ans.a,0);
	for(int i=1;i<=2;i++){
		for(int k=1;k<=2;k++){
			for(int j=1;j<=2;j++){
				ans.a[i][j]=(ans.a[i][j]+A.a[i][k]*B.a[k][j]%lim)%lim;
			}
		}
	}
	return ans;
}

struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	void pushup(int rt){
		cun[rt]=matmul(cun[lc],cun[rc]);
	}
	void build(int rt,int l,int r){
		if(l==r){
			cun[rt]=Mat[l];
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	mat query(int rt,int l,int r,int L,int R){
		mat ans;mst(ans.a,0);
		for(int i=1;i<=2;i++)ans.a[i][i]=1;
		if(L<=l && r<=R){
			ans=matmul(ans,cun[rt]);
			return ans;
		}
		int mid=(l+r)>>1;
		if(L<=mid) ans=matmul(ans,query(lson,L,R));
		if(R>mid) ans=matmul(ans,query(rson,L,R));
		return ans;
	}
}T;

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	while(~scanf("%d%d%d",&lim,&n,&Q)){
		mst(Mat,0);
		for(int t=1;t<=n;t++){
			for(int i=1;i<=2;i++){
				for(int j=1;j<=2;j++){
					scanf("%d",&Mat[t].a[i][j]);
					Mat[t].a[i][j]%=lim;
				}
			}
		}
		T.build(1,1,n);
		while(Q--){
			int l,r;
			scanf("%d%d",&l,&r);
			mat ans=T.query(1,1,n,l,r);
			for(int i=1;i<=2;i++){
				for(int j=1;j<=2;j++){
					printf("%d",ans.a[i][j]);
					if(j==1)printf(" ");
					else printf("\n");
				}
			}
			printf("\n");
		}
		printf("\n");
	}

	return 0;
}
