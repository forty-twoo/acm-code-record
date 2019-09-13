/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-14 00:24:19
 * @Description: 线段树维护矩阵乘法+dp
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=5068
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
const int MAX=5e4+10;
const int MOD=1e9+7;
using namespace std;
int a[MAX][10],n,m,Q;
struct mat{
	ll a[5][5];
};
mat X;
mat cun[MAX<<2];
void getmat(mat&c,int x){
	mst(c.a,0);
	for(int i=1;i<=2;i++){
		c.a[i][1]=a[x][i];
	}
	for(int i=3;i<=4;i++){
		c.a[i-2][2]=a[x][i];
	}
}
mat matmul(mat A,mat B){
	mat ans;
	mst(ans.a,0);
	for(int i=1;i<=2;i++){
		for(int k=1;k<=2;k++){
			for(int j=1;j<=2;j++){
				ans.a[i][j]=(ans.a[i][j]+A.a[i][k]*B.a[k][j]%MOD)%MOD;
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
	mat tmp;
	void init(){
		mst(tmp.a,0);
		for(int i=1;i<=2;i++){
			tmp.a[i][i]=1;
		}
	}
	void pushup(int rt){
		cun[rt]=matmul(cun[lc],cun[rc]);
	}
	void build(int rt,int l,int r){
		if(l==r){
			getmat(cun[rt],l);
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void change(int rt,int l,int r,int x){
		if(l==r){
			getmat(cun[rt],x);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)  change(lson,x);
		else change(rson,x);
		pushup(rt);
	}

	void query(int rt,int l,int r,int L,int R){
		if(L<=l && r<=R){
			tmp=matmul(tmp,cun[rt]);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid) query(lson,L,R);
		if(R>mid) query(rson,L,R);
	}

}T;

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	while(~scanf("%d%d",&n,&Q)){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=4;j++){
				a[i][j]=1;
			}
		}
		T.build(1,1,n-1);
		int op,x,y,z;
		for(int i=1;i<=Q;i++){
			scanf("%d",&op);
			if(op==1){
				scanf("%d%d%d",&x,&y,&z);
				if(y==1){
					if(z==1) a[x][1]^=1;
					if(z==2) a[x][3]^=1;
				}
				if(y==2){
					if(z==1) a[x][2]^=1;
					if(z==2) a[x][4]^=1;
				}
				T.change(1,1,n-1,x);
			} else{
				scanf("%d%d",&x,&y);
				T.init();
				T.query(1,1,n-1,x,y-1);
				ll ans=0;
				for(int i=1;i<=2;i++){
					for(int j=1;j<=2;j++){
						ans=(ans+T.tmp.a[i][j])%MOD;
					}
				}
				printf("%lld\n",ans);
			}
		}
	}

	return 0;
}
