#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>

using namespace std;

const int MAX_N=1001,MAX_M=1000001;
const double SUP=1000000000.0,EX=0.0000000001;
int nm,S,T,R,C,k;
int next[MAX_M],c[MAX_N],g[MAX_N],d[MAX_N],Q[MAX_M];
double flow[MAX_M];
 
void addedge(int x,int y,double w){
	g[nm]=y;
	next[nm]=c[x];
	c[x]=nm;
	flow[nm]=w;
	nm++;
}

void add(int x,int y,double w){
	addedge(x,y,w);
	addedge(y,x,0.0);
}

int bfs(){
	Q[1]=S;
	memset(d,-1,sizeof d);
	d[S]=0;
	for (int l=1,r=1;l<=r;l++){
		int i=Q[l];
		for (int k=c[i];k!=-1;k=next[k]){
			int j=g[k];
			if (d[j]==-1 && flow[k]>EX) d[j]=d[i]+1,Q[++r]=j;
		}
	}
	return d[T]!=-1;
}

double dfs(int i,double now){
	if (now<EX || i==T) return now;
	double w=0.0;
	for (int k=c[i];k!=-1 && w<now;k=next[k]){
		int j=g[k];
		double ret=min(flow[k],now-w);
		if (ret>EX && d[j]==d[i]+1)
			if ((ret=dfs(j,ret))>EX){
				flow[k]-=ret;flow[k^1]+=ret,w+=ret;
			}
	} 
	if (w>EX) d[i]=-1;
	return w;
}

int main(){
	int Ti;
	scanf("%d",&Ti);
	while (Ti--){
		scanf("%d%d%d",&R,&C,&k);
		S=R+C+1;T=S+1; 
		
		memset(c,-1,sizeof c);
		nm=0;
		double r;int x,y;
		for (int i=1;i<=R;i++) scanf("%lf",&r),add(S,i,log(r));
		for (int i=1;i<=C;i++) scanf("%lf",&r),add(i+R,T,log(r));
		for (int i=1;i<=k;i++){
			scanf("%d%d",&x,&y);
			add(x,y+R,SUP);
		} 
		
		double ans=0.0;
		
		
		while (bfs()){
			while (1){
				double ret=dfs(S,SUP);
				if (ret>EX) ans+=ret; else break;
			}
		}
		printf("%.4lf\n",exp(ans));
	}
} 

