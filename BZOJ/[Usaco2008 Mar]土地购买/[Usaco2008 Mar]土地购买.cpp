#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 100001;
typedef long long LL;
struct node{
       int x, y;
}b[MAX_N], a[MAX_N];

struct que{
       int s, t, i;
};
que q[MAX_N];
int top, n;
LL F[MAX_N];


int cmp(node x, node y){
    if (x.x != y.x) return x.x < y.x;
    return x.y < y.y;
}

LL calc(int j, int i){
   return F[j] + (LL)b[j + 1].y * b[i].x;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%d%d", &a[i].x, &a[i].y);
    } 
    sort(a + 1, a + 1 + n, cmp);
    top = 1;
    b[1] = a[1];
    for (int i = 1; i <= n; ++i){
        while (b[top].y <= a[i].y && top > 0) top--;
        b[++top] = a[i];
    }
    n = top;
    
    int l = 1, r = 0;
    F[0] = 0;
    q[r = 1].s = 1;
    q[r].t = n;
    q[r].i = 0;
    for (int i = 1; i <= n; ++i){
        F[i] = calc(q[l].i, i);
        q[l].s++;
        if (q[l].s > q[l].t) l++;
        while (l <= r && calc(q[r].i, q[r].s) > calc(i, q[r].s)){
              q[r].i = q[r].s = q[r].t = 0;
              r--;
        }
        int ll = (l <= r) ? (q[r].t + 1) : (i + 1);
        if (l <= r && calc(q[r].i, q[r].s) <= calc(i, q[r].s) && calc(q[r].i, q[r].t) > calc(i, q[r].t)){
           int f = q[r].s, t = q[r].t;
           while (f + 1 < t){
                 int mid = (f + t) / 2;
                 if (calc(q[r].i, mid) <= calc(i, mid)) f = mid; else t = mid;
           }
           q[r].t = f;
           ll = t;
        }
        if (ll <= n){
           q[++r].s = ll;
           q[r].t = n;
           q[r].i = i;
        }
    }
    cout<<F[n]<<endl;
}
