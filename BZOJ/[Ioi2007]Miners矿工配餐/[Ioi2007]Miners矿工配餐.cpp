#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 200001, INF = -1000000000;
int f[11][11][11][11], g[11][11][11][11], ct[4];
int n;
char st[MAX_N];
int t[MAX_N];

void clear(){
    for (int i = 0; i <= 3; ++i)
        for (int j = 0; j <= 3; ++j)
            for (int k = 0; k <= 3; ++k)
                for (int p = 0; p <= 3; ++p)
                    f[i][j][k][p] = INF;
}

int calc(int x, int y, int z){
    memset(ct, 0, sizeof ct);
    ct[x]++, ct[y]++, ct[z]++;
    return (ct[1] > 0) + (ct[2] > 0) + (ct[3] > 0);
}

int main(){
    scanf("%d", &n);
    scanf("%s", &st);
    for (int i = 1; i <= n; ++i){
        if (st[i - 1] == 'M') t[i] = 1;
        if (st[i - 1] == 'B') t[i] = 2;
        if (st[i - 1] == 'F') t[i] = 3;
    }
    clear();
    f[0][0][0][0] = 0;
    int ans = 0;
    for (int nt = 1; nt <= n; ++nt){
        //give 0
        memcpy(g, f, sizeof g);
        int c = t[nt];
        clear();
        for (int i = 0; i <= 3; ++i)
            for (int j = 0; j <= 3; ++j)
              if ((j == 0 && i == 0) || j != 0)
                for (int k = 0; k <= 3; ++k)
                    for (int p = 0; p <= 3; ++p)
                      if ((p == 0 && k == 0) || p != 0){
                        f[j][c][k][p] = max(f[j][c][k][p], g[i][j][k][p] + calc(i, j, c));
                        f[i][j][p][c] = max(f[i][j][p][c], g[i][j][k][p] + calc(k, p, c));
                        if (f[j][c][k][p] > ans){
                           ans = f[j][c][k][p];
                           //printf("[%d %d %d %d]  %d\n", j, c, k, p, ans);
                        }
                        if (f[i][j][p][c] > ans){
                           ans = f[i][j][p][c];
                           //printf("[%d %d %d %d]  %d\n", i, j, p, c, ans);
                        }
                      }
        //printf("---- %d ----   %d\n", nt, ans);
    }
    for (int i = 0; i <= 3; ++i)
        for (int j = 0; j <= 3; ++j)
            for (int k = 0; k <= 3; ++k)
                for (int p = 0; p <= 3; ++p)
                    ans = max(ans, f[i][j][k][p]);
    printf("%d\n", ans);
    //system("pause");
}

/*
6 
MBMFFB
*/
