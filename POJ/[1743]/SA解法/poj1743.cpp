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
int cnt[MAX_N], H[MAX_N];
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

int ck(int w){
	int mx = 0, mn = n;
	for (int i = 1; i <= n; ++i){
		if (h[i] >= w){
			mx = max(mx, sa[i]);
			mn = min(mn, sa[i]);
			if (mn <= mx && mx - mn > w) return 1;
		}
		else mx = sa[i], mn = sa[i];
	}
	return 0;
}

int main(){
	while (scanf("%d", &n) != EOF){
		if (n == 0) break;
		int ret = 0;
		memset(H, 0, sizeof H);
		memset(rk, 0, sizeof rk);
		memset(a, 0, sizeof a);
		for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
		for (int i = 1; i <= n - 1; ++i) a[i] = b[i+1] - b[i] + 100, H[a[i]] = 1, ret = max(ret, a[i]);
		
		n--;
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
		if (l > 3) printf("%d\n", l + 1); else printf("%d\n", 0);
	}
}

