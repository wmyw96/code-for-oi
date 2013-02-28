#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 222222;

char s[MAXN];
int c[MAXN], a[MAXN][2], stk[MAXN], ht[MAXN], sa[MAXN], nsa[MAXN], rk[MAXN], nrk[MAXN][2];
LL r[2];

int main() {
    int p;
    while (scanf("%d%*c", &p) && p) {
        gets(s);
        int m = strlen(s);
        s[m] = '#';
        gets(s + m + 1);
        int n = strlen(s);
        memset(c, 0, sizeof c);
        for (int i = 0; i < n; ++i)
            ++c[s[i]];
        for (int i = 0; i < 333; ++i)
            c[i + 1] += c[i];
        for (int i = n - 1; i >= 0; --i)
            sa[--c[s[i]]] = i;
        rk[sa[0]] = 1;
        for (int i = 1; i < n; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        for (int k = 1; k < n; k <<= 1) {
            memset(c, 0, sizeof c);
            for (int i = 0; i < n; ++i) {
                nrk[i][0] = rk[i];
                ++c[nrk[i][1] = i + k < n ? rk[i + k] : 0];
            }
            for (int i = 0; i < n; ++i)
                c[i + 1] += c[i];
            for (int i = n - 1; i >= 0; --i)
                nsa[--c[nrk[i][1]]] = i;
            memset(c, 0, sizeof c);
            for (int i = 0; i < n; ++i)
                ++c[nrk[i][0]];
            for (int i = 0; i < n; ++i)
                c[i + 1] += c[i];
            for (int i = n - 1; i >= 0; --i)
                sa[--c[nrk[nsa[i]][0]]] = nsa[i];
            rk[sa[0]] = 1;
            for (int i = 1; i < n; ++i)
                rk[sa[i]] = rk[sa[i - 1]] + (nrk[sa[i]][0] != nrk[sa[i - 1]][0] || nrk[sa[i]][1] != nrk[sa[i - 1]][1]);
        }
        for (int i = 0, k = 0; i < n; ++i)
            if (--rk[i]) {
                int j = sa[rk[i] - 1];
                while (i + k < n && j + k < n && s[i + k] == s[j + k])
                    ++k;
                ht[rk[i]] = k ? k-- : k;
            }
        int top = 0;
        LL ans = 0;
        memset(a, r[0] = r[1] = 0, sizeof a);
        stk[0] = -1;
        for (int i = 1; i < n; ++i) {
            a[i + 1][sa[i - 1] < m] = 1;
            for (int j = top; j >= 0; --j)
                if (ht[i] < stk[j])
                    for (int k = 0; k < 2; ++k) {
                        if (stk[j] >= p)
                            r[k] -= a[j][k] * LL(stk[j] - p + 1);
                        a[i + 1][k] += a[j][k];
                    }
                else {
                    top = j;
                    if (ht[i] > stk[j]) {
                        stk[++top] = ht[i];
                        a[top][0] = a[top][1] = 0;
                    }
                    for (int k = 0; k < 2; ++k) {
                        if (ht[i] >= p)
                            r[k] += a[i + 1][k] * LL(ht[i] - p + 1);
                        a[top][k] += a[i + 1][k];
                    }
                    break;
                }
            ans += r[sa[i] > m];
        }
        printf("%I64d\n", ans);
    }
    return 0;
}

