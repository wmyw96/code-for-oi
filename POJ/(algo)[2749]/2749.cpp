#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;

const int MAX_N = 1111, MAX_M = 2000001;
int g[MAX_M], next[MAX_M], c[MAX_N], nm, cnt;
int d[3][MAX_N];
int x[MAX_N], y[MAX_N];
int stack[MAX_N], low[MAX_N], indx[MAX_N], instack[MAX_N], N, bg[MAX_N], top;
int n, m, dd, A, B;
int ax[MAX_N], ay[MAX_N], bx[MAX_N], by[MAX_N];

int gd(int x, int y, int p, int q){
    return abs(p - x) + abs(y - q);
}

int gd2(int x, int p, int y, int q){
    return (p != q) * dd + d[p][x] + d[q][y];
}

void addedge(int x, int y){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     nm++;
}

void add(int x, int y){
     addedge(x, y);
     addedge(y, x);
}

void dfs(int i){
     stack[++top] = i, instack[i] = 1;
     indx[i] = low[i] = ++cnt;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (!indx[j]){
            dfs(j);
            low[i] = min(low[i], low[j]);
         }
         else if (instack[j] && low[i] > indx[j]) low[i] = indx[j];
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

int ck(int w){
    nm = 0; N = 0;
    memset(c, -1, sizeof c);
    // i : choose s1 ; i + n : choose s2 ;
    for (int i = 1; i <= A; ++i){
        add(ax[i], op(ay[i]));
        add(ay[i], op(ax[i]));
    }
    for (int i = 1; i <= B; ++i){
        add(bx[i], by[i]);
        add(op(bx[i]), op(by[i]));
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j){
            if (i == j) continue;
            if (gd2(i, 0, j, 0) > w) addedge(i, j + n);
            if (gd2(i, 0, j, 1) > w) addedge(i, j);
            if (gd2(i, 1, j, 0) > w) addedge(i + n, j + n);
            if (gd2(i, 1, j, 1) > w) addedge(i + n, j);
        }
    memset(indx, 0, sizeof indx);
    memset(bg, 0, sizeof bg);
    for (int i = 1; i <= 2 * n; ++i)
        if (!indx[i]) dfs(i);
    for (int i = 1; i <= n; ++i)
        if (bg[i] == bg[i + n]) return 0;
    return 1;
}

int main(){
    scanf("%d%d%d", &n, &A, &B);
    
    //S1: n + 1 ; S2 : n + 2;
    
    scanf("%d%d%d%d", &x[n + 1], &y[n + 1], &x[n + 2], &y[n + 2]);
    
    dd = gd(x[n + 1], y[n + 1], x[n + 2], y[n + 2]);
    int r = 0;
    
    for (int i = 1; i <= n; ++i){
        scanf("%d%d", &x[i], &y[i]);
        d[0][i] = gd(x[i], y[i], x[n + 1], y[n + 1]);
        d[1][i] = gd(x[i], y[i], x[n + 2], y[n + 2]);
    }
    
    //A - hate ; B - like ;
    for (int i = 1; i <= A; ++i) scanf("%d%d", &ax[i], &ay[i]);
    for (int i = 1; i <= B; ++i) scanf("%d%d", &bx[i], &by[i]);
    int l = 0; r = 1000000000;
    while (l + 1 < r){
          int mid = (l + r) / 2;
          if (ck(mid)) r = mid; else l = mid;
    }
    if (r != 1000000000) printf("%d\n", r); else printf("-1\n");
}
