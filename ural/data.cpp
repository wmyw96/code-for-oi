#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;

int main(){
	freopen("1.in", "w", stdout);
	int N = 200 , M = 200;
	printf("%d %d\n", N, M);
	srand(time(0));
	for (int j = 1; j <= N; ++j){
	for (int i = 1; i <= M; i++) printf("%c", rand() % 2 + 'a');
	printf("\n");
	}
}
