#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;

const int MAX_N = 1000001;
struct ls{
	int a, b, c;
	void mp(int aa, int bb, int cc){a = aa, b = bb, c = cc;}
};
ls s[MAX_N],ss[MAX_N];
int rk[MAX_N], a[MAX_N], b[MAX_N], sa[MAX_N], h[MAX_N], mk[MAX_N];
int cnt[MAX_N], H[MAX_N], len[MAX_N], hh[MAX_N], ans[MAX_N];
char st[MAX_N];
int n, N, K, ansn;

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
    memset(hh, 0, sizeof hh);
    int cnt = 1, now = 0;
    int i = 0;
    for (i = 1; i <= n && mk[sa[i]] != 0; ++i){
        if (h[i] >= w){
           if (hh[mk[sa[i]]] != cnt) hh[mk[sa[i]]] = cnt, now++;
           if (now >= K) return 1;
        }
        else{
             cnt++;
             if (len[sa[i]] >= w) now = 1, hh[mk[sa[i]]] = cnt; else now = 0;
        }
    }
    return 0;
}

void mp(int w){
    memset(hh, 0, sizeof hh);
    int cnt = 1, now = 0;
    for (int i = 1; i <= n && mk[sa[i]] != 0; ++i){
        if (h[i] >= w){
           if (hh[mk[sa[i]]] != cnt) hh[mk[sa[i]]] = cnt, now++;
        }
        else{
             if (now >= K){
                ++ansn;
                for (int j = sa[i - 1]; j <= sa[i - 1] + w - 1; ++j)
                    printf("%c", a[j] + 'a' - 1);
                printf("\n");
             }
             cnt++;
             if (len[sa[i]] >= w) now = 1, hh[mk[sa[i]]] = cnt; else now = 0;
        }
    }
}

int main(){
    int pp = 0;
    while (scanf("%d", &N) != EOF){
		  if (!N) return 0;
          if (!pp) pp = 1; else printf("\n");
          K = N / 2 + 1;
          n = 0;
          
          memset(rk, 0, sizeof rk);
          memset(a, 0, sizeof a);
          memset(mk, 0, sizeof mk);
          memset(H, 0, sizeof H);
          memset(sa, 0, sizeof sa);
          memset(len, 0, sizeof len);
          memset(h, 0, sizeof h);
          
          int l = 0, r = 0;
          for (int i = 1; i <= N; ++i){
              scanf("%s", &st);
              int ll = strlen(st);
              for (int j = 1; j <= ll; ++j)
                  a[j + n] = st[j - 1] - 'a' + 1,
                  H[a[j + n]] = 1,
                  mk[j + n] = i,
                  len[j + n] = ll - j + 1;
              r = max(r, ll + 1);
              n += ll + 1;
              a[n] = 100 + i;
              H[a[n]] = 1;
          }
          
          for (int i = 1; i <= 300; ++i) H[i] += H[i - 1];
          for (int i = 1; i <= n; ++i) rk[i] = H[a[i]];
	      for (int i = 1; i <= n && build(i) < n; i <<= 1);
	      for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
	      for (int i = 1, j = 0; i <= n; ++i){
		      if (rk[i] == 1) continue;
		      for (j = max(0, j - 1); j <= n && a[i + j] == a[sa[rk[i] - 1] + j];) ++j;
		      h[rk[i]] = j;
	       }
	       while (l + 1 < r){
                 int mid = (l + r) / 2;
                 if (ck(mid)) l = mid; else r = mid;
           }
           if (l) mp(l); else printf("?\n");
    }
}

