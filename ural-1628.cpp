/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-25 18:39
 * @Description: 思维	
 * @Source: https://vjudge.net/problem/URAL-1628
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
const int MAX = 2e5+10;
const int MOD = 998244353;
int n,m,k;
struct Node{
	int x,y;
}node[MAX];
typedef pair<int,int> PI;
map<PI,int> mp;
bool cmpx(Node &A,Node &B){
	if(A.x==B.x) return A.y<B.y;
	return A.x<B.x;
}
bool cmpy(Node &A,Node &B){
	if(A.y==B.y) return A.x<B.x;
	return A.y<B.y;
}

int main(){
	//debug;
	while(~scanf("%d%d%d",&n,&m,&k)){
		int ans=0;mp.clear();
		int x,y;
		for(int i=1;i<=k;i++){
			scanf("%d%d",&x,&y);
			node[i]={x,y};
			PI tmp=make_pair(x,y);
			mp[tmp]=1;
		}
		for(int i=0;i<=n+1;i++){
			x=i,y=0;node[++k]={x,y};
			PI tmp=make_pair(x,y);mp[tmp]=1;
			y=m+1;node[++k]={x,y};
			tmp=make_pair(x,y);mp[tmp]=1;
		}
		for(int i=1;i<=m;i++){
			x=0,y=i;node[++k]={x,y};
			PI tmp=make_pair(x,y);mp[tmp]=1;
			x=n+1;node[++k]={x,y};
			tmp=make_pair(x,y);mp[tmp]=1;
		}
		//calculate 1XL
		sort(node+1,node+1+k,cmpx);
		for(int i=2;i<=k;i++){
			int px=node[i-1].x,py=node[i-1].y;
			int x=node[i].x,y=node[i].y;
			if(x!=px) continue;
			else{
				if(y-py>2) ans+=1;
				else if(y-py==2){
					int ux=node[i].x-1,dx=node[i].x+1;
					int cy=node[i].y-1;
					PI tu=make_pair(ux,cy);PI td=make_pair(dx,cy);
					if(mp[tu] && mp[td]) ans+=1;
				}
			}	
		}
	
		//calculate LX1
		sort(node+1,node+1+k,cmpy);
		for(int i=2;i<=k;i++){
			int px=node[i-1].x,py=node[i-1].y;
			int x=node[i].x,y=node[i].y;
			if(y!=py) continue;
			else{
				if(x-px>2) ans+=1;
				else if(x-px==2){
					/*
					int ly=node[i].y-1,ry=node[i].y+1;
					int cx=node[i].x-1;
					PI tu=make_pair(cx,ly);PI td=make_pair(cx,ry);
					if(mp[tu] && mp[td]) ans+=1;
					*/
				}
			}	
		}	
		
		printf("%d\n",ans);
	
	}
	return 0;
}
