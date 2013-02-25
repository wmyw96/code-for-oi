#include<iostream>
#include<cstdio> 
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX_N = 1000001;
int Ti;
char st[MAX_N];

int main(){
	scanf("%d", &Ti);
	while (Ti--){
		scanf("%s", &st);
		int n = strlen(st);
		for (int i = n; i < 2 * n; ++i) st[i] = st[i - n];
		int i = 0, k, j1;
		for (int j = 1; j < n;){
			for (k = 0; k < n && st[i + k] == st[j + k]; ++k);
			if (k >= n) break;
			if (st[i + k] < st[j + k]) j += k + 1;
								  else j1 = j, j = max(i + k, j) + 1, i = j1;
		}
		printf("%d\n", i + 1);
	}
}

