#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){
	freopen("SUBLEX.in","w",stdout);
	srand(time(0));
	for (int i = 1;i <= 90000;i++) printf("%c",rand()%26+'a');
	printf("\n");
	printf("500\n");
	for (int i=1;i<=500;i++) printf("%d\n",rand()*rand());
}
