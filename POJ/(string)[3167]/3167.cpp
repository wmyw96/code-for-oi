#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 200001;
int n, m, s, ansn;
int a[MAX_N], b[MAX_N], p[MAX_N], ans[MAX_N];

struct listg{
       int lt[26], rt[26];
       int query(int l, int r, int num){
           int ret = 0;
           for (int i = 1; i <= num; ++i){
               if ((lt[i] >= l && lt[i] <= r) || (rt[i] >= l && rt[i] <= r))
                  ret++;
               else if (i == num) ret++;
           }
           int rmx = 0; 
           for (int i = num; i <= s; ++i){
               if ((lt[i] >= l && lt[i] <= r) || (rt[i] >= l && rt[i] <= r))
                  rmx++;
               else if (i == num) rmx++;
           }
           return ret * 100 + rmx;
       }
       int insert(int i, int num){
           if (lt[num] == 0) lt[num] = rt[num] = i;
           else rt[num] = max(rt[num], i);
       }
};
listg qb, qa;
       
int main(){
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i) scanf("%d", &b[i]);
    
    int j = 0;
    p[1] = 0;
    qb.insert(1, b[1]);
    for (int i = 2; i <= m; ++i){
        qb.insert(i, b[i]);
        while (j > 0 && qb.query(1, j, b[j + 1]) != qb.query(i - j, i - 1, b[i])) j = p[j];
        if (qb.query(1, j, b[j + 1]) == qb.query(i - j, i - 1, b[i])) ++j;
        p[i] = j;
        //printf("- %d\n", p[i]);
    }
    j = 0;
    for (int i = 1; i <= n; ++i){
        qa.insert(i, a[i]);
        
        while (j > 0 && qb.query(1, j, b[j + 1]) != qa.query(i - j, i - 1, a[i])) j = p[j];
        //printf("+ %d\n", j);
        if (qb.query(1, j, b[j + 1]) == qa.query(i - j, i - 1, a[i])) ++j;
        if (j == m){
           ans[++ansn] = i;
           j = p[j];
        } 
    }
    printf("%d\n", ansn);
    for (int i = 1; i <= ansn; ++i) printf("%d\n", ans[i] - m + 1);
    //system("pause");
}

