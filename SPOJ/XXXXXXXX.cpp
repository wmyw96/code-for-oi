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
typedef long long LL;
struct data{
	int num,pre;
	LL sum;
};
const int MAX_N=2000001,MAX_NLINE=50001<<2,MAX_NN=50001;
int S[MAX_N],Lc[MAX_N],Rc[MAX_N];
data T[MAX_N];
int root[MAX_NLINE],pre[MAX_NN],a[MAX_NN],nxt[MAX_NN];
map<int,int> M;
map<int,int> MM;
set<int> ST[MAX_NN];
set<int>::iterator tmp;
int n,m,nm,cnt;

bool operator < (data x,data y){
	if (x.pre==y.pre) return x.num<y.num;
	return x.pre<y.pre;
}

bool operator > (data x,data y){
	if (x.pre==y.pre) return x.num>y.num;
	return x.pre>y.pre;
}

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
	else Insert(((T[x]>dat)?Lc[x]:Rc[x]),dat);
	Balance(x);
}

LL  find(int x,int dat){
	if (!x) return 0;
	return find(((dat<T[x].pre)?Lc[x]:Rc[x]),dat) + ((dat<T[x].pre)?0:T[Lc[x]].sum+T[x].num);
}

void Build(int x,int l,int r){
	for (int i=l;i<=r;i++) Insert(root[x],mp(a[i],pre[i],a[i]));
	if (l==r) return;
	int mid=(l+r)/2;
	Build(x*2,l,mid);Build(x*2+1,mid+1,r);
}

LL  query(int x,int l,int r,int f,int t){
	if (f<=l && r<=t) return find(root[x],f-1);
	int mid=(l+r)/2;LL ret=0;
	if (f<=mid) ret+=query(x*2,l,mid,f,t);
	if (t>mid) ret+=query(x*2+1,mid+1,r,f,t);
	return ret;
}

int same(data x,data y){
	return x.pre==y.pre && x.num==y.num;
}

data Delete(int &x,data v){
	
     data ret;
     if (same(v,T[x]) || (v<T[x] && !Lc[x]) || (v>T[x] && !Rc[x])){
        ret=T[x];
        if (!Lc[x] || !Rc[x]) x=Lc[x]+Rc[x];
                     else T[x]=Delete(Lc[x],mp(T[x].num,T[x].pre+100,0));
     }
     else ret=Delete(v<T[x]?Lc[x]:Rc[x],v);
     Balance(x);
     return ret;
}

void change(int i,int dat){
	int pi=pre[i];
	int ni=nxt[i];
	
    tmp=ST[MM[a[i]]].lower_bound(i);
    
	ST[MM[a[i]]].erase(tmp);
	printf("-- %d --\n",MM[a[i]]);
	
	if (MM[dat]==0) MM[dat]=++cnt;
	tmp=ST[MM[dat]].lower_bound(i);
	pre[i]=(tmp!=ST[MM[dat]].end())?*tmp:0;
	
	tmp=ST[MM[dat]].lower_bound(i);
	if (tmp!=ST[MM[dat]].end()){
		tmp++;
		nxt[i]=(tmp!=ST[MM[dat]].end())?*tmp:n+1;
	}
	else nxt[i]=n+1;
	ST[MM[dat]].insert(i);
	
	for (int l=1,r=n,x=1;;){
		
		Delete(root[x],mp(a[i],pi,0));
		Insert(root[x],mp(dat,pre[i],a[i]));
		if (l==r) break;
		int mid=(l+r)/2;
		if (i<=mid) r=mid,x*=2; else l=mid+1,x=x*2+1;
	}
	
	nxt[pi]=ni;
	int PI=ni;
	for (int l=1,r=n,x=1;;){
		Delete(root[x],mp(a[PI],pre[PI],0));
		Insert(root[x],mp(a[PI],pi,a[PI]));
		if (l==r) break;
		int mid=(l+r)/2;
		if (PI<=mid) r=mid,x*=2; else l=mid+1,x=x*2+1;
	}
	pre[ni]=pi;
	
}
int main(){
	freopen("xxxxxxxx.in","r",stdin);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++){
		pre[i]=M[a[i]];
		nxt[M[a[i]]]=1;
		M[a[i]]=i;
		if (!MM[a[i]]) MM[a[i]]=++cnt;
		ST[MM[a[i]]].insert(i);
	}
	for (int i=1;i<=n;i++) if (nxt[i]==0) nxt[i]=n+1;
	Build(1,1,n);
	scanf("%d",&m);
	for (int i=1;i<=m;i++){
		char ch;int x,y;
		scanf(" %c%d%d",&ch,&x,&y);
		putchar(ch);putchar('\n');
		if (ch=='Q') printf("%I64d\n",query(1,1,n,x,y));
				else change(x,y);
	}
}
/*
5
1 2 4 2 3                                                                              
3
Q 2 4
U 4 7
Q 2 4
*/

