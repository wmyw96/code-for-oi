#include<iostream>
#include<cstdio>
#include<cmath> 
#include<set>
#include<algorithm>
#include<cstring>
using namespace std;
const int u=1000010;
struct rec{int x,y;}b[u];
int sa[u],rank[u],c[u],fir[u],sec[u],h[u],d[21][u],a[u];
char str[u];
int n,m,i,j,k,ans;
set<int> f;
set<int>::iterator it;
 
bool comp(rec a,rec b)
{
return a.x<b.x;
}
bool cmp(int i,int j,int k)
{
return sec[i]==sec[j]&&sec[i+k]==sec[j+k];
}
 
void sufarr(int n)
{
int i,p,l,m=30;
for(i=0;i<n;i++) c[rank[i]=a[i]]++;
for(i=1;i<m;i++) c[i]+=c[i-1];
for(i=n-1;i>=0;i--) sa[--c[a[i]]]=i;
for(p=l=1;p<n;l*=2,m=p)
{
for(p=0,i=n-l;i<n;i++) sec[p++]=i;
for(i=0;i<n;i++)
if(sa[i]>=l) sec[p++]=sa[i]-l;
for(i=0;i<n;i++) fir[i]=rank[sec[i]];
for(i=0;i<m;i++) c[i]=0;
for(i=0;i<n;i++) c[fir[i]]++;
for(i=1;i<m;i++) c[i]+=c[i-1];
for(i=n-1;i>=0;i--) sa[--c[fir[i]]]=sec[i];
memcpy(sec,rank,sizeof(rank));
rank[sa[0]]=0;
for(i=p=1;i<n;i++)
rank[sa[i]]=cmp(sa[i],sa[i-1],l)?p-1:p++;
}
}
 
void calh()
{
int i,j,k=0;
for(i=1;i<=n;i++) rank[sa[i]]=i;
for(i=0;i<n;h[rank[i++]]=k)
for(k?k--:0,j=sa[rank[i]-1];a[i+k]==a[j+k];k++);
}
 
void rmq()
{
int i,j;
for(i=1;i<=n;i++) d[0][i]=h[i];
for(i=1;i<=(int)(log(n*1.0)/log(2.0));i++)
for(j=1;j<=n-(1<<i)+1;j++)
d[i][j]=min(d[i-1][j],d[i-1][j+(1<<i-1)]);
}
 
int ask(int x,int y)
{
if(x>y) swap(x,y); x++;
int k=(int)(log(y-x+1.0)/log(2.0));
return min(d[k][x],d[k][y-(1<<k)+1]);
}
 
int main()
{
cin>>n;
scanf("%s",str);
str[n]='{'; m=n;
for(i=1;i<=n;i++) str[n+i]=str[n-i];
n=n*2+1;
for(i=0;i<n;i++) a[i]=str[i]-'a'+1;
sufarr(n+1);
calh();
rmq();
memset(a,0,sizeof(a)); 
for(i=1;i<m;i++)
{
j=n-i;
a[i]=ask(rank[i],rank[j]);
b[i].x=i-a[i],b[i].y=i; 
}
sort(b,b+m,comp);
for(i=j=0;i<m;i++)
if(a[i])
{
for(;b[j].x<=i;j++)
f.insert(b[j].y);
it=f.upper_bound(i+a[i]/2); it--;
if((*it)>=i) ans=max(ans,((*it)-i)*4);
}
cout<<ans<<endl;
return 0;
}
