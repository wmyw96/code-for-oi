#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<queue>

using namespace std;
typedef unsigned int UI;
typedef long long LL;
const int MAX_N=4000001,MAX_NN=50001,MAX_NLINE=50001<<2,MOD=1000000007;
struct data{
	int num;
	UI v;
};
UI Sum[MAX_N];
UI ans;
int S[MAX_N],Rc[MAX_N],Lc[MAX_N];
data T[MAX_N];
int a[MAX_NN];
int root[MAX_NLINE];
int n,m,nm;
int JC[MAX_NN];

void Up(int x){
	if (!x) return;
	S[x]=S[Lc[x]]+S[Rc[x]]+1;
	Sum[x]=(Sum[Lc[x]]+Sum[Rc[x]]+T[x].v)%MOD;
}
void Zig(int &x){
	int y=Lc[x];Lc[x]=Rc[y];Rc[y]=x;
	Up(x);Up(y);x=y;
}
void Zag(int &x){
	int y=Rc[x];Rc[x]=Lc[y];Lc[y]=x;
	Up(x);Up(y);x=y;
}
void Maintain(int &x){
	//if(d){
		if(S[Rc[Rc[x]]] > S[Lc[x]])
			Zag(x);
		else
			if(S[Lc[Rc[x]]] > S[Lc[x]])
				Zig(Rc[x]),Zag(x);
	//}else{
		if(S[Lc[Lc[x]]] > S[Rc[x]])
			Zig(x);
		else
			if(S[Rc[Lc[x]]] > S[Rc[x]])
				Zag(Lc[x]),Zig(x);
	//}
	Up(x);
}
void Insert(int &x,data dat){
	if (!x) T[x=++nm]=dat;
	else Insert((T[x].num>dat.num)?(Lc[x]):(Rc[x]),dat);
	Maintain(x);
}
int Getsum(int x,int dat){
	if (!x) return 0;
	if (dat>T[x].num) return Getsum(Rc[x],dat);
	else return (Getsum(Lc[x],dat)+Sum[Rc[x]]+T[x].v)%MOD;
}
int rank(int x,int dat){
	if (!x) return 0;
	if (dat<T[x].num) return rank(Lc[x],dat);
	else return (rank(Rc[x],dat)+S[Lc[x]]+1);	
}
data Delete(int &x,int v){
     data ret;
     if (v==T[x].num || (v<T[x].num && !Lc[x]) || (v>T[x].num && !Rc[x])){
        ret=T[x];
        if (!Lc[x] || !Rc[x]) x=Lc[x]+Rc[x];
                     else T[x]=Delete(Lc[x],v+1);
     }
     else ret=Delete(v<T[x].num?Lc[x]:Rc[x],v);
     Maintain(x);
     return ret;
}
int querykth(int x,int l,int r,int f,int t,int dat){
	if (f>t) return 0;
	if (f<=l && r<=t) return rank(root[x],dat);
	int mid=(l+r)/2,ret=0;
	if (f<=mid) ret+=querykth(x*2,l,mid,f,t,dat);
	if (t>mid) ret+=querykth(x*2+1,mid+1,r,f,t,dat);
	return ret;
}
int querysum(int x,int l,int r,int f,int t,int dat){
	if (f<=l && r<=t) return Getsum(root[x],dat);
	int mid=(l+r)/2,ret=0;
	if (f<=mid) ret+=querysum(x*2,l,mid,f,t,dat);
	if (t>mid) ret+=querysum(x*2+1,mid+1,r,f,t,dat);
	ret%=MOD;
	return ret;
}
data mp(int x,int y){
	data v;v.num=x;v.v=y;return v;
}
void Build(int x,int l,int r){
	for (int i=l;i<=r;i++) Insert(root[x],mp(a[i],JC[n-i]));
	if (l==r) return;
	int mid=(l+r)/2;
	Build(x*2,l,mid);
	Build(x*2+1,mid+1,r);
}
void init(){
	scanf("%d%d",&n,&m);
	JC[0]=1;
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),JC[i]=(LL)JC[i-1]*i%MOD;
	JC[0]=0;
	Build(1,1,n);
	for (int i=1;i<=n;i++){
		int rnk=querykth(1,1,n,i+1,n,a[i]);
		ans+=(LL)rnk*JC[n-i]%MOD;
		ans%=MOD;
	}
	ans++;
}
void see(int x){
	if (!x) return;
	see(Lc[x]);
	printf("(%d ,%d)",T[x].num,T[x].v);
	see(Rc[x]);
}
void exchange(int l,int r){
	int vl=a[l];int vr=a[r];
	if (l+1<r){
		ans+=querysum(1,1,n,l+1,r-1,vl)-querysum(1,1,n,l+1,r-1,vr); 
		if (ans<0) ans+=MOD;
		ans%=MOD;
	}
	
	ans-=((LL)querykth(1,1,n,l+1,n,vl)*JC[n-l])%MOD;
	if (ans<0) ans+=MOD;
	ans-=((LL)querykth(1,1,n,r+1,n,vr)*JC[n-r])%MOD;
	if (ans<0) ans+=MOD;
	//printf("%d  %d\n",ans,querykth(1,1,n,r+1,n,vr));
	swap(a[l],a[r]);

	for (int x=1,f=1,t=n;;){
		Delete(root[x],vl);
		if (f==t) break;
		int mid=(f+t)/2;		
		if (l<=mid) t=mid,x=x*2; else f=mid+1,x=x*2+1;
	}
	for (int x=1,f=1,t=n;;){
		Delete(root[x],vr);
		if (f==t) break;
		int mid=(f+t)/2;		
		if (r<=mid) t=mid,x=x*2; else f=mid+1,x=x*2+1;
	}
	for (int x=1,f=1,t=n;;){
		Insert(root[x],mp(a[l],JC[n-l]));
		if (f==t) break;
		int mid=(f+t)/2;
		if (l<=mid) t=mid,x=x*2; else f=mid+1,x=x*2+1;
	}
	for (int x=1,f=1,t=n;;){
		Insert(root[x],mp(a[r],JC[n-r]));
		if (f==t) break;
		int mid=(f+t)/2;		
		if (r<=mid) t=mid,x=x*2; else f=mid+1,x=x*2+1;
	}	
	ans+=((LL)querykth(1,1,n,l+1,n,a[l])*JC[n-l])%MOD;
	ans+=((LL)querykth(1,1,n,r+1,n,a[r])*JC[n-r])%MOD;
	ans%=MOD;
}
int main(){
	init();
	while (m--){
		int x,y;
		scanf("%d%d",&x,&y);
		exchange(x,y);
		printf("%d\n",ans);
	}
}
