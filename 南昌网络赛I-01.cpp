/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-12 02:42:26
 * @Description: CDQ分治 四维偏序做法
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
const int MAXN =2e5+10;
const int MOD =1e9+9;
int n,m,cntq;
int ans[MAX];
struct Node{
	int op;
	int x,y,z;
	int kind,t;
	Node(){}
	Node(int op1,int x1,int y1,int z1,int k,int i):op(op1),x(x1),y(y1),z(z1),kind(k),t(i){}
};
vector<Node> q,q1,q2;
vector<int> v;
int a[MAX],b[MAX],c[MAX];
bool cmp(const Node&a,const Node&b){
	if(a.x==b.x)return a.t<b.t;
	return a.x>b.x;
}
bool cmp1(const Node&a,const Node&b){
	if(a.y==b.y)return a.t<b.t;
	return a.y<b.y;
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
	for(int i=0;i<q2.size();i++){
		if(q2[i].op==0)
			add(q2[i].z,q2[i].kind);
		else
			ans[q2[i].kind]+=q2[i].op*getsum(q2[i].z);
	}
	for(int i=0;i<q2.size();i++){
		if(q2[i].op==0) add(q2[i].z,-q2[i].kind);
	}

}
void cdq1(int l,int r){
	if(l>=r) return;
	int mid=(l+r)>>1;
	cdq1(l,mid);cdq1(mid+1,r);
	q2.clear();
	for(int i=l;i<=mid;i++){
		if(q1[i].op==0) q2.push_back(q1[i]);
	}
	for(int i=mid+1;i<=r;i++){
		if(q1[i].op) q2.push_back(q1[i]);
	}
	sort(q2.begin(),q2.end(),cmp1);
	count();
}

void cdq(int l,int r){
	if(l>=r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	q1.clear();
	for(int i=l;i<=mid;i++){
		if(q[i].op==0) q1.push_back(q[i]);
	}
	for(int i=mid+1;i<=r;i++){
		if(q[i].op) q1.push_back(q[i]);
	}
	sort(q1.begin(),q1.end(),cmp);
	cdq1(0,q1.size()-1);
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
		tmp={0,i,i,b[i],1,++tot};
		q.push_back(tmp);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&p,&v);
			v++;
			if(a[p]==v) continue;
			if(b[p]!=0){
				tmp={0,p,p,b[p],-1,++tot};
				q.push_back(tmp);
			}
			if(v==a[p-1]){
				if(a[p+1]==v){
					tmp={0,p+1,p+1,v,-1,++tot};
					q.push_back(tmp);
					b[p]=b[p+1]=0;
					a[p]=v;
				} else{
					b[p]=0;
					a[p]=v;
				}
			} else{
				tmp={0,p,p,v,1,++tot};
				q.push_back(tmp);
				if(a[p+1]==v){
					tmp={0,p+1,p+1,v,-1,++tot};
					q.push_back(tmp);
					b[p+1]=0;
				} else if(b[p+1]==0){
					tmp={0,p+1,p+1,a[p+1],1,++tot};
					q.push_back(tmp);
					b[p+1]=a[p+1];
				}
				a[p]=v;b[p]=v;
			}

		} else{
			int L,R,x,y;
			scanf("%d%d%d%d",&L,&R,&x,&y);
			x++,y++;
			tmp={-1,L+1,R,x-1,++cntq,++tot};
			q.push_back(tmp);
			tmp={1,L+1,R,y,cntq,++tot};
			q.push_back(tmp);
			if(b[L+1]==0){
				if(a[L+1]>=x && a[L+1]<=y) ans[cntq]++;
			} else{
				if(a[L]>=x && a[L]<=y) ans[cntq]++;
			}
		}
	}
	cdq(0,q.size()-1);
	for(int i=1;i<=cntq;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
