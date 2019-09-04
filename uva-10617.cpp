/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-09-04 23:47
 * @Description: dp
 * @Source: https://vjudge.net/problem/UVA-10617
 */

#include<bits/stdc++.h>
#include <unordered_map>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
using namespace std;
const int MAX =1e2;
const int MAXN = 3e5+100;
const int MOD =1e9+9;
int n;
char str[MAX];
ll dp[MAX][MAX];
int main(){
	//debug;
	while(~scanf("%d",&n)){
		scanf("%s",str+1);
		mst(dp,0);
		int len=strlen(str+1);
		for(int t=1;t<=len;t++){
			for(int l=1;l<=len;l++){
				int r=l+t-1;if(r>len) continue;
				if(t==1){
					dp[l][r]=1;
					continue;
				}
				if(str[l]!=str[r]){
					dp[l][r]=dp[l][r-1]+dp[l+1][r]-dp[l+1][r-1];
				} else{
					dp[l][r]=dp[l][r-1]+dp[l+1][r]-dp[l+1][r-1]+dp[l+1][r-1]+1ll;
				}
			}
		}
		printf("%lld\n",dp[1][len]);
	}

}
