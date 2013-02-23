#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
/*define of sam*/
struct sam{
       sam *f, *go[3];
       int l;
};
sam samn[3100001];
sam *lst;
int tot;
/*define of main part*/
const int SUP = 1000000000;
char st[1100001];
int f[1100001], d[1100001];
int n, m, N;
 
struct queue{
       int l, r;
       int t[1100001], mn[1100001];
       void clear(int limit){
            l = r = 0;
            for (int i = 0; i <= limit; ++i) t[i] = mn[i] = 0;
       }
       void del(int p){
            while (l <= r && t[l] < p){
                  ++l;
            }
       }
       void add(int v, int p){
            while (l <= r && v < mn[r]){
                  mn[r] = t[r] = 0;
                  r--;
            }
            mn[++r] = v;
            t[r] = p;
       }
       int get(){
           if (l <= r) return mn[l];
           else return SUP;
       }
}Q;
 
 
void extend(int c){
     sam *p = lst;
     sam *np = samn + (++tot);
     np->l = p->l + 1;
     while (p && !p->go[c]) p->go[c] = np, p = p->f;
     if (!p) np->f = samn;
     else{
          sam *q = p->go[c];
          if (q->l == p->l + 1) np->f = q;
          else{
               sam *nq = samn + (++tot);
               nq->l = p->l + 1;
               memcpy(nq->go, q->go, sizeof nq->go);
               nq->f = q->f;
               q->f = np->f = nq;
               while (p && p->go[c] == q) p->go[c] = nq, p = p->f;
          }
     }
     lst = np;
}
 
int ck(int w){
    f[0] = 0;
    Q.clear(N);
    for (int i = 1, l = 0, r = 1 - w; i <= N; ++i, ++r){
        f[i] = f[i - 1] + 1;
        l = i - d[i];
        if (r >= 0) Q.add(f[r], r);
        Q.del(l);
        if (l <= r){
           f[i] = min(f[i], Q.get());
        }
    }
    return f[N] <= N / 10;
}
 
int main(){
    scanf("%d%d", &n, &m);
     
    lst = samn;
    for (int i = 1; i <= m; ++i){
        scanf("%s", &st);
        int l = strlen(st);
        for (int j = 0; j < l; ++j) extend(st[j] - '0');
        if (i != m) extend(2);
    }
    while (n--){
          scanf("%s", &st);
          sam *p = samn;
          int l = strlen(st);
          int len = 0;
          for (int i = 0; i < l; ++i){
              int c = st[i] - '0';
              while (p && !p->go[c]){
                    p = p->f;
                    len = min(len, p->l);
              }
              if (p) p = p->go[c], len++;
              d[i + 1] = len;
          }
          N = l;
          int r = N + 1; l = 0;
          while (l + 1 < r){
                int mid = (l + r) >> 1;
                if (ck(mid)) l = mid; else r = mid;
          }
          printf("%d\n", l);
    }
}
