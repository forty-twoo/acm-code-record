/*
 * @Author: forty-twoo
 * @Date: 2019-09-05 13:32:36
 * @Description: 搜索
 * @Source: https://vjudge.net/problem/UVA-10798#author=541713140134
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
const int MAX = 3e2;
const int MAXN = 2e5+100;
const int MOD =1e9+9;
int n;
char gra[MAX][MAX];
int mid;
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int vis[22][22][22][22][22][22];
struct Node{
	int x,y;
	int nr,e,s,w;
	int val;
	Node(){
		x=y=nr=e=s=w=0;
	}
	Node(int x_,int y_,int n_,int e_,int s_,int w_){
		x=x_;y=y_;nr=n_;e=e_;s=s_;w=w_;
		val=max(max(nr,e),max(s,w));
	}
	bool operator<(const Node&N)const{
		return val>N.val;
	}
};

int bfs(){
	prique<Node> Q;
	Node ss={mid,mid,0,0,0,0};
	vis[mid][mid][0][0][0][0]=1;
	Q.push(ss);
	while(Q.size()){
		Node cur=Q.top();Q.pop();
		if(cur.x==1 || cur.x==n || cur.y==1 || cur.y==n){
			return cur.val;
		}
		Node tmp;
		for(int i=1;i<=4;i++){
			int xx=cur.x+dx[i];
			int yy=cur.y+dy[i];
			int nr=cur.nr,s=cur.s,e=cur.e,w=cur.w;
			if(gra[xx][yy]=='R') nr++;
			if(gra[n-xx+1][n-yy+1]=='R') s++;
			if(gra[yy][n+1-xx]=='R') e++;
			if(gra[n+1-yy][xx]=='R') w++;
			if(!vis[xx][yy][nr][e][s][w]){
				vis[xx][yy][nr][e][s][w]=1;
				tmp={xx,yy,nr,e,s,w};
				Q.push(tmp);
			}
		}

	}



}
int main(){
	//debug;
	while(~scanf("%d",&n) && n){
		for(int i=1;i<=n;i++){
			scanf("%s",gra[i]+1);
		}
		mid=(n+1)/2;
		mst(vis,0);
		int ans=bfs();
		printf("At most %d rose(s) trampled.\n",ans);

	}

	return 0;
}
