/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-30 00:18
 * @Description: LCS型dp
 * @Source: http://codeforces.com/problemsets/acmsguru/problem/99999/214
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
const int MAX = 1e3+500;
const int MAXN =2e3+50;
const int MOD = 998244353;
char alp[300];
char A[MAXN],B[MAXN];
int val[400][400];
int dp[MAXN][MAXN];
int minA[MAXN],minB[MAXN];
char chA[MAXN],chB[MAXN];
vector<char>ansA,ansB;
int idA[MAXN],idB[MAXN];

void print(int i,int j){
	if(i==0 && j==0) return;
	int curv=dp[i][j];
	if(j==0){
		ansA.push_back(A[i]); ansB.push_back(chA[i]);
		print(i-1,j);
	} else if(i==0){
		ansA.push_back(chB[j]); ansB.push_back(B[j]);
		print(i,j-1);
	} else{
		if(curv==dp[i-1][j-1]+val[idA[i]][idB[j]]){
			ansA.push_back(A[i]); ansB.push_back(B[j]);
			print(i-1,j-1);
		} else if(curv==dp[i-1][j]+minA[i]){
			ansA.push_back(A[i]); ansB.push_back(chA[i]);
			print(i-1,j);
		} else{
			ansA.push_back(chB[j]); ansB.push_back(B[j]);
			print(i,j-1);
		}

	}
}
int main(){
	//debug;
	scanf("%s",alp+1);
	int lalp=strlen(alp+1);
	scanf("%s%s",A+1,B+1);
	int x;
	for(int i=1;i<=lalp;i++){
		for(int j=1;j<=lalp;j++){
			scanf("%d",&val[i][j]);
		}
	}
	mst(dp,INF);mst(minA,INF);mst(minB,INF);
	int lena=strlen(A+1);
	int lenb=strlen(B+1);
	for(int i=1;i<=lena;i++){
		for(int j=1;j<=lalp;j++){
			if(A[i]==alp[j]){
				idA[i]=j;break;
			}
		}
	}
	for(int i=1;i<=lenb;i++){
		for(int j=1;j<=lalp;j++){
			if(B[i]==alp[j]){
				idB[i]=j;break;
			}
		}
	}

	for(int i=1;i<=lena;i++){
		for(int j=1;j<=lalp;j++){
			if(val[idA[i]][j]<minA[i]){
				minA[i]=val[idA[i]][j];
				chA[i]=alp[j];
			}
		}
	}
	for(int i=1;i<=lenb;i++){
		for(int j=1;j<=lalp;j++){
			if(val[j][idB[i]]<minB[i]){
				minB[i]=val[j][idB[i]];
				chB[i]=alp[j];
			}
		}
	}
	dp[0][0]=0;
	for(int i=1;i<=lena;i++) dp[i][0]=dp[i-1][0]+minA[i];
	for(int i=1;i<=lenb;i++) dp[0][i]=dp[0][i-1]+minB[i];
	for(int i=1;i<=lena;i++){
		for(int j=1;j<=lenb;j++){
			dp[i][j]=min(dp[i-1][j-1]+val[idA[i]][idB[j]],min(dp[i-1][j]+minA[i],dp[i][j-1]+minB[j]));
		}
	}
	printf("%d\n",dp[lena][lenb]);
	print(lena,lenb);
	for(int i=ansA.size()-1;i>=0;i--)printf("%c",ansA[i]);
	puts("");
	for(int i=ansB.size()-1;i>=0;i--)printf("%c",ansB[i]);
	puts("");

	return 0;
}
