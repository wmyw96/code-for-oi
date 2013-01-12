#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
 
const int MAX_N=2001,MAX_MM=20001,INF=20000;
int g[MAX_MM],next[MAX_MM],c[MAX_N],cost[MAX_MM],flow[MAX_MM];
int Q[MAX_MM*20],E[MAX_MM*20],pre[MAX_MM*20];
int ued[MAX_MM];
int d[MAX_N];
int n,nm,ansc,S,T;
 
void addedge(int x,int y,int f,int ct){
     g[nm]=y;
	 next[nm]=c[x];
	 c[x]=nm;
	 cost[nm]=ct;                  
	 flow[nm]=f;
	 nm++;
}
 
void add(int x,int y,int f,int c){
     addedge(x,y,f,c);
     addedge(y,x,0,-c);
}
 
int spfa(){
	memset(ued,0,sizeof ued);
	for (int i=1;i<=T;i++)
		d[i]=INF;
	d[S]=0;
	Q[1]=S;
	int ret=-INF;
	for (int l=1,r=1;l<=r;l++){
		int i=Q[l];
		ued[i]=0;
		for (int k=c[i];k!=-1;k=next[k]){
			int j=g[k];
			if (flow[k]>0 && d[i]+cost[k]<d[j]){
				if (!ued[j]) Q[++r]=j,ued[j]=1;
				pre[j]=i;
				E[j]=k;
				d[j]=d[i]+cost[k];
				if (j==T) ret=1; 
			}
		}
	}
	return ret;
}
 
void aug(){
	int ret=INF;
	for (int i=T;pre[i]!=0;i=pre[i])
		ret=min(ret,flow[E[i]]);
	for (int i=T;pre[i]!=0;i=pre[i]){
		flow[E[i]]-=ret;
		flow[E[i]^1]+=ret;
		ansc+=ret*cost[E[i]];
	}
}
 
int main(){
	int Ti,ct;
	scanf("%d",&Ti);
	while (Ti--){
		scanf("%d",&n);
		S=1,T=n+2;
		ansc=0;
		nm=0;
		memset(c,-1,sizeof c);
		for (int i=1;i<=n;i++){
			scanf("%d",&ct);
			add(1,i+1,ct,0);
			add(i+1,n+2,1,0);
			add(i+1,(i==n)?(2):(i+2),INF,1);
			add(i+1,(i==1)?(n+1):i,INF,1);
		}
		int ret=0;
		while (ret=spfa()!=-INF) aug();
		printf("%d\n",ansc);
	}
}

