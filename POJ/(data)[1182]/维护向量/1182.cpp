#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm> 
using namespace std;
// A - (1) -> B :  A eat B;
// B - (2) -> A :  B eat A;
// A - (0) -> B :  A is B;

const int MAX_N = 100001;
int k, d, x, y, N, ans;
int fa[MAX_N], mk[MAX_N];

int find(int i){
    if (i == fa[i]) return i;
    int ret = find(fa[i]);
    mk[i] = (mk[i] + mk[fa[i]]) % 3;
    fa[i] = ret;
    return ret;
}

int main(){
    scanf("%d%d", &N, &k);
    for (int i = 1; i <= N; ++i) fa[i] = i;
    for (int i = 1; i <= k; ++i){
          scanf("%d%d%d", &d, &x, &y);
          d--;
          if (x <= N && y <= N){
             int fx = find(x);
             int fy = find(y);
             if (fx == fy){
                int dd;
                // x -> y 's relation
                
                /*if (mk[x] == mk[y]) dd = 0;
                if (mk[x] == 0 && mk[y] == 1) dd = 2;
                if (mk[x] == 0 && mk[y] == 2) dd = 1;
                if (mk[x] == 1 && mk[y] == 0) dd = 1;
                if (mk[x] == 2 && mk[y] == 0) dd = 2;
                if (mk[x] == 1 && mk[y] == 2) dd = 2;
                if (mk[x] == 2 && mk[y] == 1) dd = 1;*/
                
                //printf("%d %d %d %d\n", mk[x], mk[y], fa[x], fa[y]);
                dd = (mk[x] - mk[y] + 3) % 3;
                if (d == dd) ans++;
             }
             else{
                  // x - (1) -> y
                  if (d == 1){
                     if (mk[x] == 0) mk[fx] = 1;
                     else
                       if (mk[x] == 1) mk[fx] = 0;
                       else if (mk[x] == 2) mk[fx] = 2;
                     fa[fx] = y;
                  }
                  else{
                       if (mk[x] == 0) mk[fx] = 0;
                        else if (mk[x] == 1) mk[fx] = 2;
                        else if (mk[x] == 2) mk[fx] = 1;
                       fa[fx] = y;
                  }
                  ans++;
             }
          }
    }
    printf("%d\n", k - ans);
}
