#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAX_N=501,MAX_M=100001,INF=1000000000;
int g[MAX_M],c[MAX_N],next[MAX_M],cost[MAX_M],flow[MAX_M],ud[MAX_N],d[MAX_N],pre[MAX_N],E[MAX_N];
int cM,cH,nm,Hx[MAX_N],Hy[MAX_N],Mx[MAX_N],My[MAX_N],Q[MAX_M*10];
int n,m,S,T,ansc;

void addedge(int x,int y,int f,int ct){
	g[nm]=y;
	next[nm]=c[x];
	c[x]=nm;
	flow[nm]=f;
	cost[nm]=ct;
	nm++;
}

void add(int x,int y,int f,int ct){
	//printf("%d %d %d %d\n",x,y,f,ct);
	addedge(x,y,f,ct);
	addedge(y,x,0,-ct);
}

int mht(int i,int j){
	return abs(Hx[i]-Mx[j])+abs(Hy[i]-My[j]);
}

int spfa(){
	memset(ud,0,sizeof ud);
	for (int i=1;i<=T;i++) d[i]=INF;
	d[S]=0;
	Q[1]=S;
	for (int l=1,r=1;l<=r;l++){
		int i=Q[l];
		ud[i]=0;
		for (int k=c[i];k!=-1;k=next[k]){
			int j=g[k];
			//printf("%d %d %d\n",j,k,flow[k]);
			//system("pause");
			if (flow[k]>0 && d[i]+cost[k]<d[j]){
				d[j]=d[i]+cost[k];
				if (!ud[j]) ud[j]=1,Q[++r]=j;
				pre[j]=i;
				E[j]=k;
			}
		}
	}
	return d[T]!=INF;
}

void aug(){
	int ret=INF;
	for (int i=T;i!=S;i=pre[i]) ret=min(ret,flow[E[i]]);
	for (int i=T;i!=S;i=pre[i]){
		flow[E[i]]-=ret;
		flow[E[i]^1]+=ret;
		//printf("%d - ",i,E[i]);
		ansc+=ret*cost[E[i]];
	}
	//printf("%d\n",ansc);
}

int main(){
	while (scanf("%d%d",&n,&m)!=EOF){
		if (n==0 && m==0) return 0;
		cH=cM=nm=0;
		for (int i=1;i<=n;i++){
			getchar();
			for (int j=1;j<=m;j++){
				char ch=getchar();
				if (ch=='H'){Hx[++cH]=i;Hy[cH]=j;}
				if (ch=='m'){Mx[++cM]=i;My[cM]=j;}
			}
		}
		memset(c,-1,sizeof c);
		
		S=cM+cH+1;
		T=S+1;
		
		for (int i=1;i<=cM;i++) add(S,i,1,0);
		for (int i=1;i<=cH;i++) add(i+cM,T,1,0);
		for (int i=1;i<=cM;i++)
			for (int j=1;j<=cH;j++)
				add(i,j+cM,1,mht(i,j));
		
		ansc=0;
		while (spfa()) aug();
		
		printf("%d\n",ansc);
	}
} 

