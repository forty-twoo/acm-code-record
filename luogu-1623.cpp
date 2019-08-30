/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-31 03:06
 * @Description: 树形dp+高精度
 * @Source: https://www.luogu.org/problem/P1623
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f
#define eps 1e-8
typedef long long ll;
typedef  unsigned long long ull;
using namespace std;
const int MAX =1e3+10;
const int P=10000;
int n,x,k,y;
int dp[MAX][2];
vector<int> G[MAX];
struct BigInt {
	int len,a[100];
	BigInt() {
		len=0;
		memset(a,0,sizeof(a));
	}
	void init(int x) {
		memset(a,0,sizeof(a));
		len=0;
		do {
			a[++len]=x%P;
			x/=P;
		} while(x);
	}
	void output() {
		printf("%d",a[len]);
		for(int i=len-1; i>=1; i--)printf("%04d",a[i]);
		puts("");
	}
	BigInt operator *(BigInt x) {
		BigInt now;
		now.len=len+x.len-1;
		for(int i=1; i<=len; i++)
			for(int j=1; j<=x.len; j++)now.a[i+j-1]+=a[i]*x.a[j];
		for(int i=1; i<=now.len; i++) {
			now.a[i+1]+=now.a[i]/P;
			now.a[i]%=P;
		}
		while(now.a[now.len+1])now.len++;
		return now;
	}
	BigInt operator +(BigInt x) {
		BigInt now;
		now.len=max(len,x.len);
		for(int i=1; i<=now.len; i++)now.a[i]=x.a[i]+a[i];
		for(int i=1; i<=now.len; i++) {
			now.a[i+1]+=now.a[i]/P;
			now.a[i]%=P;
		}
		while(now.a[now.len+1])now.len++;
		return now;
	}
} f[MAX][2];
//int f[MAX][2];

void dfs(int x){
	int maxx=-INF;
	f[x][0].init(1);
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		dfs(y);
		dp[x][0]+=dp[y][1];
		f[x][0]=f[x][0]*f[y][1];
		//注意此处 dp[x][0]必须放在循环外
		//maxx=max(dp[x][0]-dp[y][1]+dp[y][0]+1,maxx)是错的
		maxx=max(maxx,-dp[y][1]+dp[y][0]+1);
	}
	dp[x][1]=max(dp[x][0],dp[x][0]-maxx);
	if(dp[x][0]==dp[x][1]) f[x][1]=f[x][0];
	for(auto y:G[x]){
		if(dp[x][0]-dp[y][1]+dp[y][0]+1==dp[x][1]){
			BigInt tmp;tmp.init(1);
			for(auto z:G[x]){
				if(z==y) tmp=tmp*f[z][0];
				else tmp=tmp*f[z][1];
			}
			f[x][1]=f[x][1]+tmp;
		}
	}
}

int main(){
	//debug;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		scanf("%d",&k);
		for(int j=1;j<=k;j++){
			scanf("%d",&y);
			G[x].push_back(y);
		}
	}
	dfs(1);
	printf("%d\n",dp[1][1]);
	f[1][1].output();

	return 0;
}
