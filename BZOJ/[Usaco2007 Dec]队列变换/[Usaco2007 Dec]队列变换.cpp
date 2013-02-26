#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 100001;
struct ls{
       int a, b, c;
       void mp(int x, int y, int z){
            a = x, b = y, c = z;
       }
}s1[MAX_N], s2[MAX_N];
int rk[MAX_N], H[MAX_N], sa[MAX_N], cnt[MAX_N], a[MAX_N];
int n, N;
char ans[MAX_N];

int build(int w){
    for (int i = 1; i <= n; ++i)
        s1[i].mp(rk[i], rk[i + w], i);
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; ++i) cnt[s1[i].b]++;
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) s2[cnt[s1[i].b]--] = s1[i];
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; ++i) cnt[s2[i].a]++;
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) s1[cnt[s2[i].a]--] = s2[i];
    for (int i = 1; i <= n; ++i)
        rk[s1[i].c] = rk[s1[i - 1].c] + (s1[i].a != s1[i - 1].a || s1[i].b != s1[i - 1].b);
    return rk[s1[n].c];
}

int main(){
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i){
        char ch;
        scanf(" %c", &ch);
        a[i] = ch - 'A' + 1;
        H[a[i]] = 1;
    }
    a[N + 1] = 27;
    n = N * 2 + 1;
    for (int i = N + 2; i <= n; ++i)
        a[i] = a[n - i + 1];
    for (int i = 1; i <= 27; ++i) H[i] += H[i - 1];
    for (int i = 1; i <= n; ++i) rk[i] = H[a[i]];
    for (int i = 1; i <= n && build(i) < n; i <<= 1);
    
    for (int i = 1, l = 1, r = N; i <= N; ++i){
        ans[i] = ( (rk[l] < rk[n - r + 1]) ? (a[l++]) : (a[r--]) ) + 'A' - 1;
    }
    for (int i = 1; i <= N; ++i){
        printf("%c", ans[i]);
        if (i % 80 == 0) printf("\n");
    }
    //system("pause");
}

/*
6
A
C
D
B
C
B
*/
        
