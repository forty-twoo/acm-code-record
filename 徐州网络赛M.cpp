/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-10 19:49
 * @Description: 贪心 构造
 * @Source: https://nanti.jisuanke.com/t/41395 徐州网络赛M题
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
const int MAXN =2e5+10;
const int MOD =1e9+9;
int n,m,ans;
char str[MAX],des[MAX];
int nxtp[MAX][27];
deque<int> V[27];
void pre(){
	for(int i=1;i<=n;i++){
		V[str[i]-'a'].push_back(i);
	}
	for(int i=1;i<=n;i++){
		V[str[i]-'a'].pop_front();
		for(int j=0;j<26;j++){
			if(V[j].size()==0) continue;
			nxtp[i][j]=V[j].front();
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d",&n,&m);
	scanf("%s%s",str+1,des+1);
	pre();
	int p=0;
	for(int i=1;i<=n;i++){
		if(str[i]>des[1]){
			p=i;break;
		}
	}
	if(p!=0)
		ans=max(ans,n-p+1);
	p=0;
	for(int i=1;i<=n;i++){
		if(str[i]==des[1]){
			p=i;break;
		}
	}
	if(p!=0){
		for(int i=2;i<=m;i++){
			int nxt=INF;
			for(int j=des[i]-'a'+1;j<26;j++){
				if(nxtp[p][j]!=0)
					nxt=min(nxt,nxtp[p][j]);
			}
			if(nxt!=INF)
				ans=max(ans,i-1+n-nxt+1);
			p=nxtp[p][des[i]-'a'];
			if(p==0) break;
		}
		if(p!=0 && p!=n) ans=max(ans,m+n-p);
	}
	if(ans!=0) printf("%d\n",ans);
	else printf("-1\n");

	return 0;
}
