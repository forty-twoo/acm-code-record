/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-29 15:54:41
 * @Description: dp
 * @Source: https://vjudge.net/problem/POJ-3467
 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
const int MAX=1e2+5;
const int MAXN=1e6+10;
const int MOD=1e9+7;
using namespace std;
int n,m,C,Q;
int gra[MAX][MAX];
int U[MAX][MAX],D[MAX][MAX],R[MAX][MAX],L[MAX][MAX];
int cnt[MAX][MAX];
int c[MAX];
void init(){
	for(int i=1;i<=n;i++){
		L[i][1]=R[i][m]=0;
		for(int j=2;j<=m;j++){
			if(gra[i][j]==gra[i][j-1])L[i][j]=L[i][j-1]+1;
			else L[i][j]=0;
		}
		for(int j=m-1;j>=1;j--){
			if(gra[i][j]==gra[i][j+1])R[i][j]=R[i][j+1]+1;
			else R[i][j]=0;
		}
	}
	for(int i=1;i<=m;i++){
		U[1][i]=D[n][i]=0;
		for(int j=2;j<=n;j++){
			if(gra[j][i]==gra[j-1][i])U[j][i]=U[j-1][i]+1;
			else U[j][i]=0;
		}
		for(int j=n-1;j>=1;j--){
			if(gra[j][i]==gra[j+1][i])D[j][i]=D[j+1][i]+1;
			else D[j][i]=0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cnt[i][j]=min(U[i][j],min(D[i][j],min(R[i][j],L[i][j])));
			c[gra[i][j]]+=cnt[i][j];
		}
	}
}
char op[3];
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	while(~scanf("%d%d%d%d",&n,&m,&C,&Q)){
		mst(c,0);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&gra[i][j]);
			}
		}
		init();
		while(Q--){
			scanf("%s",op);
			int x,y,v;
			if(op[0]=='Q'){
				scanf("%d",&x);
				printf("%d\n",c[x]);
			}else{
				scanf("%d%d%d",&x,&y,&v);
				if(v==gra[x][y]) continue;
				c[gra[x][y]]-=cnt[x][y];
				gra[x][y]=v;
				for(int i=2;i<=m;i++){
					if(gra[x][i]==gra[x][i-1]) L[x][i]=L[x][i-1]+1;
					else L[x][i]=0;
				}
				for(int i=m-1;i>=1;i--){
					if(gra[x][i]==gra[x][i+1]) R[x][i]=R[x][i+1]+1;
					else R[x][i]=0;
				}
				for(int i=2;i<=n;i++){
					if(gra[i][y]==gra[i-1][y]) U[i][y]=U[i-1][y]+1;
					else U[i][y]=0;
				}
				for(int i=n-1;i>=1;i--){
					if(gra[i][y]==gra[i+1][y]) D[i][y]=D[i+1][y]+1;
					else D[i][y]=0;
				}
				for(int i=1;i<=y-1;i++){
					c[gra[x][i]]-=cnt[x][i];
					cnt[x][i]=min(U[x][i],min(D[x][i],min(R[x][i],L[x][i])));
					c[gra[x][i]]+=cnt[x][i];
				}
				for(int i=y+1;i<=m;i++){
					c[gra[x][i]]-=cnt[x][i];
					cnt[x][i]=min(U[x][i],min(D[x][i],min(R[x][i],L[x][i])));
					c[gra[x][i]]+=cnt[x][i];
				}
				for(int i=1;i<=x-1;i++){
					c[gra[i][y]]-=cnt[i][y];
					cnt[i][y]=min(U[i][y],min(D[i][y],min(R[i][y],L[i][y])));
					c[gra[i][y]]+=cnt[i][y];
				}
				for(int i=x+1;i<=n;i++){
					c[gra[i][y]]-=cnt[i][y];
					cnt[i][y]=min(U[i][y],min(D[i][y],min(R[i][y],L[i][y])));
					c[gra[i][y]]+=cnt[i][y];
				}
				cnt[x][y]=min(U[x][y],min(D[x][y],min(R[x][y],L[x][y])));
				c[v]+=cnt[x][y];
			}
		}
	}
	return 0;
}
