#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_L = 1001, MAX_N = 11, MAX_M = 11;
int b[MAX_M], a[MAX_N], sg[MAX_L], h[MAX_L];
int n, m;

int ck(){
    int ans = sg[a[1]];
    for (int i = 2; i <= n; ++i)
        ans ^= sg[a[i]];
    return ans;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) scanf("%d", &b[i]);
    sort(b + 1, b + 1 + m);
    sg[0] = 0;
    memset(h, 0, sizeof h);
    for (int j = 1; j < MAX_L; ++j){
        for (int k = 1; k <= m; ++k)
            if (j - b[k] >= 0) h[sg[j - b[k]]] = j;
        for (int k = 0; k < MAX_L; ++k)
            if (h[k] != j) {sg[j] = k; break;}
    }
    if (ck()){
       printf("YES\n");
       for (int i = 1; i <= n; ++i)
           for (int j = 1; j <= m; ++j)
               if (a[i] - b[j] >= 0){
                  a[i] -= b[j];
                  if (!ck()){
                     printf("%d %d\n", i, b[j]);
                     return 0;
                  }
                  a[i] += b[j];
               }
    }
    else printf("NO\n");
}
