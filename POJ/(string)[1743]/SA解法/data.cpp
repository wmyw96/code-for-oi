#include<iostream>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;

int main(){
	freopen("in", "w", stdout);
	srand(time(0));
	for (int z = 1; z <= 10; ++z){
	int n = rand()%30 + 1;
	printf("%d\n", n);
	for (int i = 1; i <= n; ++i) printf("%d ", rand() % 2 + 1);
	printf("\n");
	}
	printf("0\n");
}
