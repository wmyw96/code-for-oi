#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;
 
#define nd(i) (i - nul)
 
const int MAX_N = 100001, MAX_M = 200001;
struct am{
       map<int, am*> go;
       am *f;
       int cnt, mk, ok, e;
};
map<int, am*>::iterator tmp;
am amn[MAX_M];
am *rd[MAX_N], *nul = amn;
int n, m, L, tot;
int a[MAX_M], Q[MAX_M], ans[MAX_N];
 
int gt()
{
    char ch = getchar();
    for ( ; ch > '9' || ch < '0'; ch = getchar());
    int tmp = 0;
    for ( ; '0' <= ch && ch <= '9'; ch = getchar())
    tmp = tmp * 10 + int(ch) - 48;
    return tmp;
}
 
int main(){
    n = gt(); m = gt();
    am *p, *q, *now;
    for (int i = 1; i <= n; ++i)
        for (int pp = 0; pp < 2; ++pp)
        {
            int l;
            l = gt();
            a[++L] = l;
            for (int i = 1; i <= l; ++i) a[++L] = gt();
        }
 
    for (int i = 1; i <= m; ++i)
    {
        int l, c;
        l = gt();
        p = nul;
        for (int j = 1; j <= l; ++j)
        {
            c = gt();
            if (!p->go[c]) p->go[c] = nul + (++tot);
            p = p->go[c];
        }
        p->ok++;
        rd[i] = p;
    }
     
    int l = 1, r = 0;
    p = nul;
    p->f = nul;
    for (tmp = p->go.begin(); tmp != p->go.end(); tmp++)
    {
        Q[++r] = nd(tmp->second); 
        (tmp->second)->f = nul;
    }
    for (; l <= r; ++l){
        int i = Q[l];
        now = nul + i;
        for (tmp = now->go.begin(); tmp != now->go.end(); tmp++)
        {
            int k = tmp->first;
            q = tmp->second;
            p = now->f;
            while (p != nul && !p->go[k]) p = p->f;
            q->f = p->go[k]; 
            if (!q->f) q->f = nul;
            Q[++r] = nd(q);
        }
    }
     
    int j = 1;
    for (int i = 1; i <= n; ++i)
        for (int pp = 0; pp < 2; ++pp)
        {
            int l = a[j];
            p = nul;++j;
            for (int k = 1; k <= l; ++k, ++j){
                int c = a[j];
                while (p != nul && !p->go[c]) p = p->f;
                p = p->go[c];
                if (p){
                   for (q = p; q != nul && q->mk != i; q = q->f){
                       q->mk = i;
                       q->cnt++;
                       ans[i] += q->ok;
                   }
                }
                else p = nul;
            }
        }
    for (int i = 1; i <= m; ++i) printf("%d\n", rd[i]->cnt);
    for (int i = 1; i < n; ++i) printf("%d ", ans[i]);
    printf("%d\n", ans[n]);
    //system("pause");
}
