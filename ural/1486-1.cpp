#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>
 
#define FI			first
#define SE			second
#define LSON(x)			(x<<1)
#define RSON(x)			((x<<1)|1)
#define Benefit(x,y)		x=max(x,y)
#define CS			const static
#define SORT_CMP(s,l,r,cmp)	sort(s+(l),s+(r)+1,cmp)
#define SORT(s,l,r)		sort(s+(l),s+(r)+1)
#define MP(x,y)			make_pair(x,y)
#define Randomize		srand( (unsigned int) time ( NULL ) )
#define INOUT(x,y)		freopen(x,"r",stdin),freopen(y,"w",stdout)
 
using namespace std;
 
#define PII			pair < int , int >
 
CS int P1 = 547 ;
CS int P2 = 733 ;
CS int MOD = 253633 ;
CS int MaxN = 510 ;
 
char g[MaxN][MaxN];
 
int f1[MaxN][MaxN];
int f2[MaxN][MaxN];
 
PII sta[MOD];
 
int head[MOD];
int _next[MOD];
int p1[MaxN];
int p2[MaxN];
 
int n,m,tot,ansl,ansx1,ansy1,ansx2,ansy2;
 
void Init()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		getchar();
		for(int j=1;j<=m;j++)	g[i][j] = getchar() - 'a' ;
	}
}
 
bool Meet(int val,int x,int y,int len)
{
	tot++;	sta[tot] = MP(x,y);
	for(int k = head[val]; k ; k = _next[k])
	{
		PII & u = sta[k];
		bool suit = true ;
		for(int x1=0;x1<len;x1++)
			suit&=(f1[x][y+x1]==f1[u.FI][u.SE+x1]);
		if(suit&&(len>ansl))
		{
			ansl = len;
			ansx2 = u.FI;	ansy2 = u.SE ;
			ansx1 = x ;	ansy1 = y ;
			return true;
		}
	}
	_next[tot] = head[val] ; head[val] = tot ;
	return false;
}
 
bool Check(int len)
{
	memset(head,0,sizeof(head));
	memset(_next,0,sizeof(_next));
	tot = 0 ;
	for(int i=n;i>0;i--)
		for(int j=1;j<=m;j++)
			if(i>n-len)	f1[i][j]=(f1[i+1][j]*P1+g[i][j])%MOD;
			else		f1[i][j]=(((f1[i+1][j]-(long long)g[i+len][j]*p1[len-1])*P1+g[i][j])%MOD+MOD)%MOD;
	for(int i=n-len+1;i>0;i--)
		for(int j=m;j>0;j--)
		{
			if(j>m-len)	f2[i][j]=(f2[i][j+1]*P2+f1[i][j])%MOD;
			else		f2[i][j]=(((f2[i][j+1]-(long long)f1[i][j+len]*p2[len-1])*P2+f1[i][j])%MOD+MOD)%MOD;
			if((j<=m-len+1)&&(Meet(f2[i][j],i,j,len)))	return true;
		}
	return false;
}
 
bool BinSea()
{
	bool find = false ;
	int l = 1 , r = min(n,m) , mid ;
	while(l<=r)
	{
		mid = (l+r)>>1 ;
		if(Check(mid))	l = mid + 1 , find = true ;
		else		r = mid - 1 ;
	}
	return find;
}
 
void Solve()
{
	p1[0] = p2[0] = 1 ; p1[1] = P1 ; p2[1] = P2 ;
	for(int i=1;i<=max(n,m);i++)
	{
		p1[i]=(p1[i-1]*P1)%MOD;
		p2[i]=(p2[i-1]*P2)%MOD;
	}
	if(BinSea())
	{
		printf("%d\n",ansl);
		printf("%d %d\n",ansx1,ansy1);
		printf("%d %d\n",ansx2,ansy2);
	}
	else	printf("0");
}
 
int main()
{
	Init();	Solve();
	return 0;
}
//wzm

