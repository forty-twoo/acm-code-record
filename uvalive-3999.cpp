/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-09-02 23:43
 * @Description: 转化为二分判定 hash
 * @Source: https://vjudge.net/problem/UVALive-3999
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
const int MAX =1e6+10;
const int MAXN = 3e5+100;
const int MOD =1e9+9;
int ks,n;
map<char,int> mp;
char str[10][MAX];
int len[10];
ll base[MAX];
ll f[10][MAX];
const int maxn=2500*2500+3;
const int maxd=15;
const int seed=2500*2500+3;//是一个大素数
typedef long long LL;
struct HASH//哈希表
{
	int head[seed];
	int size;
	struct  NODE
	{
		int key;
		int value;
		int next;
	}edges[maxn];
	void init()
	{
		memset(head,-1,sizeof(head));
		size=0;
	}
	void insert(int key,int value)//插入值
	{
		int h=key%seed;
		for(int i=head[h];i!=-1;i=edges[i].next)
		{
			if(edges[i].key==key)
			{
				edges[i].value=max(value,edges[i].value);
				return;
			}
		}
		edges[size].key=key;
		edges[size].value=value;
		edges[size].next=head[h];
		head[h]=size++;
	}
	int search(int key)//寻找
	{
		int h=key%seed;
		for(int i=head[h];i!=-1;i=edges[i].next)
		{
			if(edges[i].key==key)
			{
				return edges[i].value;
			}
		}
		return -1;
	}
}tr;
void init(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=len[i];j++){
			ll x=mp[str[i][j]];
			f[i][j]=((f[i][j-1]*131ll)+x)%MOD;
		}
	}

}
bool check(int x){
	tr.init();
	for(int j=1;j<=len[1]-x+1;j++){
		int r=j+x-1;
		int l=j;
		ll tp;
		tp=(f[1][r]-(f[1][l-1]*base[r-l+1])%MOD+MOD)%MOD;
		if(tr.search(tp)==-1){
			tr.insert(tp,1);
		}
	}
	for(int i=2;i<=n;i++){
		bool flg=false;
		for(int j=1;j<=len[i]-x+1;j++){
			int r=j+x-1;
			int l=j;
			ll tp;
			tp=(f[i][r]-(f[i][l-1]*base[r-l+1])%MOD+MOD)%MOD;
			if(tr.search(tp)==i-1){
				tr.insert(tp,i);
				if(i==n) return true;
				flg=true;
			}
		}
		if(!flg) return false;
	}
	return false;
}
int main(){
	//debug;
	base[0]=1;
	for(int i=1;i<=1000001;i++) base[i]=(base[i-1]*131ll)%MOD;
	scanf("%d",&ks);
	mp['A']=1,mp['C']=2,mp['G']=3,mp['T']=4;
	while(ks--){
		int minn=INF;
		int maxx=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",str[i]+1);
			len[i]=strlen(str[i]+1);
			minn=min(minn,len[i]);
			maxx=max(maxx,len[i]);
		}
		init();
		if(n==1){
			printf("%d\n",maxx);
			continue;
		}
		int l=0,r=minn;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(check(mid)) l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
