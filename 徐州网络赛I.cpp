/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-10 21:37
 * @Description: 树状数组离线处理二维偏序
 * @Source: https://nanti.jisuanke.com/t/41391  徐州网络赛I题
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
typedef pair<int,int> PI;
int n,m,a[MAX],pos[MAX],ans[MAX];
struct Node{
	int x,y;
	int id;
	bool operator<(const Node&A){
		if(y==A.y) return id<A.id;
		return y<A.y;
	}
};
struct BIT{
	int val[MAX];
	void add(int x,int v){
		for(;x<=n;x+=lowbit(x)){
			val[x]+=v;
		}
	}
	int ask(int x){
		int ans=0;
		for(;x;x-=lowbit(x)){
			ans+=val[x];
		}
		return ans;
	}
}Bit;
vector<Node> V;

void init(){
	for(int i=1;i<=n;i++){
		for(int j=2;j*i<=n;j++){
			int pa=pos[i];
			int pb=pos[i*j];
			if(pa>pb) swap(pa,pb);
			Node tmp;tmp.x=pa,tmp.y=pb,tmp.id=0;
			V.push_back(tmp);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pos[a[i]]=i;
	}
	init();
	int L,R;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&L,&R);
		Node tmp;tmp.x=L,tmp.y=R,tmp.id=i;
		V.push_back(tmp);
	}
	sort(V.begin(),V.end());
	for(int i=0;i<V.size();i++){
		Node tmp=V[i];
		if(tmp.id==0){
			Bit.add(tmp.x,1);
		}else{
			ans[tmp.id]=Bit.ask(n)-Bit.ask(tmp.x-1);
		}
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
