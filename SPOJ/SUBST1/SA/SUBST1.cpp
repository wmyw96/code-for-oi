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
char a[MAX_N];
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

int main(){
	int Ti;
	scanf("%d", &Ti);
	while (Ti --){
		int ret = 0;
		memset(H, 0, sizeof H);
		memset(rk, 0, sizeof rk);
		scanf("%s", &a);
		n = strlen(a);
		for (int i = 0; i <= n - 1; ++i) H[a[i]] = 1, ret = max(ret, a[i] - 'A' + 'A');
		
		for (int i = 1; i <= ret; ++i) H[i] += H[i-1];
		for (int i = 1; i <= n; ++i) rk[i] = H[a[i - 1]];//, printf("%d\n", rk[i]);
		
		for (int i = 1; i <= n && build(i) < n; i <<= 1);
		
		for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
		
		LL ans = (LL)n * (n + 1) / 2;
		for (int i = 1, j = 0; i <= n; ++i){
			if (rk[i] == 1) continue;
			for (j = max(0, j - 1); j <= n && a[i + j - 1] == a[sa[rk[i] - 1] + j - 1];) ++j;
			h[rk[i]] = j;
			ans -= j;
			//printf("- %d %d %d\n", i, rk[i], h[rk[i]]);
		}
		cout<<ans<<endl;
	}
}
// ans应该用LL
//乘的时候也要+LL 
