/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-25 17:52
 * @Description: 区间dp
 * @Source: https://vjudge.net/problem/UVALive-4231
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
const int MAX = 1e2+10;
const int MOD = 998244353;
int n;
char spk[MAX];
int dp[MAX][MAX][MAX];
char s[MAX][5];
int main(){
	//debug;
	while(~scanf("%d",&n)&&n){
		for(int i=0;i<MAX;i++) for(int j=0;j<MAX;j++) for(int k=0;k<MAX;k++) dp[i][j][k]=-1;
		for(int i=1;i<=n;i++){
			scanf("%s",s[i]);
		}
		scanf("%s",spk+1);
		int len=strlen(spk+1);
		//attention!!!
		if(len==1){
			printf("0\n");
			continue;
		}
		for(int t=2;t<=len;t++){
			for(int l=1;t+l-1<=len;l++){
				int r=l+t-1;
				if(t==2){
					for(int k=1;k<=n;k++){
						int v=s[k][0]-'A'+1;
						if(s[k][1]==spk[l] && s[k][2]==spk[r]) dp[l][r][v]=1;
					}
				} else{
					for(int j=l;j<r;j++){
						for(int k=1;k<=n;k++){
							int v=s[k][0]-'A'+1,x=s[k][1]-'A'+1,y=s[k][2]-'A'+1;
							int tmp=dp[l][r][v];if(tmp==-1)tmp=INF;
							if(l!=j && j+1!=r){
								if(dp[l][j][x]==-1 || dp[j+1][r][y]==-1) continue;
								dp[l][r][v]=min(max(dp[l][j][x],dp[j+1][r][y])+1,tmp);
							} else if(l==j){
								if(spk[l]-'A'+1==x && dp[j+1][r][y]!=-1){
									dp[l][r][v]=min(tmp,dp[j+1][r][y]+1);
								}
							} else if(j+1==r)
								if(spk[j+1]-'A'+1==y && dp[l][j][x]!=-1)
									dp[l][r][v]=min(tmp,dp[l][j][x]+1);
						}
					}
				}
			}
		}
		int ans=INF;
		for(int i=1;i<='T'-'A'+1;i++){
			if(dp[1][len][i]==-1) continue;
			ans=min(ans,dp[1][len][i]);
		}
		ans=(ans==INF)?-1:ans;
		printf("%d\n",ans);
	}
	return 0;
}
