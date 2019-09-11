/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-11 15:16:43
 * @Description: CDQ分治
 * @Source: https://vjudge.net/contest/250839#problem/A
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
const int MAX = 1e5+10;
const int MAXN =2e5+10;
const int MOD =1e9+9;
int n;
struct Node{
	int id,op,t,x,pos;
}node[MAX];
int num[MAX],ans[MAX];
int dc[MAX],tot=0;
bool cmp(const Node&X,const Node&Y){
	return X.t<Y.t;
}
bool cmp2(const Node&X,const Node&Y){
	return X.id<Y.id;
}
void CDQ(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	sort(node+l,node+mid+1,cmp);
	sort(node+mid+1,node+r+1,cmp);
	int j=l;
	for(int i=mid+1;i<=r;i++){
		while(j<=mid && node[j].t<node[i].t){
			num[node[j].pos]+=node[j].op;
			j++;
		}
		if(node[i].op==0)
			ans[node[i].id]+=num[node[i].pos];
	}
	//撤销操作
	for(int i=l;i<j;i++) num[node[i].pos]-=node[i].op;
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&node[i].op,&node[i].t,&node[i].x);
		if(node[i].op==2)node[i].op=-1;
		if(node[i].op==3)node[i].op=0;
		node[i].id=i;
		dc[++tot]=node[i].x;
	}
	sort(dc+1,dc+1+tot);
	tot=unique(dc+1,dc+1+tot)-(dc+1);
	for(int i=1;i<=n;i++){
		node[i].pos=lower_bound(dc+1,dc+1+tot,node[i].x)-dc;
	}
	CDQ(1,n);
	sort(node+1,node+1+n,cmp2);
	for(int i=1;i<=n;i++){
		if(node[i].op==0){
			printf("%d\n",ans[i]);
		}
	}

	return 0;
}
