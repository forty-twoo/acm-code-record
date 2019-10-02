/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-02 16:40:19
 * @Description: 贪心+优先队列(反悔法)
 * @Source: https://www.luogu.org/problem/P4053
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
const int MAX=2e5;
const int MAXN=1e5+10;
const int MOD=1e9+7;
using namespace std;
struct Node{
	ll x,y;
	bool operator<(const Node&X)const{
		return y<X.y;
	}
}node[MAX];
prique<ll> Q;
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&node[i].x,&node[i].y);
	}
	sort(node+1,node+1+n);
	ll sum=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(sum+node[i].x<=node[i].y){
			sum+=node[i].x;
			ans++;
			Q.push(node[i].x);
		}else{
			if(Q.size()){
				ll cur=Q.top();
				if(cur>node[i].x){
					sum-=cur;
					Q.pop();
					Q.push(node[i].x);
					sum+=node[i].x;
				}
			}
		}
	}
	printf("%d\n",ans);

	return 0;
}
