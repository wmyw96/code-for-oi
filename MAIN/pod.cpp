#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N = 1000001;
int c[MAX_N], P[MAX_N], tot, u[MAX_N];
LL n;

LL getans(LL N){
	LL ret = 0;
	for (int i = 1; (LL)i * i <= N; ++i)
		ret += (N / ((LL)i * i)) * u[i];
	return N - ret;
}

int main(){
	u[1] = 1;
	for (int i = 2; i < MAX_N; ++i){
		if (!c[i]) c[i] = i, P[++tot] = i, u[i] = -1;
		else{
			if (u[i / c[i]] == 0) u[i] = 0;
			else 
				if (c[i / c[i]] == c[i]) u[i] = 0;
				else u[i] = - u[i / c[i]];
		}
		for (int j = 1; j <= tot; ++j){
			if ((LL)P[j] * i >= MAX_N) break;
			c[P[j] * i] = P[j];
			if (i % P[j] == 0) break;
		}
		//printf("%d %d\n", u[i], i);
	}
	cin >> n;
	LL l = 1, r = (LL)10000 * 10000 * 10000;
	while (l + 1 < r){
		LL mid = l + r >> 1;
		if (getans(mid) < n) l = mid; else r = mid;
	}
	cout<< r << endl;
}

