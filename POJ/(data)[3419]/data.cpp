#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;

int n, m, w;

int rand(int l, int r){
    return rand() % (r - l + 1) + 1;
}

int main(){
    srand(time(0));
    freopen("1.in", "w", stdout);
    n = 20;
    w = 6;
    m = 10;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; ++i) printf("%d ", rand() % w + 1);
    printf("\n");
    for (int i = 1; i <= m; ++i){
        int x = rand(1, n - 1);
        int y = x + rand(x + 1, n);
        printf("%d %d\n", x - 1, y - 1);
    }
}
