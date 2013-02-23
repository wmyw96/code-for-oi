#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;

typedef long long LL;
const int MAX_N = 2100001;
/* define of sam */
struct sam{
       sam *f, *go[26];
       int l, rt, mk;
};
sam *lst, samn[MAX_N];
int tot;
/* define of main part */
char st[MAX_N];
int H[MAX_N], Q[MAX_N];
int n, m;
void extend(int c){
     sam *p = lst;
     sam *np = samn + (++tot);
     np->l = p->l + 1;
     np->rt = 1;
     np->mk = -1;
     while (p && !p->go[c]) p->go[c] = np, p = p->f;
     if (!p) np->f = samn;
     else{
          sam *q = p->go[c];
          if (q->l == p->l + 1) np->f = q;
          else{
               sam *nq = samn + (++tot);
               nq->l = p->l + 1;
               nq->rt = 0;
               nq->mk = -1;
               memcpy(nq->go, q->go, sizeof nq->go);
               nq->f = q->f;
               q->f = np->f = nq;
               while (p && p->go[c] == q) p->go[c] = nq, p = p->f;
          }
     }
     lst = np;
}
               
int main(){
    scanf("%s", &st);
    int l = strlen(st);
    lst = samn;
    for (int i = 0; i < l; ++i) extend(st[i] - 'a');
    
    for (int i = 1; i <= tot; ++i) H[samn[i].l]++;
    for (int i = 1; i <= l; ++i) H[i] += H[i - 1];
    for (int i = tot; i >= 1; --i) Q[H[samn[i].l]--] = i;
    
    for (int i = tot; i >= 1; --i){
        sam *p = samn + Q[i];
        p->f->rt += p->rt;
    }
    
    scanf("%d", &n);
    for (int kk = 1; kk <= n; ++kk){
        scanf("%s", &st);
        l = strlen(st);
        int ll = l;
        sam *p = samn;
        LL ans = 0;
        int len = 0;
        for (int i = 0; i < 2 * l - 1; ++i){
            int c = st[i % l] - 'a';
            while (p && !p->go[c]) len = min(len, p->l), p = p->f;
            if (!p) p = samn;
            len = min(len, p->l);
            if (p->go[c]){
               p = p->go[c];
               len++;
               while (p->f && p->f->l + 1 > l) p = p->f, len = min(len, p->l);
               if (i >= l - 1 && len >= ll){
                  ans += p->rt * (p->mk != kk);
                  p->mk = kk;
               }
            }
        }
        cout<<ans<<endl;
    }
}
