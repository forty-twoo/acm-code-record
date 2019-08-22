/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-22 20:37
 * @Description:  贪心 优先队列
 * @Source: https://vjudge.net/problem/POJ-3110
 */

 //#include<bits/stdc++.h>
#include<iostream>
#include<cmath>
#include<cstdio>
#include<sstream>
#include<cstdlib>
#include<string>
#include<string.h>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<list>
#include<queue>
#include<ctime>

#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
using namespace std;
const int MAX = 3e5+10;
const int MOD = 998244353;
int n;
char subj[MAX];
struct Node{
	int dle;
	int td;
}node[MAX];
bool cmp1(Node &x,Node&y){
	return x.dle>y.dle;
}
struct Nd{
	int td;
	bool operator<(const Nd&x) const{
		return td<x.td;
	}

}nd[MAX];
prique<Nd> Q;
const int B=5e4;

bool spe(int x){
	if(x%400==0 || (x%4==0 && x%100!=0)) return true;
	else return false;
}
int fst1[13],fst2[13];
int cun1[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int cun2[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int nian[300];

void init(){
	nian[0]=B;
	for(int i=1901;i<=2100;i++){
		if(spe(i-1)) nian[i-1900]=nian[i-1-1900]+366;
		else nian[i-1900]=nian[i-1-1900]+365;
	}
	for(int i=1;i<=12;i++){
		fst1[i]=fst1[i-1]+cun1[i];
		fst2[i]=fst2[i-1]+cun2[i];
	}
}
int get_day(int day,int mon,int year){
	int x=0;
	if(spe(year)) x=nian[year-1900]+fst1[mon-1]+day;
	else x=nian[year-1900]+fst2[mon-1]+day;
	return x;
}

void get_ans(int v){
	int dl;
	int cnt=0;
	if(v>0){
		for(int i=1;i<=210;i++){
			for(int j=1;j<=12;j++){
				if(spe(i+1900-1)) dl=cun1[j];
				else dl=cun2[j];
				for(int k=1;k<=dl;k++){
					++cnt;
					if(cnt==v){
						printf("%02d.%02d.%04d\n",k,j,(1900+i-1));return;
					}
				}
			}
		}
	} else{
		v=-v;v+=1;
		for(int i=1899;i>=1600;i--){
			for(int j=12;j>=1;j--){
				if(spe(i)) dl=cun1[j];
				else dl=cun2[j];
				for(int k=dl;k>=1;k--){
					++cnt;
					if(cnt==v){
						printf("%02d.%02d.%04d\n",k,j,i);return;
					}
				}
			}
		}

	}
}

int main(){
	debug;
	init();
	while(~scanf("%d",&n)){
		while(Q.size())Q.pop();
		int t;
		int maxx=0;
		int cnt=0;
		int mon,day,year;
		for(int i=1;i<=n;i++){
			scanf("%s",subj);
			scanf("%d.%d.%d",&day,&mon,&year);
			scanf("%d",&t);
			int x=get_day(day,mon,year);
			maxx=max(maxx,x);
			Node tmp;
			tmp.dle=x,tmp.td=x-t;
			node[i]=tmp;
		}
		sort(node+1,node+1+n,cmp1);
		int s=1;
		bool f=true;int val=0;
		for(int i=maxx;i>=1;i--){
			if(node[s].dle==i){
				Nd tmp;tmp.td=node[s].td;
				Q.push(tmp);
				s++;
			} else{
				if(Q.size()){
					Nd cur=Q.top();Q.pop();
					if(cur.td>i){
						f=false;break;
					} else{
						cnt++;
					}
				}
			}
			if(cnt==n){
				val=i;break;
			}
		}
		val-=B;
		if(!f){
			printf("Impossible\n");
		} else{
			get_ans(val);
		}
	}


	return 0;
}
