#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAX_N=1000001;
int tot,ans;
int c[MAX_N],P[MAX_N];
typedef long long LL;

int main(){
	c[1]=0;
	for (int i=2;i<MAX_N;i++){
		if (!c[i]) P[++tot]=i,c[i]=i;
		for (int j=1;j<=tot;j++){
			if ((LL)i*P[j]<MAX_N)
				c[i*P[j]]=P[j];
			else break;
			if (i%P[j]==0) break;
		}
	}
	for (int i=2;i<MAX_N;i++){
		int num=i,check=1,cnt=1;
		
		while (num!=1){
			int x=c[num];
			num/=x;
			if (x==c[num]) {check=0;break;} else cnt*=2;
		}
		
		if (check && cnt>3){
			ans++;
			if (ans%108==0) printf("%d\n",i);
		}
	}
}


