/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-09-04 14:16
 * @Description: 二分+排序
 * @Source:
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
const int MAX =1e5+10;
const int MAXN = 3e5+100;
const int MOD =1e9+9;
int n,m;
string pat;
struct Node{
	string str;
	int v;
	int id;
}prestr[20][MAX];
string cun[MAX];
int precnt[20];
bool cmppre(const Node&x,const Node&y){
	if(x.str==y.str) {
		if(x.v!=y.v)
			return x.v>y.v;
		else return cun[x.id]<cun[y.id];
	}
	return x.str<y.str;
}
bool check(int x){
	int len=pat.length();
	if(prestr[len][x].str<pat) return false;
	else return  true;
}
void solve(){
	int len=pat.length();
	int l=1,r=precnt[len];
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	for(int i=l;i<=min(precnt[len],l+9);i++){
		if(prestr[len][i].str!=pat) break;
		int id=prestr[len][i].id;
		cout<<cun[id]<<endl;
	}
}
int main(){
	//debug;
	ios::sync_with_stdio(0);
	cin>>n;
	string tmp;int v;
	for(int i=1;i<=n;i++){
		cin>>tmp;
		cin>>v;
		cun[i]=tmp;
		int len=tmp.length();
		for(int j=1;j<=len;j++){
			string subs=tmp.substr(0,j);
			int t=precnt[j];
			prestr[j][t+1]={subs,v,i};
			precnt[j]++;
		}
	}
	for(int i=1;i<=15;i++){
		if(precnt[i]>0) sort(prestr[i]+1,prestr[i]+1+precnt[i],cmppre);
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>pat;
		solve();
		if(i!=m) cout<<endl;
	}

	return 0;
}
