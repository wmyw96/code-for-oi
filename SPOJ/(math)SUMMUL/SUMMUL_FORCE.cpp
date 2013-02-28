#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
using namespace std;
int f[5001];
const int MOD= 1000000007;
typedef long long LL;
int main(){
	int T,n;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		memset(f,0,sizeof f);
		f[0]=1;
		f[1]=1;
		f[2]=3;
		for (int i=3;i<=n;i++)
			for (int j=0;j<i;j++){
			    f[i]+=(LL)f[j]*(i-j)%MOD;
			    f[i]%=MOD;
			    //printf("%d %d %d\n",j,f[j],(i-j));
		} 
		printf("%d\n",f[n]-n);
	}
} 

