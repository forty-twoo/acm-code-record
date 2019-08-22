/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-22 15:48
 * @Description: 01字典树
 * @Source: https://vjudge.net/problem/UVALive-4682
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
typedef  unsigned long long ull;
using namespace std;
const int MAX = 1e5+10;
const int MAXN = 32*MAX;
const int MOD = 998244353;
int ks,n,sum[MAX],a[MAX];

struct Trie_01{
#define N 32
	int ch[MAXN][2],tot,val[MAXN];
	void init(){
		tot=0;mst(ch,0);
	}
	inline void insert(int x){
		int u=0;
		for(int i=N-1;i>=0;i--){
			int cur=(x>>i&1);
			if(ch[u][cur]) u=ch[u][cur];
			else{
				ch[u][cur]=++tot;
				u=tot;
			}
		}
		val[u]=x;
	}
	inline int query(int x){
		int u=0;
		for(int i=N-1;i>=0;i--){
			int cur=(x>>i&1);
			if(ch[u][cur^1]) u=ch[u][cur^1];
			else u=ch[u][cur];
		}
		return val[u]^x;
	}

}Trie;

int main(){
	debug;
	scanf("%d",&ks);
	sum[0]=0;
	while(ks--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			sum[i]=sum[i-1]^a[i];
		}
		Trie.init();Trie.insert(sum[0]);
		int ans=0;
		for(int i=1;i<=n;i++){
			ans=max(ans,Trie.query(sum[i]));
			Trie.insert(sum[i]);
		}
		printf("%d\n",ans);
	}

	return 0;
}
