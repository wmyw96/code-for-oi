#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<set>
#include<map>
using namespace std;

const int MAX_N = 200001, MAX_T = 20000001;
struct node{
       node *l, *r;
       int s;
};
node T[MAX_T];
node *root[MAX_N];
int a[MAX_N];
int n, m, k, tot, b[MAX_N];

void newn(node *&p, int d){
     p = T + (++tot);
     p->l = p->r = T;
     p->s = d;
}

void insert(node *x, node *&y, int l, int r, int st){
     newn(y, x->s + 1);
     if (l == r) return;
     int mid = (l + r) >> 1;
     if (st <= mid){
        y->r = x->r;
        insert(x->l, y->l, l, mid, st);
     }
     else{
          y->l = x->l;
          insert(x->r, y->r, mid + 1, r, st);
     }
}

int query(node *x, node *y, int l, int r, int v){
    if (l == r) return l;
    int s = y->l->s - x->l->s;
    int mid = (l + r) >> 1;
    if (s >= v) return query(x->l, y->l, l, mid, v);
          else  return query(x->r, y->r, mid + 1, r, v - s);
}

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + 1 + n);
    m = unique(b + 1, b + 1 + n) - b - 1;
    root[0] = T;
    root[0]->l = root[0]->r = T, root[0]->s = 0;
    for (int i = 1; i <= n; ++i)
        insert(root[i - 1], root[i], 1, m, lower_bound(b + 1, b + m + 1, a[i]) - b);
    for (int i = 1; i <= k; ++i){
        int kk, l, r;
        scanf("%d%d%d", &l, &r, &kk);
        printf("%d\n", b[query(root[l - 1], root[r], 1, m, kk)]);
    }
}
