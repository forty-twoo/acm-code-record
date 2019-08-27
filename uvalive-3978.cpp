/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-27 15:08
 * @Description: dp hash
 * @Source: https://cn.vjudge.net/problem/UVALive-3978
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
const int MAX = 1e3+10;
const int MAXN = 3e4+10;
const int MOD = 998244353;
char str[1001],has[10001][101];
int n;
char b[101];
int vis[10001];
int f[MAX][MAX],g[MAX];

typedef pair<int,int> FE; //(first, last)
typedef pair<int,FE> P;   //(len, first, last)
typedef pair<P,string> PI; //(len, first, last, alpha)
map<PI,int> mp;

int ans[10001];
int tot;
int solve(int len,int tot){
	if(len==0){
		return tot;
	}
	for(int j=len;j>=1;j--){
		if(f[j][len] && g[j-1]==1){
			ans[tot]=f[j][len];
			return solve(j-1,tot+1);
		}
	}
}

int main(){
	//debug;
	int ks;
	scanf("%d",&ks);
	while(ks--){
		scanf("%s",str+1);
		scanf("%d",&n);
		mp.clear();mst(f,0);mst(g,0);mst(ans,0);mst(vis,0);
		for(int i=1;i<=n;i++){
			scanf("%s",has[i]+1);
			int len=strlen(has[i]+1);
			FE fe; P pp;
			fe.first=has[i][1]-'a'+1;fe.second=has[i][len]-'a'+1;
			pp.first=len;pp.second=fe;
			for(int j=0;j<len;j++) b[j]=has[i][j+1];
			sort(b,b+len);
			string alp="";
			for(int j=0;j<len;j++) alp+=b[j];
			PI pr; pr.first=pp;pr.second=alp;
			if(!mp[pr])
				mp[pr]=i;
			vis[mp[pr]]++;
		}
		int len=strlen(str+1);
		for(int i=1;i<=len;i++){
			for(int j=i;j<=min(i+100-1,len);j++){
				int fc=str[i]-'a'+1,ec=str[j]-'a'+1;
				int len=j-i+1;
				int t=0;
				for(int k=i;k<=j;k++){
					b[t]=str[k];
					t++;
				}
				sort(b,b+t);
				FE fe;fe=make_pair(fc,ec);
				P pp=make_pair(len,fe);
				string alp="";
				for(int k=0;k<t;k++) alp+=b[k];
				PI pr=make_pair(pp,alp);
				if(mp[pr]) f[i][j]=mp[pr];
			}
		}
		g[0]=1;
		for(int i=1;i<=len;i++){
			for(int j=1;j<=i;j++){
				if(f[j][i]!=0){
					g[i]+=g[j-1]*vis[f[j][i]];

				}
			}
		}
		if(g[len]==0){
			printf("impossible\n");
		} else if(g[len]>1){
			printf("ambiguous\n");
		} else{
			tot=solve(len,1);
			for(int i=tot-1;i>=1;i--){
				printf("%s",has[ans[i]]+1);
				if(i!=1) printf(" ");
				else puts("");
			}
		}

	}
	return 0;
}
