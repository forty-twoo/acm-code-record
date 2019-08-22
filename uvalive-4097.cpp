/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-22 14:23
 * @Description: 贪心 set
 * @Source: https://vjudge.net/problem/UVALive-4097
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
typedef  unsigned long long ull;
using namespace std;
const int MAX = 5e2+10;
const int MOD = 998244353;
int n,m,a[MAX];
multiset<int> S;

int main(){
	debug;
	while(~scanf("%d%d",&n,&m)){
		if(!n && !m) break;
		S.clear();
		for(int i=1;i<=m;i++){
			scanf("%d",&a[i]);
			S.insert(a[i]);
		}
		int cnt=n;
		sort(a+1,a+1+m);
		multiset<int>::iterator it;
		int pre=INF;
		while(1){
			cnt=n;
			while(S.size()<n){
				int cur=*S.begin();
				S.erase(S.begin());
				for(int i=1;i<=m;i++){
					S.insert(cur+a[i]);
				}
			}
			int tmp=0;
			for(auto t: S){
				tmp+=t;cnt--;
				if(!cnt) break;
			}
			if(tmp<pre) {
				pre=tmp;
				int cur=*S.begin();
				S.erase(S.begin());
				for(int i=1;i<=m;i++){
					S.insert(cur+a[i]);
				}
			} else{
				break;
			}
		}
		printf("%d\n",pre);
	}
	return 0;

}
