#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
 
const int MAX_N = 1000001;
struct T_T{
       int s, i, mk;
}t[MAX_N];
 
struct O_O{
       int l, i;
};
 
bool operator < (O_O x, O_O y){
     return x.l < y.l;
};
 
priority_queue<O_O> Q;
 
int cmp(T_T x, T_T y){
    if (x.s != y.s) return x.s < y.s;
    return x.mk < y.mk;
}
 
int n, m, C, U, ct, ans;
int x[MAX_N], y[MAX_N], w[MAX_N], hash[MAX_N];
 
int main(){    
    scanf("%d%d%d", &m, &n, &C);
    U = C;
    for (int i = 1; i <= m; ++i){
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
         
        t[++ct].s = x[i];
        t[ct].i = i;
        t[ct].mk = 1;
         
        t[++ct].s = y[i];
        t[ct].i = i;
        t[ct].mk = -1;
    }
     
    sort(t + 1, t + 1 + ct, cmp);
     
    int j = 1;
     
    O_O p;
    p.l = p.i = 0;
    Q.push(p);
     
    for (int i = 1; i <= n; ++i)
        for (; t[j].s == i; ++j){
             
            int k = t[j].i; //k为现在是哪一批. 
             
            if (t[j].mk > 0){
                         
               int cnt = min(w[k], U);//cnt现在一批的数量. 
               while (1){
                     O_O p = Q.top();
                     if (p.l > y[k] && cnt >= C + hash[p.i]){
                        C += hash[p.i];
                        hash[p.i] = 0;
                        Q.pop();
                     }
                     else break;
               }
                
               O_O p = Q.top();
               if (p.l > y[k]){
                  if (cnt > C){
                     int cc = cnt - C; //删去的数量.
                     hash[p.i] -= cc;
                     C += cc; 
                  }
                   
                  O_O q;
                  q.i = k, q.l = y[k];
                  Q.push(q);
                  hash[k] = cnt;
                  C -= cnt;
               }
               else{
                    cnt = min(cnt, C);
                    if (cnt){
                       O_O q;
                       q.i = k, q.l = y[k];
                       Q.push(q);
                       hash[k] = cnt;
                       C -= cnt;
                    }
               }
             
            }
            else{
                 int cnt = hash[k];
                 C += cnt;
                 ans += cnt;
                 hash[k] -= cnt;
            }
        }
         
    printf("%d\n", ans);
}
