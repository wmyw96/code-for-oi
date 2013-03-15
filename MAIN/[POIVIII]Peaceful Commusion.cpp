#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX_N = 20001, MAX_M = 80001;
int g[MAX_M], next[MAX_M], c[MAX_N], nm, x[MAX_M], y[MAX_M];
int instack[MAX_N], stack[MAX_N], top, indx[MAX_N], low[MAX_N], cnt, bg[MAX_N], N;
int ops[MAX_N], col[MAX_N], Q[MAX_M], in[MAX_N], ans[MAX_N];
int n, m;

void dfs(int i){
     stack[++top] = i;
     instack[i] = 1;
     indx[i] = low[i] = ++cnt;
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
            bg[j] = N;
            instack[j] = 0;
        }while (j != i);
     }
}

void addedge(int x, int y){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     ++nm;
}

void add(int x, int y){
     if (bg[x] != bg[y]) addedge(bg[y], bg[x]), in[bg[x]]++;
}
       
int op(int i){
    return (i % 2) ? (i + 1) : (i - 1);
}

int main(){
    memset(c, -1, sizeof c);
    scanf("%d%d", &n, &m);
    n *= 2;
    for (int i = 1; i <= m; ++i){
        scanf("%d%d", &x[i], &y[i]);
        addedge(x[i], op(y[i]));
        addedge(y[i], op(x[i]));
        addedge(op(y[i]), x[i]);
        addedge(op(x[i]), y[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (!indx[i]) dfs(i);
    int ck = 1;
    for (int i = 1; i <= n; i += 2)
        if (bg[i] == bg[i + 1]) {ck = 0; break;}
           else ops[bg[i + 1]] = bg[i], ops[bg[i]] = bg[i + 1];
    if (ck){
       nm = 0;
       memset(c, -1, sizeof c);
       for (int i = 1; i <= m; ++i){
           add(x[i], op(y[i]));
           add(y[i], op(x[i]));
       }
       int l = 1, r = 0;
       for (int i = 1; i <= N; ++i)
           if (in[i] == 0) Q[++r] = i;
       for (;l <= r; ++l){
           int i = Q[l];
           if (col[i] != -1){
              col[i] = 1;
              col[ops[i]] = -1;
           }
           for (int k = c[i]; k != -1; k = next[k]){
               int j = g[k];
               in[j]--;
               if (in[j] == 0) Q[++r] = j;
           }
       }
       for (int i = 1; i <= n; ++i)
           if (col[bg[i]] == 1) ans[i] = 1;
       for (int i = 1; i <= n; ++i)
           if (ans[i]) printf("%d\n", i);
    }
    else printf("NIE\n");
}

