/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-26 01:00
 * @Description: 线段树 扫描线
 * @Source: https://vjudge.net/problem/POJ-3470
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define eps 1e-8
#define pb push_back
typedef long long ll;
using namespace std;
const int MAX = 5e5+10;
const int MAXN=2e5+10;
const int MOD = 998244353;
const ll INF=1e18;
int n,cnt;
ll ans[MAX][6];
int chose[MAX];
int add[MAX];
int poss[MAX][6];
ll dc[MAX],tot;
struct Node{
	ll x,y,len;
	int dir; //dir==1:x  dir==2:y
	int id; //id<=n: seg or: point
}node[MAX];
bool cmp_upx(const Node&A,const Node&B){
	return A.y>B.y;
}
bool cmp_downx(const Node&A,const Node&B){
	return A.y<B.y;
}
bool cmp_lefty(const Node&A,const Node&B){
	return A.x<B.x;
}
bool cmp_righty(const Node&A,const Node&B){
	return A.x>B.x;
}
int Hash(ll x){
	return lower_bound(dc+1,dc+1+tot,x)-dc;
}


struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,m
#define rson rc,m+1,r
	ll miny[MAXN<<2],idd[MAXN<<2],lazy[MAXN<<2],ans;
	int pos;
	void pushdown(int rt){
		if(lazy[rt]){
			if(miny[lc]>=miny[rt]){
				miny[lc]=miny[rt];
				idd[lc]=idd[rt];
				lazy[lc]=1;
			}
			if(miny[rc]>=miny[rt]){
				miny[rc]=miny[rt];
				idd[rc]=idd[rt];
				lazy[rc]=1;
			}
			lazy[rt]=0;
		}
	}
	void build(int rt,int l,int r,ll val){
		if(l==r){
			miny[rt]=val;
			lazy[rt]=0;
			return;
		}
		int m=(l+r)/2;
		build(lson,val);build(rson,val);
		miny[rt]=max(miny[lc],miny[rc]);
		lazy[rt]=min(lazy[lc],lazy[rc]);
	}
	void insert(int rt,int l,int r,int L,int R,ll v,int id){
		if(L<=l && r<=R){
			if(v<=miny[rt]){
				idd[rt]=id;
				lazy[rt]=1;
				miny[rt]=v;
			}
			return;
		}
		int m=(l+r)/2;
		pushdown(rt);
		if(L<=m) insert(lson,L,R,v,id);
		if(R>m) insert(rson,L,R,v,id);
	}
	void query(int rt,int l,int r,int x){
		if(l==r){
			pos=idd[rt];
			ans=miny[rt];
			return;
		}
		int m=(l+r)/2;
		pushdown(rt);
		if(x<=m) query(lson,x);
		else query(rson,x);
	}
}T1;

void solveup(){
	sort(node+1,node+1+cnt,cmp_upx);
	T1.build(1,1,tot,INF);
	for(int i=1;i<=cnt;i++){
		if(node[i].dir==2){
			int L=Hash(node[i].x);
			int R=L;
			T1.insert(1,1,tot,L,R,node[i].y,node[i].id);

		} else if(node[i].dir==1){
			int L=Hash(node[i].x);
			int R=Hash(node[i].x+node[i].len);
			T1.insert(1,1,tot,L,R,node[i].y,node[i].id);
		} else if(node[i].id>n){
			T1.ans=INF;
			int id=node[i].id-n;
			int x=Hash(node[i].x);
			T1.query(1,1,tot,x);
			ll miny=T1.ans;
			ans[id][1]=miny-node[i].y;
			poss[id][1]=T1.pos;
		}
	}
}

