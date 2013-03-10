#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
int n, m, k;

int main(){
    srand(time(0));
    freopen("f.in", "w", stdout);
    n = 200000;
    m = 200000;
    k = 1000;
    printf("%d %d %d\n", n, k, m);
    for (int i = 1; i <= m; ++i) printf("%d\n", rand() % n + 1);
    for (int i = 1; i < n; ++i){
        int x = rand() % (i) + 1;
        printf("%d %d %d\n", i + 1, x, rand() % 10 - rand() % 6);
    }
}
