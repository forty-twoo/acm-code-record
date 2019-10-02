/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-02 16:40:19
 * @Description: 补图二分图最大点独立集求最大团
 * @Source: https://www.luogu.org/problem/P2423
 */

/*
 * 本题给了两个集合A和B,每个集合中有一些点,A中两个点之间有边当条件为a xor b mod 2=1, B中
 * 两个点有边的条件为a xor b mod 2=0 或者 (a or b)化成二进制有奇数个1, 题目还给出了A中有几个点
 * 和B中的点有关系, 图中所有关系是无向的,求整个图的最大团.
 *
 * 解法：发现A最多只能选2个点，因为A中选出来的点奇偶性必须互异。B中奇权点之间有边，偶权点之间有边
 * 奇权点可能与偶权点间有边，可以发现B的反图是一个二分图，因此转为计算反图二分图的最大独立集集。
 *
 * 技巧：匈牙利算法不断mst(vis,0)会超时，我们给vis一个时间戳就不会超时了
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
const int MAX=3e3+10;
const int MAXN=1e5+10;
const int MOD=1e9+7;
using namespace std;
int ca,cb,cab;
int va[MAX],vb[MAX],head[MAX];
vector<int> A[MAX],evenb,oddb;
struct Edge{
	int u,v,nxt;
}edge[MAXN];
int tot;
void add(int u,int v){
	edge[++tot].u=u;edge[tot].v=v;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
int tpre;
int match[MAX],vis[MAX],in[MAX];
struct Hungry{
	bool dfs(int x){
		for(int i=head[x];i;i=edge[i].nxt){
			int y=edge[i].v;
			if(vis[y]==tpre+1 || !in[y])continue;  //运用时间戳
			vis[y]=tpre+1;
			if(!match[y]||dfs(match[y])){
				match[y]=x;
				return true;
			}
		}
		return false;
	}
	int solve(){
		int ans=0;
		for(int i=0;i<oddb.size();i++){
			int x=oddb[i];
			if(!in[x])continue;
			if(dfs(x)){
				ans++;
				tpre++; //!!!
			}
		}
		return ans;
	}

}hungry;
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	int ks;
	scanf("%d",&ks);
	while(ks--){

		int ans=0;evenb.clear();oddb.clear();
		scanf("%d%d%d",&ca,&cb,&cab);
		int x,y;
		for(int i=1;i<=ca;i++){
			scanf("%d",&va[i]);
			A[i].clear();
		}
		for(int i=1;i<=cb;i++){
			scanf("%d",&vb[i]);
			if(vb[i]%2==0)evenb.pb(i);
			else oddb.pb(i);
		}
		for(int i=1;i<=cab;i++){
			scanf("%d%d",&x,&y);
			A[x].pb(y);
		}
		//choose 0 point in A
		tpre=tot=0;
		mst(vis,0);mst(head,0);mst(match,0);

		for(int i=1;i<=cb;i++)in[i]=1;
		for(auto ii:oddb){
			for(auto jj:evenb){
				if(!((__builtin_popcount((vb[ii]|vb[jj])))&1) )
					add(ii,jj);
			}
		}
		ans=max(ans,cb-hungry.solve());
		int all;
		//choose 1 point in A
		for(int i=1;i<=ca;i++){
			all=tot=0;
			mst(in,0);mst(match,0);
			for(auto to:A[i]){
				in[to]=1;
				all++;
			}
			int cnt=hungry.solve();
			ans=max(ans,1+all-cnt);
		}
		//choose 2 point in A
		for(int i=1;i<=ca;i++){
			for(int j=i+1;j<=ca;j++){
				if((va[i]^va[j])%2==1){
					all=tot=0;
					mst(match,0);mst(in,0);mst(match,0);
					for(auto to:A[i])in[to]++;
					for(auto to:A[j])in[to]++;
					for(int i=1;i<=cb;i++)if(in[i]==2)all++;else in[i]=0;
					int cnt=hungry.solve();
					ans=max(ans,2+all-cnt);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
