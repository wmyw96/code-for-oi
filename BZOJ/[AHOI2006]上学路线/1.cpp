#include<cstdio>
#include<queue>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=500;
struct Edge{ int t,c,Len; bool e; Edge(int _t,int _Len,int _c,Edge* _next): t(_t),Len(_Len),next(_next),c(_c),e(false){} Edge*next,*op; 
/*void addFlow(int _c) { c-=_c; op->c+=_c; }*/}*E[maxn];
int n,m,vs,vt;
void InsEdge(int s,int t,int c,int Len){ 
	E[s]=new Edge(t,Len,c,E[s]); 
	E[t]=new Edge(s,Len,c,E[t]); 
	E[s]->op=E[t];E[t]->op=E[s];
}
void Init(){ 
	scanf("%d %d",&n,&m);
	int s,t,Len,c; vs=0,vt=n-1; 
	while(m--) { 
		scanf("%d %d %d %d",&s,&t,&Len,&c); 
		InsEdge(s-1,t-1,c,Len); 
	}
}
const int inf=~0U>>2;
int DistToStart[maxn],DistToEnd[maxn];
void Spfa(int Dist[maxn],int vs){ 
	queue<int> Q; bool inQ[maxn]={0}; 
	for(int i=0;i<n;i++) Dist[i]=inf;
	 Dist[vs]=0;inQ[vs]=true;Q.push(vs); 
	 while(Q.size()) { 
			int t=Q.front();Q.pop();
			inQ[t]=false;
			int cost=Dist[t]; 
			for(Edge*i=E[t];i;i=i->next) 
			{ int ncost=cost+i->Len; if(ncost<Dist[i->t]) { Dist[i->t]=ncost; if(!inQ[i->t]) inQ[i->t]=true,Q.push(i->t); } } 
	}
}
void BuildGraph(){ 
	Spfa(DistToStart,vs); 
	Spfa(DistToEnd,vt); 
	int cost=DistToStart[vt]; 
	for(int i=0;i<n;i++) 
	for(Edge*e=E[i];e;e=e->next) 
	if(DistToStart[i]+e->Len+DistToEnd[e->t]==cost) 
	{ e->e=true; e->op->e=true; e->op->c=0; } 
	cout<<cost<<endl;
}
int h[maxn],vh[maxn],v;
	
int aug(int no,int m){ 
	if(no==vt) return m; 
	int l=m; 
	for(Edge*i=E[no];i;i=i->next)
	if(i->e&&i->c&&h[no]==h[i->t]+1) 
	{ int d=aug(i->t,min(l,i->c)); i->c-=d,i->op->c+=d,l-=d; if(!l||h[vs]>=v) return m-l; } 
	int minh=v; 
	for(Edge*i=E[no];i;i=i->next)
	if(i->e&&i->c) minh=min(minh,h[i->t]+1); 
	if(!--vh[h[no]]) h[vs]=v; vh[h[no]=minh]++; return m-l;
}
long long CalFlow(){ 
	memset(h,0,sizeof(h)); 
	memset(vh,0,sizeof(vh)); 
	v=n;vh[0]=v;long long flow=0; 
	while(h[vs]<v) flow+=aug(vs,inf); return flow;
}
int main(){ //freopen("1.in","r",stdin); 
Init(); BuildGraph(); cout<<CalFlow()<<endl;
}
