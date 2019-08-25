/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-25 18:10
 * @Description: 思维 模拟
 * @Source: https://vjudge.net/problem/UVA-12198
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
int n,num;
char str[10];
int two,one;
void drop(int num){
	two+=num;
	printf("DROP %d %d\n",2,num);
}
void take(int num){
	if(one<num){
		if(one!=0)
			printf("TAKE %d %d\n",1,one);
		int ned=num-one;
		printf("MOVE %d->%d %d\n",2,1,two);
		one=two-ned;two=0;
		printf("TAKE %d %d\n",1,ned);
	}else{
		printf("TAKE %d %d\n",1,num);
		one-=num;
	}
}

int main(){
	//debug;
	while(~scanf("%d",&n)&&n){
		two=one=0;
		for(int i=1;i<=n;i++){
			scanf("%s%d",str,&num);
			if(str[0]=='D'){
				drop(num);
			}else{
				take(num);
			}
		}
		puts("");
	}
	return 0;
}
