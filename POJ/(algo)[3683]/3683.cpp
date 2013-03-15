#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 10001, MAX_M = 3000001;
int g[MAX_M], next[MAX_M], c[MAX_N], nm, x[MAX_M], y[MAX_M];
int instack[MAX_N], stack[MAX_N], top, indx[MAX_N], low[MAX_N], cnt, bg[MAX_N], N;
int ops[MAX_N], col[MAX_N], Q[MAX_M], in[MAX_N], ans[MAX_N];
int s[2][MAX_N], t[2][MAX_N];
int n, m;

void addedge(int x, int y){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     nm++;
}

int gettime(int h, int m){
    return h * 60 + m;
}

void dfs(int i){
     indx[i] = low[i] = ++cnt;
     instack[i] = 1;
     stack[++top] = i;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (!indx[j]){
            dfs(j);
            low[i] = min(low[i], low[j]);
         }
         else if (instack[j] && indx[j] < low[i]) low[i] = indx[j];
     }
     if (low[i] == indx[i]){
        int j; N++;
        do{
            j = stack[top--];
            instack[j] = 0;
            bg[j] = N;
        }while (i != j);
     }
}

int op(int i){
    return (i > n) ? (i - n) : (i + n);
}

void add_2(int x, int y){
     if (bg[x] != bg[y]) addedge(bg[y], bg[x]), in[bg[x]]++;
}

void pt(int x){
     printf("%02d:%02d", x / 60 , x % 60);
}

void printtime(int i, int j){
     pt(i); printf(" "); pt(j);
}

int cross(int x, int p, int y, int q){
    int al = s[p][x], ar = t[p][x], bl = s[q][y], br = t[q][y];
    if (bl >= al && bl < ar) return 1;
    if (al >= bl && al < br) return 1;
    return 0;
}

int main(){
    scanf("%d", &n);
    // i : 前段时间  i + n : 后段时间 
    memset(c, -1, sizeof c);
    nm = 0;
    memset(indx, 0, sizeof indx);
    
    for (int i = 1; i <= n; ++i){
        int h1, m1, h2, m2, td;
        scanf("%d:%d%d:%d%d", &h1, &m1, &h2, &m2, &td);
        s[0][i] = gettime(h1, m1);
        t[0][i] = s[0][i] + td;
        t[1][i] = gettime(h2, m2);
        s[1][i] = t[1][i] - td;
    }
    for (int i = 1; i <= n; ++i){
        for (int k = 0; k < 2; ++k)
            for (int j = i + 1; j <= n; ++j)
                for (int p = 0; p < 2; ++p)
                    if (cross(i, k, j, p)){
                       x[++m] = i + k * n;
                       y[m] = j + p * n;
                       addedge(i + k * n, j + (!p) * n);
                       addedge(j + p * n, i + (!k) * n);
                    }
    }
    for (int i = 1; i <= 2 * n; ++i)
        if (!indx[i]) dfs(i);
    int ck = 1;
    for (int i = 1; i <= n; ++i)
        if (bg[i] == bg[i + n]) ck = 0; else ops[bg[i]] = bg[i + n], ops[bg[i + n]] = bg[i];
    if (ck){
       nm = 0;
       memset(c, -1, sizeof c);
       for (int i = 1; i <= m; ++i){
           add_2(x[i], op(y[i]));
           add_2(y[i], op(x[i]));
       }
       int l = 1, r = 0;
       for (int i = 1; i <= N; ++i)
           if (in[i] == 0) Q[++r] = i;
       for (; l <= r; ++l){
           int i = Q[l];
           if (col[i] == 0){
              col[i] = 1;
              col[ops[i]] = -1;
           }
           for (int k = c[i]; k != -1; k = next[k]){
               int j = g[k];
               in[j]--;
               if (!in[j]) Q[++r] = j;
           }
       }
       printf("YES\n");
       for (int i = 1; i <= n; ++i)
           ans[i] = (col[bg[i]] == 1);
       for (int i = 1; i <= n; ++i){
           if (ans[i]) printtime(s[0][i], t[0][i]);
           else printtime(s[1][i], t[1][i]);
           printf("\n");
       }
    }
    else printf("NO\n");
}

