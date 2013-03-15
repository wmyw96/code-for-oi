#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 10001, MAX_M = 5000001;
int m, n;
int g[MAX_M], next[MAX_M], c[MAX_M], nm;
int low[MAX_N], indx[MAX_N], instack[MAX_N], bg[MAX_N], N, stack[MAX_N], top, cnt;
char st[11];

int op(int i){
    if (i > n) return i - n; else return i + n;
}

void addedge(int x, int y){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     nm++;
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

int main(){
    scanf("%d%d", &n, &m);
    nm = 0;
    memset(c, -1, sizeof c);
    //i 表示 0, i + n 表示 1. 
    for (int i = 1; i <= m; ++i){
        int x, y, cc;
        scanf("%d%d%d", &x, &y, &cc);
        ++x, ++y;
        scanf("%s", &st);
        if (st[0] == 'A'){
           if (cc == 0) addedge(x + n, y), addedge(y + n, x);
                 else addedge(x, x + n), addedge(y, y + n);
        }
        if (st[0] == 'O'){
           if (cc == 0) addedge(x + n, x), addedge(y + n, y);
                 else addedge(x, y + n), addedge(y, x + n);
        }
        if (st[0] == 'X'){
           if (cc == 0) addedge(x, y), addedge(y, x), addedge(x + n, y + n), addedge(y + n, x + n);
                 else addedge(x, y + n), addedge(y, x + n), addedge(x + n, y), addedge(y + n, x);
        }
    }
    for (int i = 1; i <= n * 2; ++i)
        if (!indx[i]) dfs(i);
    int ck = 1;
    for (int i = 1; i <= n; ++i)
        if (bg[i] == bg[i + n]) ck = 0;
    if (ck) printf("YES\n"); else printf("NO\n");
    //system("pause");
}
