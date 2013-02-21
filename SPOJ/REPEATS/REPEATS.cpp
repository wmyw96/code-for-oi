#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N = 200001;
struct ls{
	int a, b, c;
	void mp(int aa, int bb, int cc){a = aa, b = bb, c = cc;}
};
ls s[MAX_N],ss[MAX_N];
int rk[MAX_N], sa[MAX_N], h[MAX_N];
int a[MAX_N];
int cnt[MAX_N], H[MAX_N];
int f[MAX_N][25];
int n;

int build(int w){
	if (w > n) return n + 1;
	for (int i = 1; i <= n; ++i)
		s[i].mp(rk[i], rk[i + w], i);
	
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) ++cnt[s[i].b];
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) ss[cnt[s[i].b]--] = s[i];
	
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) ++cnt[ss[i].a];
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s[cnt[ss[i].a]--] = ss[i];	
	
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		rk[s[i].c] = rk[s[i - 1].c] + (s[i].a != s[i-1].a || s[i].b != s[i-1].b),
		ret = max(ret, rk[s[i].c]);
		
	return ret;
}

int lcp(int x, int y){
	if (x > y) return lcp(y, x);
	++x;
	//printf("+ %d %d\n", x ,y);
	if (x == y) return h[y];
	int k = (int) ( log(y - x) / log(2));
	return min(f[x][k], f[y - (1<<k) + 1][k]);
}
int up(int &x, int y){
	if (y > x) x = y;
}
int main(){
	int Ti;
	scanf("%d", &Ti);
	while (Ti --){
		int ret = 0; char ch;
		memset(H, 0, sizeof H);
		memset(rk, 0, sizeof rk);
		memset(a, 0, sizeof a);
		memset(f, 0, sizeof f);
		scanf("%d", &n);
		
		for (int i = 1; i <= n; ++i) scanf(" "),scanf("%c", &ch), a[i] = ch;
		for (int i = 1; i <= n ; ++i) H[a[i]] = 1, ret = max(ret, a[i]);
		for (int i = 1; i <= ret; ++i) H[i] += H[i-1];
		for (int i = 1; i <= n; ++i) rk[i] = H[a[i]];
		for (int i = 1; i <= n && build(i) < n; i <<= 1);
		for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
		
		for (int i = 1, j = 0; i <= n; ++i){
			if (rk[i] == 1) continue;
			for (j = max(0, j - 1); j <= n && a[i + j] == a[sa[rk[i] - 1] + j];) ++j;
			h[rk[i]] = j;
		}
		
		for (int i = n; i >= 1; i--){
			f[i][0] = h[i];
			for (int k = 1; ((1 << k) + i - 1) <= n; ++k)
				f[i][k] = min(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
		}
		
		int ans = 1;
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i + k <= n; i += k)
			 if (a[i] == a[i + k]){
				int p = lcp(rk[i], rk[i + k]);
				//printf("%d %d %d\n", i, k, p);
				int j = k - p % k;
				if (i - j > 0 && j > 0) up(ans, p / k + 1 + (lcp(rk[i - j], rk[i + k - j]) >= k));
				else up(ans, p / k + 1);
			 }
		printf("%d\n", ans);
	}
}

