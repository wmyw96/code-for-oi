#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<ctime>
using namespace std;
int n,m;

int main(){
	srand(time(0));
	n=50;
	freopen("XXXXXXXX.in","w",stdout);
	printf("%d\n",n);
	for (int i=1;i<=n;i++){
		printf("%d ",rand()%100000);
	}
	int m=100;
	printf("\n%d\n",m);
	for (int i=1;i<=m;i++){
		int x=rand()%(n/2)+1;
		int y=x+rand()%(n/2)+1;
		int w=rand()%10000;
		if (w!=0){
			printf("U %d %d\n",rand()%n+1,rand()%100000);
		}
		else 
			printf("Q %d %d\n",x,y);
	}
}

