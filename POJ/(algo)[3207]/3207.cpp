#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAX_N = 10001, MAX_M = 700001;
int nn, n;
int x[MAX_N], y[MAX_N], g[MAX_M], next[MAX_M], c[MAX_M], nm;
int low[MAX_N], indx[MAX_N], instack[MAX_N], bg[MAX_N], N, stack[MAX_N], top, cnt;

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
            instack[j] = 0;
            bg[j] = N;
        }while (i != j);
     }
}

int op(int i){return i + n;}

void addedge(int x, int y){
     //printf("%d %d\n", (x > n) ? (x - n) : (x), (y > n) ? (y - n) : y);
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     nm++;
}

int cross(int x, int y, int p, int q){
    if (x > y) swap(x, y);
    if (p > q) swap(p, q);
    return (p < y && p > x) ^ (q < y && q > x);
}

int main(){
    scanf("%d%d", &nn, &n);
    for (int i = 1; i <= n; ++i){
        scanf("%d%d", &x[i], &y[i]);
    }
    memset(c, -1, sizeof c);
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (cross(x[i], y[i], x[j], y[j])){
               addedge(i, op(j));
               addedge(j, op(i));
               addedge(op(j), i);
               addedge(op(i), j);
            }
    for (int i = 1; i <= n * 2; ++i)
        if (!indx[i]) dfs(i);
    int ck = 1;
    for (int i = 1; i <= n; i++)
        if (bg[i] == bg[i + n]) ck = 0;
    //for (int i = 1; i <= n * 2; i++) printf("%d\n", bg[i]);
    if (ck) printf("panda is telling the truth...\n"); else printf("the evil panda is lying again\n");
    //system("pause");
}
