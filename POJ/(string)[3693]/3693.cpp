#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX_N = 500001;
struct rec{
	int a, b, c;
	void mp(int aa, int bb, int cc){a = aa, b = bb, c = cc;}
};
rec s[MAX_N], ss[MAX_N];
int rk[MAX_N], sa[MAX_N], a[MAX_N], cnt[MAX_N], h[MAX_N];
char st[MAX_N];
int H[1001];
int n, ansn, rd;
char ans[MAX_N], tmp[MAX_N];
int f[MAX_N][25];

int build(int w){
	if (w > n) return n + 1;
	for (int i = 1; i <= n; ++i)
		s[i].mp(rk[i], rk[i + w], i);
	
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[s[i].b]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) ss[cnt[s[i].b]--] = s[i];
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[ss[i].a]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s[cnt[ss[i].a]--] = ss[i];
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		rk[s[i].c] = rk[s[i - 1].c] + (s[i].a != s[i - 1].a || s[i].b != s[i - 1].b), ret = max(ret, rk[s[i].c]);
	return ret;
}

int lcp(int x, int y){
	if (x > y) return lcp(y, x);
	++x;
	if (x == y) return h[y];
	int k = (int)(log(y - x) / log(2));
	return min(f[x][k], f[y - (1<<k) + 1][k]);
}

void up(int rd1, int fr, int len){
	if (rd1 > rd){
		rd = rd1;
		strncpy(ans, st + fr - 1, len * rd1);
		//printf("%s %d %d\n", ans, rd, len);
	}
	else if (rd1 == rd){
		strncpy(tmp, st + fr - 1, len * rd1);
		//printf("%s\n",tmp);
		if (strcmp(tmp, ans) == -1) strncpy(ans, tmp, len * rd);
	}
}

int main(){
	int tot = 0;
	while (scanf("%s", &st) != EOF){
		if (st[0] == '#') break;
		memset(H, 0, sizeof H);
		memset(rk, 0, sizeof rk);
		memset(a, 0, sizeof a);
		n = strlen(st);
		int ret = 0;
		for (int i = 0; i < n; ++i) H[st[i] - 'a'] = 1, ret = max(ret, st[i] - 'a');
		for (int i = 1; i <= ret; ++i) H[i] += H[i - 1];
		for (int i = 1; i <= n; ++i) rk[i] = H[st[i - 1] - 'a'];
		for (int i = 1; i <= n && build(i) < n; i *= 2);
		for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
		for (int i = 1, j = 0; i <= n; ++i){
			if (rk[i] == 1) continue;
			for (j = max(j - 1, 0); j <= n && st[i + j - 1] == st[sa[rk[i] - 1] + j -1]; ++j);
			h[rk[i]] = j;
		}
		
		for (int i = n; i >= 1; --i){
			f[i][0] = h[i];
			for (int k = 1; ((1<<k) + i - 1) <= n; ++k)
				f[i][k] = min(f[i][k - 1], f[i + (1<<k-1)][k - 1]);
		}
		rd = 1;
		memset(ans, 0, sizeof ans);
		ans[0] = 'z';
		for (int i = 1; i <= n; ++i) if (st[i - 1] < ans[0]) ans[0] = st[i - 1];//, printf("%c\n", ans[0]);
		ans[1] = 0;
		//printf("%s\n", ans);
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i + k <= n; i += k){
				for (int j = 0; j < k && i - j > 0 && st[i - j - 1] == st[i - j + k - 1]; ++j){
					int p = lcp(rk[i - j], rk[i - j + k]) / k + 1;
					//printf("%d %d %d %d %d\n", i - j, p, rk[i - j], rk[i - j + k], k);
					up(p, i - j, k);
				}
			}
		//printf("%d\n", rd);
		printf("Case %d: %s\n", ++tot, ans);
	}
} 

