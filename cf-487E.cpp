/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-10-06 03:44:42
 * @Description: 无向图缩点重构+树链剖分
 * @Source: https://codeforces.com/contest/487/problem/E
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
const int MAX=2e5+10;
const int MAXN=5e5+10;
const int MOD=1e9+7;
using namespace std;
int a[MAX],n,m,Q,head[MAX],tot=0;
int dfn[MAX],low[MAX],num,sta[MAX],new_id[MAX];
vector<int> dcc[MAX];
int cnt,ctop,cut[MAX],root;
int top[MAX],son[MAX],fa[MAX],sz[MAX],dep[MAX],id[MAX],rk[MAX],cnt2;
int fa2[MAX],fbk[MAX];
multiset<int> S[MAX];
multiset<int>::iterator it;
struct Edge{
	int u,v,nxt;
}edge[MAXN];

void add(int u,int v){
	edge[++tot]={u,v,head[u]};
	head[u]=tot;
}

int dfs1(int u,int ff){
	sz[u]=1;dep[u]=dep[ff]+1;fa[u]=ff;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff) continue;
		sz[u]+=dfs1(v,u);
		if(sz[v]>sz[son[u]]){
			son[u]=v;
		}
	}
	return sz[u];
}
void dfs2(int u,int ff){
	top[u]=ff;
	id[u]=++cnt2;
	rk[cnt2]=u;
	if(son[u]){
		dfs2(son[u],ff);
	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v!=son[u] && v!=fa[u])
			dfs2(v,v);
	}
}
void tarjan(int x){
	dfn[x]=low[x]=++num;
	sta[++ctop]=x;
	if(x==root &&head[x]==0){
		dcc[++cnt].pb(x);
		return;
	}
	int flg=0;
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].v;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				flg++;
				if(x!=root || flg>1)cut[x]=1;
				cnt++;
				int z;
				do{
					z=sta[ctop--];
					S[cnt].insert(a[z]);
					dcc[cnt].pb(z);
				} while(z!=y);
				dcc[cnt].pb(x);
				S[cnt].insert(a[x]);

			}
		} else low[x]=min(low[x],dfn[y]);
	}
}
struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	int minv[MAX<<2];
	void pushup(int rt){
		minv[rt]=min(minv[lc],minv[rc]);
	}
	void build(int rt,int l,int r){
		if(l==r){
			minv[rt]=*S[rk[l]].begin();
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void change1(int rt,int l,int r,int x,int v){
		if(l==r){
			S[rk[x]].insert(v);
			int minn=*(S[rk[x]].begin());
			minv[rt]=minn;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) change1(lson,x,v);
		else change1(rson,x,v);
		pushup(rt);
	}
	int querymin(int rt,int l,int r,int L,int R){
		if(L>R)return INF;
		int ans=INF;
		if(L<=l && r<=R){
			ans=min(ans,minv[rt]);
			return ans;
		}
		int mid=(l+r)>>1;
		if(L<=mid)ans=min(ans,querymin(lson,L,R));
		if(R>mid)ans=min(ans,querymin(rson,L,R));
		return ans;
	}

}T;
char op[3];
void query(int x,int y){
	int ans=INF;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=min(ans,T.querymin(1,1,num,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	if(y<=cnt && fa2[y]!=0){
		ans=min(ans,*(S[fa2[y]].begin()));
	}
	ans=min(ans,T.querymin(1,1,num,id[y],id[x]));
	printf("%d\n",ans);
}
void build_new_val(int x,int f){
	fa2[x]=f;
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].v;
		if(y==f)continue;
		build_new_val(y,x);
		if(y>cnt){
			S[x].insert(fbk[y]);
		}
	}

}
int main(){
#ifndef ONLINE_JUDGE
	freopen("data.txt","r",stdin);
#endif

	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	int u,v;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			root=i;
			tarjan(i);
		}
	}
	num=cnt;
	//无割点
	if(cnt==1){
		S[1].clear();
		for(int i=1;i<=n;i++)S[1].insert(a[i]);
		for(int i=1;i<=Q;i++){
			int x,w,y;
			scanf("%s",op);
			if(op[0]=='C'){
				scanf("%d%d",&x,&w);
				if((it=S[1].find(a[x]))!=S[1].end())
					S[1].erase(it);
				a[x]=w;
				S[1].insert(w);
			} else{
				scanf("%d%d",&x,&y);
				if(x==y)printf("%d\n",a[x]);
				else
					printf("%d\n",*S[1].begin());
			}
		}
		return 0;
	}
	/********缩点后重新构图*******/
	for(int i=1;i<=n;i++){
		if(cut[i]){
			new_id[i]=++num;
			S[num].insert(a[i]);
			if(a[i]==0){
				printf("gedian\n");
			}

		}
	}
	mst(head,0);tot=0;
	for(int i=1;i<=cnt;i++){
		for(auto x:dcc[i]){
			if(cut[x]){
				add(i,new_id[x]);
				add(new_id[x],i);
				if((it=S[i].find(a[x]))!=S[i].end())
					S[i].erase(it);
				fbk[new_id[x]]=a[x];
			} else{
				new_id[x]=i;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!cut[i]){
			build_new_val(new_id[i],0);
			dfs1(new_id[i],0);
			dfs2(new_id[i],new_id[i]);
			break;
		}
	}

	/*********树链剖分*********/
	mst(T.minv,INF);
	T.build(1,1,num);
	for(int i=1;i<=Q;i++){
		int x,w,y;
		scanf("%s",op);
		if(op[0]=='C'){
			scanf("%d%d",&x,&w);
			if(!cut[x]){
				int t=new_id[x];
				if((it=S[t].find(a[x]))!=S[t].end())
					S[t].erase(it);
				T.change1(1,1,num,id[t],w);
				a[x]=w;
			} else{
				int t=new_id[x];
				if((it=S[t].find(a[x]))!=S[t].end())
					S[t].erase(it);
				T.change1(1,1,num,id[t],w);
				if(fa2[t]>0){
					if((it=S[fa2[t]].find(a[x]))!=S[fa2[t]].end())
						S[fa2[t]].erase(it);
					T.change1(1,1,num,id[fa2[t]],w);
				}
				a[x]=w;

			}
		} else{
			scanf("%d%d",&x,&y);
			if(x==y){
				printf("%d\n",a[x]);
				continue;
			} else{
				query(new_id[x],new_id[y]);
			}
		}
	}

	return 0;
}
