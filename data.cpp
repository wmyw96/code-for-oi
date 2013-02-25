#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;

int main(){
    freopen("1486.in", "w", stdout);
    srand(time(0));
    int n = 200;
    int m = 200;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j) printf("%c", rand() % 2 + 'a');
        printf("\n");
    }
}