void solvedown(){
	sort(node+1,node+1+cnt,cmp_downx);
	T1.build(1,1,tot,INF);
	for(int i=1;i<=cnt;i++){
		if(node[i].dir==2){
			int L=Hash(node[i].x);
			int R=L;
			T1.insert(1,1,tot,L,R,-(node[i].y+node[i].len),node[i].id);
		} else if(node[i].dir==1){
			int L=Hash(node[i].x);
			int R=Hash(node[i].x+node[i].len);
			T1.insert(1,1,tot,L,R,-node[i].y,node[i].id);
		} else if(node[i].id>n){
			T1.ans=INF;
			int id=node[i].id-n;
			int x=Hash(node[i].x);
			T1.query(1,1,tot,x);
			ll miny=T1.ans;
			ans[id][2]=node[i].y-(-miny);
			poss[id][2]=T1.pos;
		}
	}
}

void solveright(){
	sort(node+1,node+1+cnt,cmp_righty);
	T1.build(1,1,tot,INF);
	for(int i=1;i<=cnt;i++){
		if(node[i].dir==1){
			int L=Hash(node[i].y);
			int R=L;
			T1.insert(1,1,tot,L,R,node[i].x,node[i].id);
		} else if(node[i].dir==2){
			int L=Hash(node[i].y);
			int R=Hash(node[i].y+node[i].len);
			T1.insert(1,1,tot,L,R,node[i].x,node[i].id);
		} else if(node[i].id>n){
			T1.ans=INF;
			int id=node[i].id-n;
			int x=Hash(node[i].y);
			T1.query(1,1,tot,x);
			ll miny=T1.ans;
			ans[id][3]=miny-node[i].x;
			poss[id][3]=T1.pos;
		}
	}
}
void solveleft(){
	sort(node+1,node+1+cnt,cmp_lefty);
	T1.build(1,1,tot,INF);
	for(int i=1;i<=cnt;i++){
		if(node[i].dir==1){
			int L=Hash(node[i].y);
			int R=L;
			T1.insert(1,1,tot,L,R,-(node[i].x+node[i].len),node[i].id);
		} else if(node[i].dir==2){
			int L=Hash(node[i].y);
			int R=Hash(node[i].y+node[i].len);
			T1.insert(1,1,tot,L,R,-node[i].x,node[i].id);
		} else if(node[i].id){
			T1.ans=INF;
			int id=node[i].id-n;
			int x=Hash(node[i].y);
			T1.query(1,1,tot,x);
			ll miny=T1.ans;
			ans[id][4]=node[i].x-(-miny);
			poss[id][4]=T1.pos;
		}
	}
}
int main(){
	debug;
	int m;
	scanf("%d%d",&n,&m);
	ll x1,x2,y1,y2;cnt=tot=0;
	for(int i=0;i<MAX;i++){
		for(int j=0;j<5;j++) ans[i][j]=INF+10000000;
	}
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		dc[++tot]=x1;dc[++tot]=x2;dc[++tot]=y1;dc[++tot]=y2;
		if(y1==y2){
			//node[++cnt]={min(x1,x2),y1,abs(x1-x2),1,i};
			node[++cnt].x=min(x1,x2);node[cnt].y=y1;node[cnt].len=(x1-x2)>0?(x1-x2):(x2-x1);
			node[cnt].dir=1;node[cnt].id=i;
		} else{
			//node[++cnt]={x1,min(y1,y2),abs(y1-y2),2,i};
			node[++cnt].x=x1;node[cnt].y=min(y1,y2);node[cnt].len=(y1-y2)>0?(y1-y2):(y2-y1);
			node[cnt].dir=2;node[cnt].id=i;
		}
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x1,&y1);
		dc[++tot]=x1;dc[++tot]=y1;
		//node[++cnt]={x1,y1,0,0,i+n};
		node[++cnt].x=x1;node[cnt].y=y1;node[cnt].len=0;
		node[cnt].dir=0;node[cnt].id=i+n;
	}
	sort(dc+1,dc+1+tot);
	tot=unique(dc+1,dc+1+tot)-(dc+1);
	solveup();
	solvedown();
	solveleft();
	solveright();
	for(int i=1;i<=m;i++){
		chose[i]=0;
		for(int j=1;j<=4;j++){
			if(ans[i][0]>ans[i][j]){
				ans[i][0]=ans[i][j];
				chose[i]=poss[i][j];
			}
		}
		add[chose[i]]++;
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",add[i]);
	}
	return 0;
}
