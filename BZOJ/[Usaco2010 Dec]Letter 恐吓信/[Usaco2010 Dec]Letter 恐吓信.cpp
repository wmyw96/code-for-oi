#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 200001;
struct sam{
       sam *f, *go[26];
       int l;
};
sam samn[MAX_N], *lst;
int n, m, tot;
char st[MAX_N];
int d[MAX_N], f[MAX_N];

struct DQueue{
       int mn[MAX_N], l, r, Qt[MAX_N];
       
       void clear(){
            l = r = 0;
            memset(mn, 0, sizeof mn);
            memset(Qt, 0, sizeof Qt);
       }
       
       void pop(int t){
            while (Qt[l] < t && l <= r) l++;
       }
       
       void push(int t, int v){
            while (l <= r && v < mn[l]) l++;
            mn[++r] = v;
            Qt[r] = t;
       }
       
       int getmin(){
           return mn[l];
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
               memcpy(nq->go, q->go, sizeof nq->go);
               nq->l = p->l + 1;
               nq->f = q->f;
               q->f = np->f = nq;
               while (p && p->go[c] == q) p->go[c] = nq, p = p->f;
          }
     }
     lst = np;
}

int main(){
    scanf("%d%d", &n ,&m);
    int nn = 0;
    lst = samn;
    while (nn < n){
          scanf("%s", &st);
          int l = strlen(st);
          nn += l;
          for (int i = 1; i <= l; ++i) extend(st[i - 1] - 'A');
    }
    nn = 0;
    int len = 0;
    sam *p = samn;
    while (nn < m){
          scanf("%s", &st);
          int l = strlen(st);
          for (int i = 0; i < l; ++i){
              int c = st[i] - 'A';
              while (p->f && !p->go[c]){
                    p = p->f;
                    len = min(len, p->l);
              }
              if (p->go[c]){
                 p = p->go[c];
                 len++;
                 d[nn + i + 1] = len;
              }
          }
          nn += l;
    }
    f[0] = 0;
    Q.clear();
    Q.push(0, f[0]);
    for (int i = 1; i <= m; ++i){
        Q.pop(i - d[i]);
        f[i] = Q.getmin() + 1;
        Q.push(i, f[i]);
    }
    printf("%d\n", f[m]);
}

/*
38 9
THEQUICKBROWNFOXDO
GJUMPSOVERTHELAZYDOG
FOXDOG
DOG
*/
