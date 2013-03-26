#include<iostream>
#include<cstdio> 
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 201, MAX_C = 101;
struct bign{
       int n, a[MAX_N];
       void clear(int i){
            memset(a, 0, sizeof a);
            a[n = 1] = i;
       }
};

bign operator + (bign x, bign y){
     bign c;
     memset(c.a, 0, sizeof c.a);
     c.n = max(x.n, y.n);
     for (int i = 1; i <= c.n; ++i){
         c.a[i] += x.a[i] + y.a[i];
         c.a[i + 1] += c.a[i] / 10;
         c.a[i] %= 10;
     }
     if (c.a[c.n + 1] > 0) c.n++;
     return c;
}

int cok(bign x){
    return x.n > 1 || x.a[1] > 0;
}

void print(bign x){
     for (int i = x.n; i >= 1; --i) printf("%d", x.a[i]);
     printf("\n");
}

unsigned char st[MAX_N];
int mc[1001];
int C, m, n, tot;
int nxt[MAX_N][MAX_C];
int f[MAX_N], ok[MAX_N], Q[MAX_N];
bign F[MAX_N][MAX_N];

int main(){
    scanf("%d%d%d", &C, &m, &n);
    scanf("%s", &st);
    for (int i = 0; i < C; ++i){
        mc[st[i]] = i;
    }
    for (int i = 1; i <= n; ++i){
        scanf("%s", &st);
        int p = 0;
        for (int j = 0; st[j] != '\0'; ++j){
            int c = mc[st[j]];
            if (!nxt[p][c]) nxt[p][c] = ++tot;
            p = nxt[p][c];
        }
        ok[p] = 1;
    }
    int l = 1, r = 0;
    for (int k = 0; k < C; ++k)
        if (nxt[0][k]) Q[++r] = nxt[0][k];
    for (; l <= r; ++l){
        int i = Q[l];
        for (int k = 0; k < C; ++k){
            int p = f[i], q = nxt[i][k];
            while (p && !nxt[p][k]) p = f[p];
            if (q){
                   f[q] = nxt[p][k];
                   ok[q] |= ok[f[q]];
                   Q[++r] = q;
            }
            else nxt[i][k] = nxt[p][k];
        }
    }
    
    F[0][0].clear(1); 
    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= tot; ++j)
            if (cok(F[i][j])){
               for (int k = 0; k < C; ++k){
                   int q = nxt[j][k];
                   if (!ok[q])
                      F[i + 1][q] = F[i + 1][q] + F[i][j];//, printf("%d %d ", q, i + 1), print(F[i + 1][q]);
               }
            }
    bign ans;
    ans.clear(0);
    for (int i = 0; i <= tot; ++i)
        ans = F[m][i] + ans;
    print(ans); 
    //system("pause");
}
