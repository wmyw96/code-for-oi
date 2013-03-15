#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 10001, MAX_M = 100001;
int c[MAX_N], next[MAX_M], g[MAX_M], nm;
int instack[MAX_N], stack[MAX_N], indx[MAX_N], low[MAX_N], cnt, top, N, bg[MAX_N];
int n, m;
int op[MAX_N], a[MAX_M], b[MAX_M];

void dfs(int i){
     instack[i] = 1;
     stack[++top] = i;
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
            instack[j] = 0; 
            bg[j] = N;
        }while (i != j);
     }
}

void addedge(int x, int y){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     nm++;
}

int check(int w){
    nm = 0;
    memset(c, -1, sizeof c);
    cnt = 0;
    memset(indx, 0, sizeof indx);
    for (int i = 1; i <= w; ++i){
        addedge(op[a[i]], b[i]);
        addedge(op[b[i]], a[i]);
    }
    for (int i = 1; i <= n * 2; ++i)
        if (!indx[i]) dfs(i);
    for (int i = 1; i <= n * 2; ++i)
        if (bg[i] == bg[op[i]]) return 0;
    return 1;
}

int work(){
    memset(op, 0, sizeof op);
    for (int i = 1; i <= n; ++i){
        int x, y;
        scanf("%d%d", &x, &y);
        x++, y++;
        op[x] = y, op[y] = x;
    }
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &a[i], &b[i]), a[i]++, b[i]++;
    int l = 0, r = m + 1;
    while (l + 1 < r){
          int mid = (l + r) / 2;
          if (check(mid)) l = mid; else r = mid;
    }
    printf("%d\n", l);
}

int main(){
    while (scanf("%d%d", &n, &m) != EOF){
          if (n == 0 && m == 0) return 0;
          work();
    }
}
//题目中0开始，实际上从1开始，没有加T_T
//Tarjan写错：instack[j] = 1; 应该是instack[j] = 0;
//加边 g[nm] = y; 写成了g[++nm] = y 导致边的紊乱
 
 
