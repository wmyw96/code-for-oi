#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

int main(){
	scanf("%d", &Ti);
	while (Ti--){
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i){
			scanf("%s", &st);
			la[i] = strlen(st);
			for (int j = 0; j < la[i]; j++)
				a[i] = (a[i] * p + st[j] - 'a') % MOD;
				
		}
	}
} 
