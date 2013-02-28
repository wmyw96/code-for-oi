#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;

int main(){
	freopen("3296.in", "w", stdout);
	int N = 50000;
	srand(time(0));
	for (int j = 1; j <= 10; ++j){
	for (int i = 1; i <= N; i++) printf("%c", rand() % 3 + 'a');
	printf("\n");
	}
}
