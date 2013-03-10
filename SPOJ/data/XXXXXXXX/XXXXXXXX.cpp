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
const int MAX_N=4000001,MAX_NLINE=50001<<2,MAX_NN=50001;
int S[MAX_N],Lc[MAX_N],Rc[MAX_N];
data T[MAX_N];
int root[MAX_NLINE],a[MAX_NN],pre[MAX_NN];
map<int,int> MM;
set<int> ST[MAX_NLINE];
set<int>::iterator tmp;
int n,m,nm,cnt;
int DEL;

bool operator < (data x,data y){
	if (x.pre==y.pre) return x.num<y.num;
	return x.pre<y.pre;
}

bool operator > (data x,data y){
	if (x.pre==y.pre) return x.num>y.num;
	return x.pre>y.pre;
}

inline int PRE(int i){
	tmp=ST[MM[a[i]]].lower_bound(i);
	if (*tmp>=i) tmp--;
	return *tmp;
}

inline int NXT(int i){
	tmp=ST[MM[a[i]]].lower_bound(i);
	if (*tmp==i) tmp++;
	return *tmp;
}

inline data mp(int x,int y,int w){
	data ret;
	ret.num=x;ret.pre=y;ret.sum=w;
	return ret;
}

inline void Up(int x){
	if (!x) return;
	S[x]=S[Lc[x]]+S[Rc[x]]+1;
	T[x].sum=T[Lc[x]].sum+T[Rc[x]].sum+T[x].num;
}

inline void Zig(int &x){
	int y=Lc[x];Lc[x]=Rc[y];Rc[y]=x;
	Up(x);Up(y);x=y;
}

inline void Zag(int &x){
	int y=Rc[x];Rc[x]=Lc[y];Lc[y]=x;
	Up(x);Up(y);x=y;
}

inline void Balance(int &x){
	if (S[Lc[Lc[x]]]>S[Rc[x]]) Zig(x);
	if (S[Rc[Rc[x]]]>S[Lc[x]]) Zag(x);
	Up(x);
}

inline void Maintain(int &x, bool d){
	if(d){
		if(S[Rc[Rc[x]]] > S[Lc[x]])
			Zag(x);
		else
			if(S[Lc[Rc[x]]] > S[Lc[x]])
				Zig(Rc[x]),Zag(x);
	}else{
		if(S[Lc[Lc[x]]] > S[Rc[x]])
			Zig(x);
		else
			if(S[Rc[Lc[x]]] > S[Rc[x]])
				Zag(Lc[x]),Zig(x);
	}
	Up(x);
}

inline void Insert(int &x,data dat){
	if (!x) T[x=++nm]=dat,Up(x);
	else Insert(((T[x]>dat)?Lc[x]:Rc[x]),dat),Maintain(x, dat > T[x]);
}

inline LL  find(int x,int dat){
	if (!x) return 0;
	return find(((dat<T[x].pre)?Lc[x]:Rc[x]),dat) + ((dat<T[x].pre)?0:T[Lc[x]].sum+T[x].num);
}

inline int same(data x,data y){
	return (x.pre==y.pre && x.num==y.num);
}

inline data Delete(int &x,data v){
     data ret;
     if (same(v,T[x]) || (v<T[x] && !Lc[x]) || (v>T[x] && !Rc[x])){
        ret=T[x];
        if (!Lc[x] || !Rc[x]) x=Lc[x]+Rc[x];
                     else T[x]=Delete(Lc[x],mp(T[x].num,T[x].pre+1,0));
     }
     else ret=Delete(v<T[x]?Lc[x]:Rc[x],v);
     Balance(x);
     return ret;
}

inline void Build(int x,int l,int r){
	for (int i=l;i<=r;i++) Insert(root[x],mp(a[i],pre[i],a[i]));
	if (l==r) return;
	int mid=(l+r)/2;
	Build(x*2,l,mid);Build(x*2+1,mid+1,r);
}

inline LL  query(int x,int l,int r,int f,int t){
	if (f<=l && r<=t) return find(root[x],f-1);
	int mid=(l+r)/2;LL ret=0;
	if (f<=mid) ret+=query(x*2,l,mid,f,t);
	if (t>mid) ret+=query(x*2+1,mid+1,r,f,t);
	return ret;
}

inline void change(int i,int dat){
	if (dat==a[i]) return;
	/*tmp=ST[MM[a[i]]].lower_bound(i);
	tmp--;
	int pi=*tmp;
	tmp++;tmp++;
	int ni=*tmp,v=a[i];*/
	int pi=PRE(i),ni=NXT(i),v=a[i];
	
	int p=MM[a[i]];
	tmp=ST[p].lower_bound(i);
	ST[p].erase(tmp);
	
	if ((p=MM[dat])==0) MM[dat]=++cnt,ST[cnt].insert(0),ST[cnt].insert(n+1),p=cnt;
	a[i]=dat;
	ST[p].insert(i);
	
	int prei=PRE(i);
	for (int l=1,r=n,x=1;;){
		Delete(root[x],mp(v,pi,0));
		Insert(root[x],mp(dat,prei,dat));
		if (l==r) break;
		int mid=(l+r)/2;
		if (i<=mid) r=mid,x*=2; else l=mid+1,x=x*2+1;
	}
	
	if (ni<=n){
		int PNI=PRE(ni);
		for (int l=1,r=n,x=1;;){
			Delete(root[x],mp(a[ni],i,0));
			Insert(root[x],mp(a[ni],pi,a[ni]));
			if (l==r) break;
			int mid=(l+r)/2;
			if (ni<=mid) r=mid,x*=2; else l=mid+1,x=x*2+1;
		}
	}
	
	int nn=NXT(i);
	if (nn<=n){
		int PN=PRE(i);
		for (int l=1,r=n,x=1;;){
			Delete(root[x],mp(a[nn],PN,0));
			Insert(root[x],mp(a[nn],i,a[nn]));
			if (l==r) break;
			int mid=(l+r)/2;
			if (nn<=mid) r=mid,x*=2; else l=mid+1,x=x*2+1;
		}
	}
	
}

inline void getint(int &x) {
	char ch;
	while(!isdigit(ch= getchar()) && ch!='-');
	if(ch == '-'){
		x= 0;
		while(isdigit(ch= getchar())) x= x*10 + ch-'0';
		x= -x;
	}else{
		x= ch-'0';
		while(isdigit(ch= getchar())) x= x*10 + ch-'0';
	}
}

int main(){
	//freopen("xxxxxxxx.in","r",stdin);
	//freopen("xx.out","w",stdout);
	getint(n);
	for (int i=1;i<=n;i++) getint(a[i]);
	for (int i=1;i<=n;i++){
		if (!MM[a[i]]) MM[a[i]]=++cnt,ST[cnt].insert(0),ST[cnt].insert(n+1);
		ST[MM[a[i]]].insert(i);
		pre[i]=PRE(i);
	}
	Build(1,1,n);
	scanf("%d",&m);
	for (int i=1;i<=m;i++){
		char ch;int x,y;
		while(ch= getchar(), ch<'A' || ch>'Z');
		getint(x);getint(y);
		if (ch=='Q') printf("%lld\n",query(1,1,n,x,y));
				else change(x,y);
	}
}
