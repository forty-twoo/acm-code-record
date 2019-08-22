/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-22 15:11
 * @Description: 单调队列优化dp
 * @Source: https://vjudge.net/problem/HYSBZ-1499
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f3f3f
#define eps 1e-8
typedef long long ll;
typedef  unsigned long long ull;
using namespace std;
const int MAX = 2e2+10;
int n,m,k;
char gra[MAX][MAX];
struct Node{
	int s,t,d;
}node[MAX];
int f[MAX][MAX][MAX];
int Q[MAX];
int main(){
	//debug;
	int x,y;
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&k);
	for(int i=1;i<=n;i++){
		scanf("%s",gra[i]+1);
	}
	for(int i=1;i<=k;i++){
		scanf("%d%d%d",&node[i].s,&node[i].t,&node[i].d);
	}
	int ans=0;
	mst(f,0xcf);
	f[0][x][y]=0;
	for(int i=1;i<=k;i++){
		int d=node[i].d;
		int delt=node[i].t-node[i].s+1;
		if(d==1){
			for(int j=1;j<=m;j++){
				int l=1,r=0;
				for(int t=n;t>=1;t--){
					if(gra[t][j]=='x'){
						l=1,r=0;continue;
					}
					while(l<=r && Q[l]-t>delt) l++;
					while(l<=r && f[i-1][Q[r]][j]+Q[r]-t<=f[i-1][t][j]) r--; //注意此处是<=f[i-1]......
					Q[++r]=t;
					f[i][t][j]=max(max(f[i][t][j],f[i-1][t][j]),f[i-1][Q[l]][j]+Q[l]-t);
					ans=max(ans,f[i][t][j]);
				}
			}
		} else if(d==2){
			for(int j=1;j<=m;j++){
				int l=1,r=0;
				for(int t=1;t<=n;t++){
					if(gra[t][j]=='x'){
						l=1,r=0;continue;
					}
					while(l<=r && t-Q[l]>delt) l++;
					while(l<=r && f[i-1][Q[r]][j]+t-Q[r]<=f[i-1][t][j]) r--;
					Q[++r]=t;
					f[i][t][j]=max(max(f[i][t][j],f[i-1][t][j]),f[i-1][Q[l]][j]+t-Q[l]);
					ans=max(ans,f[i][t][j]);
				}
			}

		} else if(d==3){
			for(int t=1;t<=n;t++){
				int l=1,r=0;
				for(int j=m;j>=1;j--){
					if(gra[t][j]=='x'){
						l=1,r=0;continue;
					}
					while(l<=r && Q[l]-j>delt) l++;
					while(l<=r && f[i-1][t][Q[r]]+Q[r]-j<=f[i-1][t][j]) r--;
					Q[++r]=j;
					f[i][t][j]=max(max(f[i-1][t][j],f[i][t][j]),f[i-1][t][Q[l]]+Q[l]-j);
					ans=max(ans,f[i][t][j]);
				}
			}

		} else if(d==4){
			for(int t=1;t<=n;t++){
				int l=1,r=0;
				for(int j=1;j<=m;j++){
					if(gra[t][j]=='x'){
						l=1,r=0;continue;
					}
					while(l<=r && j-Q[l]>delt) l++;
					while(l<=r && f[i-1][t][Q[r]]+j-Q[r]<=f[i-1][t][j]) r--;
					Q[++r]=j;
					f[i][t][j]=max(max(f[i][t][j],f[i-1][t][j]),f[i-1][t][Q[l]]+j-Q[l]);
					ans=max(ans,f[i][t][j]);
				}
			}
		}
	}
	printf("%d\n",ans);

	return 0;
}
