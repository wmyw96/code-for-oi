#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
using namespace std;
struct data{
	int num,sum,pre;
};

const int MAX_N=2000001,MAX_NLINE=50001<<2,MAX_NN=50001;
int S[MAX_N],Lc[MAX_N],Rc[MAX_N];
data T[MAX_N];
int root[MAX_NLINE],pre[MAX_NN],a[MAX_NN];
map<int,int> M;
map<int,int> MM;
int n,m,nm;

data mp(int x,int y,int w){
	data ret;
	ret.num=x;ret.pre=y;ret.sum=w;
	return ret;
}

void Up(int x){
	if (!x) return;
	S[x]=S[Lc[x]]+S[Rc[x]]+1;
	T[x].sum=T[Lc[x]].sum+T[Rc[x]].sum+T[x].num;
}

void Zig(int &x){
	int y=Lc[x];Lc[x]=Rc[y];Rc[y]=x;
	Up(x);Up(y);x=y;
}

void Zag(int &x){
	int y=Rc[x];Rc[x]=Lc[y];Lc[y]=x;
	Up(x);Up(y);x=y;
}

void Balance(int &x){
	if (S[Lc[Lc[x]]]>S[Rc[x]]) Zig(x);
	if (S[Rc[Rc[x]]]>S[Lc[x]]) Zag(x);
	Up(x);
}

void Insert(int &x,data dat){
	if (!x) T[x=++nm]=dat;
	else Insert(((T[x].pre>dat.pre)?Lc[x]:Rc[x]),dat);
	Balance(x);
}

int find(int x,int dat){
	if (!x) return 0;
	return find(((dat<T[x].pre)?Lc[x]:Rc[x]),dat) + ((dat<T[x].pre)?0:T[Lc[x]].sum+T[x].num);
}

void Build(int x,int l,int r){
	for (int i=l;i<=r;i++) Insert(root[x],mp(a[i],pre[i],a[i]));
	if (l==r) return;
	int mid=(l+r)/2;
	Build(x*2,l,mid);Build(x*2+1,mid+1,r);
}

int query(int x,int l,int r,int f,int t){
	if (f<=l && r<=t) return find(root[x],f-1);
	int mid=(l+r)/2;int ret=0;
	if (f<=mid) ret+=query(x*2,l,mid,f,t);
	if (t>mid) ret+=query(x*2+1,mid+1,r,f,t);
	return ret;
}

void 
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++){
		pre[i]=M[a[i]];
		M[a[i]]=i;
		if (!MM[a[i]]) MM[a[i]]=++cnt;
		ST[MM[a[i]]].insert(i);
	}
	Build(1,1,n);
	scanf("%d",&m);
	for (int i=1;i<=m;i++){
		char ch;int x,y;
		scanf(" %c%d%d",&ch,&x,&y);
		if (ch=='Q') printf("%d\n",query(1,1,n,x,y));
				else change(x,y);
	}
}
/*
5
1 2 4 2 3                                                                              
3
Q 2 4
Q 2 4
*/

5
1 2 4 2 3                                                                              
3
Q 2 4
Q 2 4
*/

