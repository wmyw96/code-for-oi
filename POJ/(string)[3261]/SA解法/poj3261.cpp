#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX_N = 100001;
struct ls{
	int a, b, c;
	void mp(int aa, int bb, int cc){a = aa, b = bb, c = cc;}
};
ls s[MAX_N],ss[MAX_N];
int rk[MAX_N], a[MAX_N], b[MAX_N], sa[MAX_N], h[MAX_N];
int cnt[MAX_N], H[MAX_N * 20];
int n, k;

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

int ck(int w){
	int TT = 0;
	for (int i = 1; i <= n; ++i){
		if (h[i] >= w){
			++TT;
			if (TT >= k) return 1;
		}
		else TT = 1;
	}
	return 0;
}

int main(){
	scanf("%d%d", &n, &k);
	int ret = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), H[a[i]] = 1, ret = max(ret, a[i]);
		
	for (int i = 1; i <= ret; ++i) H[i] += H[i-1];
	for (int i = 1; i <= n; ++i) rk[i] = H[a[i]];
		
	for (int i = 1; i <= n && build(i) < n; i <<= 1);
		
	for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
	for (int i = 1, j = 0; i <= n; ++i){
		if (rk[i] == 1) continue;
		for (j = max(0, j - 1); j <= n && a[i + j] == a[sa[rk[i] - 1] + j];) ++j;
		h[rk[i]] = j;
	}
	int l = 0, r = n;
	while (l + 1 < r){
		int mid = (l + r) / 2;
		if (ck(mid)) l = mid; else r = mid;
	}
	
	printf("%d\n", l);
}

