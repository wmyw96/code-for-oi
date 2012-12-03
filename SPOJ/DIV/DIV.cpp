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
		int pr=1,now=1,num=i,prex=0,step=0;
		while (num!=1){
			int x=c[num];
			num/=x;
			now++;
			if (x!=c[num]) pr*=now,now=1;
			prex=x;
		}
		
		while (pr!=1){
			int x=c[pr];
			pr/=x;
			if (c[pr]==x) {step=101;break;}
			step++;
			if (step>2) break;
		}
		if (step==2){
			ans++;
			if (ans%9==0) printf("%d\n",i);
		}
	}
}

