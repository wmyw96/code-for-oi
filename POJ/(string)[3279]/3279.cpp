#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 500001, MAX_L = 10001 + 1;
struct ls{
       int a, b, c;
       void mp(int x, int y, int z){
            a = x, b = y, c = z;
       }
}s1[MAX_N], s2[MAX_N];
int n, m, k, N;
int cnt[MAX_N], rk[MAX_N], sa[MAX_N], h[MAX_N], a[MAX_N], H[MAX_L];
int f[MAX_N][22], mk[MAX_N];
int b[MAX_N], lt;

int build(int w){
    if (w > N) return 0;
    for (int i = 1; i <= N; ++i)
        s1[i].mp(rk[i], rk[i + w], i);
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= N; ++i) cnt[s1[i].b]++;
    for (int i = 1; i <= N; ++i) cnt[i] += cnt[i - 1];
    for (int i = N; i >= 1; --i) s2[cnt[s1[i].b]--] = s1[i];
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= N; ++i) cnt[s2[i].a]++;
    for (int i = 1; i <= N; ++i) cnt[i] += cnt[i - 1];
    for (int i = N; i >= 1; --i) s1[cnt[s2[i].a]--] = s2[i];
    for (int i = 1; i <= N; ++i)
        rk[s1[i].c] = rk[s1[i - 1].c] + (s1[i].a != s1[i - 1].a || s1[i].b != s1[i - 1].b);
    return rk[s1[N].c];
}

int lcp(int l, int r){
    if (l > r) return lcp(r, l);
    l++;
    if (l == r) return h[l];
    int k = (int)(log(r - l + 1) / log(2));
    return min(f[l][k], f[r - (1<<k) + 1][k]);
}

int glcp(int l, int r){
    if (l > r) return glcp(r, l);
    if (l == 0) return -1;
    return lcp(l, r);
}

int main(){
    while (scanf("%d%d%d", &n, &m, &k) != EOF){
          memset(a, 0, sizeof a);
          memset(rk, 0, sizeof rk);
          memset(H, 0, sizeof H);
          memset(h, 0, sizeof h);
          memset(sa, 0, sizeof sa);
          memset(f, 0, sizeof f);
          memset(mk, 0, sizeof mk);
          lt = 0;
          memset(b, 0, sizeof b);
          for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), mk[i] = 1;
          a[n + 1] = 10001;
          for (int i = 1; i <= m; ++i) scanf("%d", &a[i + 1 + n]), mk[i + n + 1] = 2;
          N = n + m + 1;
          for (int i = 1; i <= N; ++i) H[a[i]] = 1;
          for (int i = 1; i < MAX_L; ++i) H[i] += H[i - 1];
          for (int i = 1; i <= N; ++i) rk[i] = H[a[i]];
          for (int i = 1; i <= N && build(i) < N; i <<= 1);
          for (int i = 1; i <= N; ++i) sa[rk[i]] = i;
          for (int i = 1, j = 0; i <= N; ++i){
              if (rk[i] == 1) continue;
              for (j = max(0, j - 1); j + i <= N  && sa[rk[i] - 1] + j <= N && a[i + j] == a[sa[rk[i] - 1] + j]; ++j);
              h[rk[i]] = j;
          }
          for (int i = N; i >= 1; --i){
              f[i][0] = h[i];
              for (int k = 1; i + (1<<k) - 1 <= N; ++k)
                  f[i][k] = min(f[i][k - 1], f[i + (1<<k-1)][k - 1]);
          }
          for (int i = 1; i < N; ++i)
          {
              if (mk[sa[i]] == 2) b[++lt] = i;
              //printf("%d\n", h[i]);
          }
          int ans = 0, nxt, pre;
          for (int i = 1; i <= n; ++i){
              nxt = pre = 0;
              int l = 0, r = lt + 1;
              while (l + 1 < r){
                    int mid = (l + r) / 2;
                    if (b[mid] < rk[i]) l = mid; else r = mid;
              }
              pre = b[l], nxt = b[r];              
              if (nxt == 0 && pre == 0) continue;
              if (glcp(nxt, rk[i]) > k || glcp(pre, rk[i]) > k) continue;
              if (glcp(nxt, rk[i]) < k && glcp(pre, rk[i]) < k) continue;
              ans++;
          }
          printf("%d\n", ans);
    }
}
