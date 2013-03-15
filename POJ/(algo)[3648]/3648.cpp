#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 20001, MAX_M = 800001;
int g[MAX_M], next[MAX_M], c[MAX_N], nm, x[MAX_M], y[MAX_M];
int instack[MAX_N], stack[MAX_N], top, indx[MAX_N], low[MAX_N], cnt, bg[MAX_N], N;
int ops[MAX_N], col[MAX_N], Q[MAX_M], in[MAX_N], ans[MAX_N];
int n, m;

int op(int i){
    if (i > n) return i - n; else return i + n;
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

void add_2(int x, int y){
     if (bg[x] != bg[y]) addedge(bg[y], bg[x]), in[bg[x]]++;
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

int work(){
    nm = 0;
    memset(c, -1, sizeof c);
    memset(in, 0, sizeof in);
    memset(indx, 0, sizeof indx);
    
    // i : man ,i + n : woman
    addedge(n + 1, 1);
    for (int i = 1; i <= m; ++i){
        char chx, chy;
        scanf("%d%c%d%c", &x[i], &chx, &y[i], &chy);
        x[i]++, y[i]++;
        if (chx == 'w') x[i] += n;
        if (chy == 'w') y[i] += n;
        addedge(x[i], op(y[i]));
        addedge(y[i], op(x[i]));
    }
    for (int i = 1; i <= n * 2; ++i)
        if (!indx[i]) dfs(i);
    int ck = 1;
    for (int i = 1; i <= n; ++i)
        if (bg[i] == bg[i + n]) ck = 0; else ops[bg[i]] = bg[i + n], ops[bg[i + n]] = bg[i];
    if (ck){
       nm = 0;
       memset(c, -1, sizeof c);
       add_2(1 + n, 1);
       for (int i = 1; i <= m; ++i){
           add_2(x[i], op(y[i]));
           add_2(y[i], op(x[i]));
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
           if (col[bg[i]] == -1) ans[i] = 0; else ans[i] = 1; //man : 0, woman : 1
       for (int i = 2; i <= n; ++i){
           printf("%d", i - 1);
           if (ans[i]) printf("w"); else printf("h");
           if (i != n) printf(" "); else printf("\n");
       }
    }
    else printf("bad luck\n");
    //system("pause");
}

int main(){
    while (scanf("%d%d", &n, &m) != EOF){
          if (n == 0 && m == 0) return 0;
          work();
    }
}

/*
4 4
1h2h
2w3w
1h3h
0h 2w
*/
