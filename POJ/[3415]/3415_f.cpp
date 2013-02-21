#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;

const int maxn=200020;
int rank[maxn],rr[maxn<<1],ss[maxn],pp[maxn],ww[maxn],sa[maxn],h[maxn];
int n,k,n1,n2,top,a[maxn],st[maxn][2];
char s1[maxn],s2[maxn];
bool boo[maxn];
LL now,ans;

void Make(int n,int m) {
    int i,c;
    for (i=1;i<=n;++i) rank[i]=a[i];
    for (c=1;c<=n;c<<=1,m=n) {
        for (i=1;i<=n;++i) rr[i]=rank[i];
        for (i=0;i<=m;++i) ss[i]=0;
        for (i=1;i<=n;++i) ++ss[rr[i+c]];
        for (i=1;i<=m;++i) ss[i]+=ss[i-1];
        for (i=1;i<=n;++i) pp[ss[rr[i+c]]--]=i;
        for (i=0;i<=m;++i) ss[i]=0,ww[i]=-1;
        for (i=1;i<=n;++i) ++ss[rr[i]];
        for (i=1;i<=m;++i) ss[i]+=ss[i-1];
        for (i=n;i;--i) {
            if (ww[rr[pp[i]]]!=rr[pp[i]+c]) --ss[rr[pp[i]]];
            ww[rr[pp[i]]]=rr[pp[i]+c];
            rank[pp[i]]=ss[rr[pp[i]]]+1;
        }
    }
    for (i=1;i<=n;++i) sa[rank[i]]=i;
}

void Cut(int p) {
    int tmp=0;
    for (;(top)&&(st[top][0]>p);--top)
        now-=(LL)st[top][0]*(LL)st[top][1],tmp+=st[top][1];
    st[++top][0]=p,st[top][1]=tmp;
    now+=(LL)p*(LL)tmp;
}

void Interval(int l,int r,bool flag) {
    top=0; now=0;
    for (int i=l-1;i<=r;++i)
        if (flag==boo[i]) {
            if (i>=l) Cut(h[i]-k+1);
            st[++top][0]=n+1,st[top][1]=1;
            now+=n+1;
        } else {
            if (i>=l) Cut(h[i]-k+1);
            ans+=now;
        }
}

void Work() {
    int l=1,r;
    for (;l<=n;) {
        if (h[l]<k) {++l;continue;}
        r=l;
        while (h[r+1]>=k) ++r;
        Interval(l,r,false);
        Interval(l,r,true);
        l=r+1;
    }
}

int main() {
    while (scanf("%d",&k)) {
        if (!k) return 0;
        memset(h,0,sizeof(h));
        memset(rr,0,sizeof(rr));
        scanf("%s",&s1); scanf("%s",&s2);
        n=ans=0;
        n1=strlen(s1); n2=strlen(s2);
        for (int i=0;i<n1;++i) a[++n]=(int)s1[i];
        a[++n]=1;
        for (int i=0;i<n2;++i) a[++n]=(int)s2[i];
        Make(n,255);
        for (int i=1;i<=n;++i) boo[i]=(sa[i]<=n1);
        for (int i=1;i<=n;++i)
            for (int j=max(h[rank[i-1]]-1,1);a[sa[rank[i]-1]+j-1]==a[i+j-1];++j) h[rank[i]]=j;
        Work();
        cout<<ans<<endl;
    }
    return 0;
}

