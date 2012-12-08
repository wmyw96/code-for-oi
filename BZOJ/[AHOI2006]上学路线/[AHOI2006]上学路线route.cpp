#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int MAX_N=1001,MAX_M=1000001,INF=2147483647;
int ans[MAX_N],d[MAX_N],instack[MAX_N];
int n,m;
queue<int> Q;
 
struct Gragh{
	int w[MAX_M],g[MAX_M],next[MAX_M],c[MAX_M],cost[MAX_M];
	int nm;
	inline Gragh(){
		nm=0;
	}
	void addedge(int x,int y,int ww,int co){
		g[++nm]=y;
		next[nm]=c[x];
		c[x]=nm;
		cost[nm]=co;
		w[nm]=ww;
	}
}E,EE,EEE;

void bfs_spfa(){
	Q.push(1);
	int p=0;
	for (int i=2;i<=n;i++) ans[i]=INF;
	while (!Q.empty()){
		int i=Q.front();Q.pop();
		instack[i]=0;
		p++;
		for (int k=E.c[i];k;k=E.next[k]){
			int j=E.g[k];
			//printf("** %d %d %d \n",p,i,j);
			if (ans[i]+E.w[k]<ans[j]){
				ans[j]=ans[i]+E.w[k];
				//printf("# %d %d %d\n",j,i,ans[j]);
				if (!instack[j]) 
					Q.push(j),instack[j]=1;
				EEE.c[j]=0;
				EEE.addedge(j,i,0,E.cost[k]);
				//for (int kk=EEE.c[j];kk;kk=EEE.next[kk]) printf("%d ",EEE.g[kk]);
				//printf("\n");
			}
			else if (ans[i]+E.w[k]==ans[j]){
				//printf("# %d %d\n",j,i);
				EEE.addedge(j,i,0,E.cost[k]);
				//for (int kk=EEE.c[j];kk;kk=EEE.next[kk]) printf("%d ",EEE.g[kk]);
				//printf("\n");
			}
		}
	}
	printf("%d\n",ans[n]);
}

bool bfs(){
	memset(d,-1,sizeof d);
	Q.push(1);
	d[1]=0;
	while (!Q.empty()){
		int i=Q.front();
		Q.pop();
		for (int k=EE.c[i];k;k=EE.next[k]){
			int j=EE.g[k];
			if (d[j]==-1 && EE.cost[k])
				Q.push(j),d[j]=d[i]+1; 
		}
	}
	return d[n]!=-1;
}

int dfs(int i,int tmp){
	if (i==n) return tmp;
	int ret;
	for (int k=EE.c[i];k;k=EE.next[k]){
		int j=EE.g[k];
		if (d[j]==d[i]+1 && EE.cost[k]>0 && (ret=dfs(j,min(tmp,EE.cost[k])))){
			EE.cost[k]-=ret,
			EE.cost[k^1]+=ret;
			return ret;
		}
	} 
}

int main(){
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int x,y,w,c;
		scanf("%d%d%d%d",&x,&y,&w,&c);
		E.addedge(x,y,w,c);
	}
	
	bfs_spfa();
	
	for (int i=1;i<=n;i++){
		for (int k=EEE.c[i];k;k=EEE.next[k]){
			int j=EEE.g[k];
			EE.addedge(j,i,0,EEE.cost[k]);
			//printf("%d %d %d\n",j,i,EEE.cost[k]);
			EE.addedge(i,j,0,0);
		}
		//printf("-- %d --\n",i);
		//for (int kk=EEE.c[i];kk;kk=EEE.next[kk]) printf("%d ",EEE.g[kk]);
		//printf("\n");
	}
	int ar=0,ret=0;
	while (bfs()){
		ret=0;
		while (ret=dfs(1,INF)) ar+=ret;
	}
	printf("%d\n",ar);
}
/*

6 8
1 2 1 3
2 6 1 5
1 3 1 1
3 4 1 1
4 6 1 1
5 6 1 2
1 5 1 4
2 1 1 3

*/

