/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-12 02:47:02
 * @Description: CDQ分治 三维偏序做法
 * @Source: https://nanti.jisuanke.com/t/41356
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
const int MAX = 2e5+10;
const int MAXN =2e6;
const int MOD =1e9+9;
int n,m,cntq;
int ans[MAX];
int cnt;
struct Node{
	int op;
	int x,y;
	int kind,t;
	Node(){}
	Node(int op1,int x1,int y1,int k,int i):op(op1),x(x1),y(y1),kind(k),t(i){}
}node[MAXN];
Node tmp[MAXN];
int a[MAX],b[MAX],c[MAX];
int tot=0;
bool cmp(const Node&a,const Node&b){
	if(a.x==b.x)return a.t<b.t;
	return a.x<b.x;
}
void add(int x,int val){
	if(x==0) return;
	for(;x<=MAX;x+=lowbit(x)){
		c[x] += val;
	}
}

int getsum(int x){
	int sum = 0;
	for(;x;x-=lowbit(x)){
		sum+=c[x];
	}
	return sum;
}

void count(){
	for(int i=1;i<=tot;i++){
		if(tmp[i].op==0)
			add(tmp[i].y,tmp[i].kind);
		else
			ans[tmp[i].kind]+=tmp[i].op*getsum(tmp[i].y);
	}
	for(int i=1;i<=tot;i++){
		if(tmp[i].op==0) add(tmp[i].y,-tmp[i].kind);
	}

}

void cdq(int l,int r){
	if(l>=r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	tot=0;
	for(int i=l;i<=mid;i++){
		if(node[i].op==0) tmp[++tot]=node[i];
	}
	for(int i=mid+1;i<=r;i++){
		if(node[i].op) tmp[++tot]=node[i];
	}
	sort(tmp+1,tmp+1+tot,cmp);
	count();
}


int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	a[0]=-INF;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]++;
	}
	for(int i=1;i<=n;i++)if(a[i]!=a[i-1])b[i]=a[i];
	int tot = 0;
	int op,p,v;Node tmp;
	for(int i=1;i<=n;i++){
		if(b[i]==0) continue;
		node[++cnt]={0,i,b[i],1,++tot};
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&p,&v);
			v++;
			if(a[p]==v) continue;
			if(b[p]!=0){
				node[++cnt]={0,p,b[p],-1,++tot};
			}
			if(v==a[p-1]){
				if(a[p+1]==v){
					node[++cnt]={0,p+1,v,-1,++tot};
					b[p]=b[p+1]=0;
					a[p]=v;
				} else{
					b[p]=0;
					a[p]=v;
				}
			} else{
				node[++cnt]={0,p,v,1,++tot};
				if(a[p+1]==v){
					node[++cnt]={0,p+1,v,-1,++tot};
					b[p+1]=0;
				} else if(b[p+1]==0){
					node[++cnt]={0,p+1,a[p+1],1,++tot};
					b[p+1]=a[p+1];
				}
				a[p]=v;b[p]=v;
			}
		} else{
			int L,R,x,y;
			scanf("%d%d%d%d",&L,&R,&x,&y);
			x++;y++;
			if(L==R){
				if(a[L]>=x && a[L]<=y){
					ans[++cntq]=1;
				} else{
					ans[++cntq]=0;
				}
				continue;
			}
			node[++cnt]={1,L,x-1,++cntq,++tot};
			node[++cnt]={-1,L,y,cntq,++tot};
			node[++cnt]={-1,R,x-1,cntq,++tot};
			node[++cnt]={1,R,y,cntq,++tot};
			if(b[L+1]==0){
				if(a[L+1]>=x && a[L+1]<=y) ans[cntq]++;
			} else{
				if(a[L]>=x && a[L]<=y) ans[cntq]++;
			}
		}
	}
	cdq(1,cnt);
	for(int i=1;i<=cntq;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
