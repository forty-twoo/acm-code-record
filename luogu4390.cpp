/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-27 16:44:36
 * @Description: 三维偏序(CDQ分治)
 * @Source: https://www.luogu.org/problem/P4390
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
const int MAX=5e5+10;
const int MAXN=2e6+10;
const int MOD=1e9+7;
using namespace std;
int n,cnt=0;
int p=0;
ll ans[MAX];
struct Node{
	int k;
	int id;
	int x,y;
	int num;
}node[MAX];
Node curn[MAX];
bool cmpx(const Node&A,const Node&B){
	return A.x<B.x;

}
struct BIT{
	ll c[MAXN];
	void init(){
		mst(c,0);
	}
	void add(int x,ll v){
		for(;x<=n;x+=lowbit(x)){
			c[x]+=v;
		}
	}
	ll query(int x){
		ll ans=0;
		for(;x>0;x-=lowbit(x)){
			ans+=c[x];
		}
		return ans;
	}
}bit;

void count(){
	for(int i=1;i<=p;i++){
		if(curn[i].k==0){
			bit.add(curn[i].y,curn[i].num);
		} else{
			ans[curn[i].id]+=bit.query(curn[i].y)*curn[i].k;
		}
	}
	for(int i=1;i<=p;i++){
		if(curn[i].k==0){
			bit.add(curn[i].y,-curn[i].num);
		}
	}
}
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	p=0;
	for(int i=l;i<=mid;i++){
		if(node[i].k==0){
			curn[++p]=node[i];
		}
	}
	for(int i=mid+1;i<=r;i++){
		if(node[i].k!=0){
			curn[++p]=node[i];
		}
	}
	stable_sort(curn+1,curn+1+p,cmpx);
	count();
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int tmp;
	scanf("%d%d",&tmp,&n);
	bit.init();
	int op;
	int at=0;
	while(scanf("%d",&op)){
		if(op==3)break;
		int x1,y1,x2,y2,num;
		if(op==1){
			scanf("%d%d%d",&x1,&y1,&num);
			node[++cnt].id=0,node[cnt].k=0;
			node[cnt].num=num,node[cnt].x=x1,node[cnt].y=y1;
		} else{
			at++;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			node[++cnt].id=at,node[cnt].k=-1;
			node[cnt].x=x1-1,node[cnt].y=y2;
			node[++cnt].id=at,node[cnt].k=-1;
			node[cnt].x=x2,node[cnt].y=y1-1;
			node[++cnt].id=at,node[cnt].k=1;
			node[cnt].x=x1-1,node[cnt].y=y1-1;
			node[++cnt].id=at,node[cnt].k=1;
			node[cnt].x=x2,node[cnt].y=y2;
		}
	}
	CDQ(1,cnt);
	for(int i=1;i<=at;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
