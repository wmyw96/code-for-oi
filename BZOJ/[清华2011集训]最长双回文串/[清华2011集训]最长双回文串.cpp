#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 300001, SUP = 100000000;
struct se{
	int a, b, c;
	void mp(int x, int y, int z){
		a = x; b = y; c = z;
	}
};
se s1[MAX_N], s2[MAX_N];
int rk[MAX_N], cnt[MAX_N], sa[MAX_N], a[MAX_N], H[1001], h[MAX_N], f[MAX_N][26];
int w1[MAX_N], w2[MAX_N];
int mn[MAX_N << 2], g[MAX_N];
char st[MAX_N];
int n;

int build(int w){
	if (w > n) return n + 1;
	for (int i = 1; i <= n; ++i) s1[i].mp(rk[i], rk[i + w], i);
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[s1[i].b]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s2[cnt[s1[i].b]--] = s1[i];
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[s2[i].a]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s1[cnt[s2[i].a]--] = s2[i];
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		rk[s1[i].c] = rk[s1[i - 1].c] + (s1[i].a != s1[i - 1].a || s1[i].b != s1[i - 1].b),
		ret = max(ret, rk[s1[i].c]);
	return ret;
}

int lcp(int l, int r){
	if (l > r) return lcp(r, l);
	l++;
	if (l == r) return h[l];
	int k = (int)(log(r - l + 1) / log(2));
	return min(f[l][k], f[r - (1<<k) + 1][k]);
}

void insert(int x, int l, int r, int site, int dat){
	if (l == r) {mn[x] = dat;return;}
	int mid = (l + r) / 2;
	if (site <= mid) insert(x * 2, l, mid, site, dat);
	if (site > mid) insert(x * 2 + 1, mid + 1, r, site, dat);
	mn[x] = min(mn[x * 2], mn[x * 2 + 1]);
}

int query(int x, int l, int r, int f, int t){
	if (r < l || f > t) return SUP;
	if (f <= l && r <= t) return mn[x];
	int mid = (l + r) / 2;
	int ret = SUP;
	if (f <= mid) ret = query(x * 2, l, mid, f, t);
	if (t > mid) ret = min(ret, query(x * 2 + 1, mid + 1, r, f, t));
	return ret;
}

int main(){
	scanf("%s", &st);
	int l = strlen(st), ret = 0;

    for (int i = 1; i <= l; ++i) a[i] = st[i - 1];
    for (int i = l; i >= 1; --i) a[l * 2 - i + 2] = st[i - 1];
    for (int i = 1; i <= 2 * l + 1; ++i) if (i != l + 1) H[a[i]] = 1, ret = max(a[i], ret);
    a[l + 1] = ret + 1;
    H[++ret] = 1;
	for (int i = 0; i <= ret; ++i) H[i] += H[i - 1];
	for (int i = 1; i <= (n = 2 * l + 1); ++i) rk[i] = H[a[i]];
	for (int i = 1; i <= n && build(i) < n; i <<= 1);

	for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
	for (int i = 1, j = 0; i <= n; ++i){
		if (rk[i] == 1) continue;
		for (j = max(0, j - 1); j <= n && a[i + j] == a[sa[rk[i] - 1] + j]; ++j);
		h[rk[i]] = j;
	}
	for (int i = n; i >= 1; --i){
		f[i][0] = h[i];
		for (int k = 1; (1 << k) + i - 1 <= n; ++k)
			f[i][k] = min(f[i][k - 1], f[i + (1 << k-1)][k - 1]);
	}
	int nn = (n - 1) / 2;
	w1[1] = 1;
	for (int i = 2, d = 2; i <= nn; ++i){
		for (;lcp(rk[d], rk[n - d + 1]) < i - d + 1; ++d);
		w1[i] = max(1, (i - d + 1) * 2 - 1);
	}
	for (int i = 2, dl = 1, dr = 2; i <= nn; ++i){
		for (;lcp(rk[dr], rk[n - dl + 1]) < i - dr + 1; ++dl, ++dr);
		w1[i] = max(w1[i], (i - dr + 1) * 2);
	}
	
	w2[nn] = 1;
	for (int i = nn - 1, d = nn - 1; i >= 1; --i){
        for (; lcp(rk[d], rk[n - d + 1]) < d - i + 1; --d);
        w2[i] = max(1, (d - i + 1) * 2 - 1);
    }
    for (int i = nn - 1, dl = nn, dr = nn - 1; i >= 1; --i){
        for (; lcp(rk[dr], rk[n - dl + 1]) < dl - i + 1; --dl, --dr);
        w2[i] = max(w2[i], (dl - i + 1) * 2);
    }
    int ans = 0;
    for (int i = 1; i < n; ++i)
        ans = max(ans, w1[i] + w2[i + 1]);
	printf("%d\n", ans);
} 
