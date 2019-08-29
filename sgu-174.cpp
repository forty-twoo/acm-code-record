/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-30 00:46
 * @Description: 基础并查集
 * @Source: http://codeforces.com/problemsets/acmsguru/problem/99999/174
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
const int MAX = 4e5+20;
const int MAXN = 30*MAX;
const int MOD = 998244353;
int n;
typedef pair<int,int> PI;
map<PI,int> mp;
struct Node{
	int a,b,c,d;
}node[MAX];
int fa[MAX];
int finda(int x){
	return fa[x]==x?x:finda(fa[x]);
}
int main(){
	//debug;
	int cnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&node[i].a,&node[i].b,&node[i].c,&node[i].d);
	}
	for(int i=1;i<=2*n;i++) fa[i]=i;
	for(int i=1;i<=n;i++){
		PI x=make_pair(node[i].a,node[i].b);
		PI y=make_pair(node[i].c,node[i].d);
		if(!mp[x]) mp[x]=++cnt;
		if(!mp[y]) mp[y]=++cnt;
		int fx=finda(mp[x]);
		int fy=finda(mp[y]);
		if(fx==fy){
			printf("%d\n",i);
			exit(0);
		} else{
			fa[fx]=fy;
		}
	}
	printf("0\n");

	return 0;
}
