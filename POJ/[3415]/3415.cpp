#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAX_N = 500001;
typedef long long LL;
struct ls{
       int a, b, c;
       void mp(int aa, int bb, int cc){a = aa, b = bb, c = cc;}
}s[MAX_N], ss[MAX_N]; 
int a[MAX_N], cnt[MAX_N], rk[MAX_N], sa[MAX_N], h[MAX_N], H[MAX_N], mk[MAX_N];
char st[MAX_N];
int k, n;
int dta[2][MAX_N], top[2], sl[2][MAX_N], sr[2][MAX_N];
LL sum[2];
 
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
        rk[s[i].c] = rk[s[i - 1].c] + (s[i].a != s[i - 1].a || s[i].b != s[i - 1].b),
        ret = max(ret, rk[s[i].c]);
    return ret;
}
 
void upd(int c, int i){
    while (top[c] > 0 && sl[c][top[c]] > h[i] - k + 1){
          sum[c] -= (LL)dta[c][top[c]] * (sr[c][top[c]] - sl[c][top[c]] + 1);
          if (top[c] > 1) dta[c][top[c] - 1] += dta[c][top[c]];
          dta[c][top[c]--] = 0;
    }
    if (top[c] > 0 && h[i] - k + 1 < sr[c][top[c]]){
		sum[c] -= (LL)dta[c][top[c]] * (sr[c][top[c]] - (h[i] - k + 1));
		sr[c][top[c]] = (h[i] - k + 1);
    }
}
 
void upu(int c, int i){
     if (sr[c][top[c]] < h[i] - k + 1){
		top[c]++;
		sl[c][top[c]] = (top[c] > 1) ? (sr[c][top[c] - 1] + 1) : 1;
		sr[c][top[c]] = h[i] - k + 1;
     }
     if (h[i] - k + 1 > 0) sum[c] += h[i] - k + 1;
     if (top[c] > 0) dta[c][top[c]]++;
}
 
int main(){
    while (scanf("%d", &k) != EOF){
          if (!k) break;
          
          sum[0] = sum[1] = top[0] = top[1] = 0;
          memset(H, 0, sizeof H); memset(rk, 0, sizeof rk);
          memset(sl, 0, sizeof sl); memset(sr, 0, sizeof sr);
          memset(dta, 0, sizeof dta);
          memset(a, 0, sizeof a);
          
          scanf("%s", &st);int l = strlen(st), ret = 0;
          for (int i = 1; i <= l; ++i) 
              a[i] = st[i - 1], H[a[i]] = 1, ret = max(ret, a[i]), mk[i] = 0;
          n = l + 1;
          scanf("%s", &st);l = strlen(st);
          for (int i = 1; i <= l; ++i) 
              a[i + n] = st[i - 1], H[a[i + n]] = 1, ret = max(ret, a[i + n]), mk[i + n] = 1;
          a[n] = ++ret, n += l, H[ret] = 1;
          for (int i = 1; i <= ret; ++i) H[i] += H[i - 1];
          for (int i = 1; i <= n; ++i) rk[i] = H[a[i]];
          for (int i = 1; i <= n && build(i) < n; i <<= 1);
          for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
          for (int i = 1, j = 0; i <= n; ++i){
              if (rk[i] == 1) continue;
              for (j = max(j - 1, 0); j <= n && a[i + j] == a[sa[rk[i] - 1] + j];) ++j;
              h[rk[i]] = j;
          }
          LL ans = 0;
          for (int i = 1; i < n; ++i){
              int p = sa[i];
              int c = mk[p];
              upd(0, i); upd(1, i);
              upd(c, i + 1); 
              upu(c, i + 1);
              ans += sum[!c];
          }
          cout<<ans<<endl;
    } 
}

