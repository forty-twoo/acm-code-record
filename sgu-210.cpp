/*
 * @Don't panic: Allons-y!
 * @Author: fortya-twoo
 * @LastEditTime: 2019-09-05 15:49:14
 * @Description: 二分图最大匹配+思维
 * @Source: http://codeforces.com/problemsets/acmsguru/problem/99999/210
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
const int MAX = 4e2+20;
const int MAXN =8e2+20;
const int MOD =1e9+9;
int n;
struct Node{
	int love;
	int id;
	bool operator<(const Node&x){
		return love>x.love;
	}
}node[MAX];
int ans[MAX];
int match[MAXN],vis[MAXN];
vector<int> G[MAX];
bool dfs(int x){
	for(auto y:G[x]){
		if(!vis[y]){
			vis[y]=1;
			if(!match[y] || dfs(match[y])){
				match[y]=x;
				ans[x]=y;
				return  true;
			}
		}
	}
	return false;
}
int main(){
	//debug;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&node[i].love);
		node[i].id=i;
	}
	sort(node+1,node+1+n);
	for(int i=1;i<=n;i++){
		int k,x;
		scanf("%d",&k);
		for(int j=1;j<=k;j++){
			scanf("%d",&x);
			G[i].push_back(x+n);
		}
	}
	for(int i=1;i<=n;i++){
		mst(vis,0);
		dfs(node[i].id);
	}
	for(int i=1;i<=n;i++){
		if(ans[i]!=0) ans[i]-=n;
		printf("%d ",ans[i]);
	} 
	puts("");
	system("pause");

	return 0;
}
