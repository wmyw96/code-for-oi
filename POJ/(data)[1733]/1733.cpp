#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;

const int MAX_N = 200001;
int n, m, x, y, cnt;
char st[MAX_N];
int mk[MAX_N], fa[MAX_N], re[MAX_N];
map<int, int> M;

int find(int i){
    if (fa[i] == i) return i;
    int ret = find(fa[i]);
    mk[i] = (mk[fa[i]] + mk[i]) % 2;
    fa[i] = ret;
    return ret;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i){
        scanf("%d%d", &x, &y);
        scanf("%s", &st);
        --x;
        if (M[x] == 0){
           M[x] = ++cnt;
           fa[cnt] = cnt;
           //re[cnt] = x;
        }
        if (M[y] == 0){
           M[y] = ++cnt;
           fa[cnt] = cnt;
           //re[cnt] = y;
        }
        x = M[x];
        y = M[y];
        int d = (st[0] == 'o');
        int fx = find(x);
        int fy = find(y);
        if (fx == fy){
           int dd = (mk[x] + mk[y]) % 2;
           if (d != dd){
              printf("%d\n", i - 1);
              //system("pause");
              return 0;
           }
        }
        else{
             fa[fx] = y;
             if (mk[x] == 1) mk[fx] = (d) ? (0) : (1);  else mk[fx] = d;
             //printf("%d %d %d %d %d\n", x, fx, y, mk[fx], d);
        } 
    }
    printf("%d\n", m);
    //system("pause");
}
