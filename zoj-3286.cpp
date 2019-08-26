/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-26 16:06
 * @Description: 数学 分解质因数+筛法
 * @Source: https://zoj.pintia.cn/problem-sets/91827364500/problems/91827368124
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
const int MAX = 1e6+10;
const int MAXN = 3e4+10;
const int MOD = 998244353;
int v[MAX],n;
int vis[MAX],ans[MAX];
int num[MAX],cnt[MAX];

void init(int N){
	for(int i=1;i<=N;i++) cnt[i]=1;

	for(ll i=2;i<=N;i++){
		if(v[i]) continue;
		num[1]=0;
		for(int j=i;j<=N/i;j++){
			v[i*j]=1;
		}
		ll j=1;
		while(j*i<=N){
			num[i*j]=num[j]+1;
			cnt[i*j]=cnt[i*j]*(num[i*j]+1);
			j++;
		}
		//清空
		j=1;
		while(j*i<=N){
			num[i*j]=0;
			j++;
		}
	}
	ans[1]=0;
	for(int i=2;i<=N;i++){
		ans[i]=vis[cnt[i]+1];
		vis[cnt[i]+1]++;
	}
}


int main(){
	init(MAX);
	while(~scanf("%d",&n)){
		printf("%d\n",ans[n]);
	}

	return 0;
}
