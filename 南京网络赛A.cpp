/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-09 22:23:46
 * @Description: 树状数组离线处理二维数点
 * @Source: https://nanti.jisuanke.com/t/41298 2019南京网络赛A题
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
using namespace std;
typedef pair<ll,int> PI;
const int MAX = 1e6+10;
const int MAXN =2e5+10;
const int MOD =1e9+9;
int n,m,Q;
ll rec[MAX];
struct Node{
	int op; //op=-1:下线段 op=0:事件点 op=1:上线段
	int x,y,xx;
	ll val;
	int id;
	bool operator<(const Node&A){
		if(y!=A.y)
			return y<A.y;
		else return op<A.op;
	}
}node[MAX];

struct BIT{
	ll val[MAX];
	void init(){
		mst(val,0);
	}
	void add(int x,ll v){
		for(;x<=MAX;x+=lowbit(x)) val[x]+=v;
	}
	ll ask(int x){
		ll ans=0;
		for(;x;x-=lowbit(x)) ans+=val[x];
		return ans;
	}
	ll query(int l,int r){
		return ask(r)-ask(l-1);
	}
}Bit;


ll lefup[MAX]; //(i,n-i+1)
ll rigup[MAX]; //(i,i)
ll lefdown[MAX]; //(i,i)
ll rigdown[MAX]; //(i,n-i+1)
void init(ll n){
	ll d=n-1;
	ll mid=(n+1)/2;
	ll has=1;
	for(int i=1;i<=mid;i++){
		has+=d*3ll;
		lefup[i]=has;
		d--;
		has+=(d+1ll);
		d--;
	}
	d=n-1ll;
	has=1ll;
	for(int i=n;i>=mid;i--){
		rigup[i]=has;
		has+=d*4ll;
		d-=2ll;
	}
	d=n-1ll;has=1ll;
	for(int i=1;i<=mid;i++){
		has+=d*2ll;
		lefdown[i]=has;
		has+=d*2ll;
		d-=2ll;
	}
	d=n-1ll,has=1ll;
	for(int i=n;i>=mid;i--){
		has+=d;
		rigdown[i]=has;
		has+=d*3ll;
		d-=2ll;
	}
}
ll get_val(ll x,ll y){
	ll mid=(n+1)/2;
	ll canx,cany;
	if(x>=y){
		if(x==y){
			if(x<=mid) return lefdown[x];
			else return rigup[x];
		}
		if(x+y==n+1){
			return rigdown[x];
		}
		if(x+y<n+1){
			canx=y,cany=y;
			return lefdown[canx]-(x-canx);
		} else{
			canx=x,cany=n+1-x;
			return rigdown[canx]-(y-cany);
		}
	} else{
		if(x==y){
			return lefdown[x];
		}
		if(x+y==n+1ll){
			return lefup[x];
		}
		if(x+y<n+1ll){
			canx=x,cany=x;
			return lefdown[canx]+(y-cany);
		} else{
			canx=n+1ll-y,cany=y;
			return lefup[canx]+(x-canx);
		}
	}
}
ll get_ans(ll x){
	ll ans=0;
	while(x){
		ans+=x%10ll;
		x/=10ll;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int ks;
	scanf("%d",&ks);
	while(ks--){
		scanf("%d%d%d",&n,&m,&Q);
		init((ll)n);
		Bit.init();
		int cnt=0;
		int x,y;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			ll ans=get_ans(get_val((ll)x,(ll)y));
			node[++cnt].op=0,node[cnt].x=x,node[cnt].y=y,node[cnt].val=ans;
		}
		int x1,x2,y1,y2;
		for(int i=1;i<=Q;i++){
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			node[++cnt].op=-1,node[cnt].x=x1,node[cnt].y=y1,node[cnt].xx=x2,node[cnt].id=i;
			node[++cnt].op=1,node[cnt].x=x1,node[cnt].y=y2,node[cnt].xx=x2,node[cnt].id=i;
		}
		sort(node+1,node+1+cnt);
		for(int i=1;i<=cnt;i++){
			if(node[i].op==1){
				ll up=Bit.query(node[i].x,node[i].xx);
				rec[node[i].id]=up-rec[node[i].id];
			}else if(node[i].op==-1){
				ll down=Bit.query(node[i].x,node[i].xx);
				rec[node[i].id]=down;
			}else{
				Bit.add(node[i].x,node[i].val);
			}
		}
		for(int i=1;i<=Q;i++){
			printf("%lld\n",rec[i]);
		}
	}

	return 0;
}
