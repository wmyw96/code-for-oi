#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N = 511, p = 53, q = 41, MOD = 999983 , MOD2 = 999979;
int a[MAX_N][MAX_N], rx[MOD], ry[MOD];
char H[MOD], H2[MOD2];
char st[MAX_N];
LL h[MAX_N], h2[MAX_N], now, now2;
LL bq[MAX_N], bp[MAX_N];
int n, m, ax, ay, nown;

int ck(int w){
	memset(h, 0, sizeof h);
	memset(h2, 0, sizeof h2);
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j < w; ++j) h[i] = (h[i] * p + a[j][i]) % MOD;
		
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j < w; ++j) h2[i] = (h2[i] * p + a[j][i]) % MOD2;
		
	memset(H, 0, sizeof H);
	memset(H2, 0, sizeof H2);
	memset(rx, 0, sizeof rx);
	memset(ry, 0, sizeof ry);
	
	for (int i = w; i <= n; ++i){
		for (int j = 1; j <= m; ++j) {
			h[j] -= bp[w] * a[i - w][j] % MOD;
			if (h[j] < 0) h[j] += MOD;
			h[j] = (h[j] * p + a[i][j]) % MOD;
			
			h2[j] -= bp[w] * a[i - w][j] % MOD2;
			if (h2[j] < 0) h2[j] += MOD2;
			h2[j] = (h2[j] * p + a[i][j]) % MOD2;
		}
		
		now = 0;
		now2 = 0;
		for (int j = 1; j <= w; ++j){
			now = (now * q + h[j]) % MOD;
			now2 = (now2 * q + h2[j]) % MOD2;
		}
			
		if (H[now] && H2[now2]) 
			{ax = i; ay = w; nown = now; return 1;}
		
		H[now]++;
		H2[now2]++;
		
		rx[now] = i, ry[now] = w;
		
		for (int j = w + 1; j <= m; ++j){
			now -= bq[w] * h[j - w] % MOD;
			if (now < 0) now += MOD;
			now = (now * q + h[j]) % MOD;
			
			now2 -= bq[w] * h2[j - w] % MOD2;
			if (now2 < 0) now2 += MOD2;
			now2 = (now2 * q + h2[j]) % MOD2;	
					
			if (H[now] && H2[now2]) 
			{ax = i; ay = j; nown = now; return 1;}
			
			H[now] = 1;
			H2[now2] = 1;
			
			rx[now] = i, ry[now] = j;
			//printf("%d %d %d\n", i, j, now);
		}
	}
	return 0;
} 

int main(){
	scanf("%d%d", &n, &m);
	
	bp[1] = bq[1] = 1;
	for (int i = 2; i <= max(n, m); ++i) 
		bp[i] = bp[i - 1] * p % MOD,
		bq[i] = bq[i - 1] * q % MOD;

	for (int i = 1; i <= n; ++i){
		scanf("%s", &st);
		for (int j = 1; j <= m; ++j)
			a[i][j] = st[j - 1] - 'a' + 1;
	}
	int l = 0, r = min(n, m) + 1;
	while (l + 1 < r){
		int mid = (l + r) / 2;
		if (ck(mid)) l = mid; else r = mid;
	}
	
	printf("%d\n", l);
	if (l > 0){
		ck(l);
		printf("%d %d\n", rx[nown] - l + 1, ry[nown] - l + 1);
		printf("%d %d\n", ax - l + 1, ay - l + 1);
	}
}


