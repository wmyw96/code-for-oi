#include <stdio.h>

#define Appear(x) \
       app[x+1000000]

bool app[2000001];
int repeat[200001];              // 以k为结尾的串中，出现重复数字的位置
int perfect[200001];              // 以k为结尾的perfect串长度
int profit[200001];              // 第k个公司的营业额

inline int mmax(int a, int b) {
       return a>b?a:b;
}

inline int mmin(int a, int b) {
       return a<b?a:b;
}

int main() {
       int N, M;
       int L, R;
       int i, k;
       scanf("%d %d", &N, &M);
       for(i=0; i<N; i++) {
              scanf("%d", profit+i);
       }

       // 约定Pk为以k为结尾的最长perfect串
       // 当前perfect串中出现的数，在app[]中对应位置为true
       perfect[0] = 1;
       repeat[0] = 0;
       Appear(profit[0]) = true;

       for(k=1; k<N; k++) {
              // 如果第k个数在Pk-1中未出现，将第k个数加入Pk-1仍然是个perfect串，那么|Pk| = |Pk-1|+1
              if( !Appear(profit[k]) ) {
                     Appear(profit[k]) = true;
                     perfect[k] = perfect[k-1]+1;
                     repeat[k] = repeat[k-1];       // repeat值和Pk-1相同
              }
              // 否则，从Pk-1开头开始找，一直找到和第k个数相同的那个数，截掉前面的那一段
              else {
                     i = k-perfect[k-1];
                     while( profit[i] != profit[k] ) {
                            Appear(profit[i]) = false;
                            i ++;
                     }
                     perfect[k] = k-i;                     // 新的串长度
                     repeat[k] = k;                            // repeat值为自己
              }
       }

       int ret;
       for(k=0; k<M; k++) {
              ret = 0;
              scanf("%d %d", &L, &R);
              while( 1 ) {
                     // 结果大于当前范围，可提前退出
                     if( R-L+1 <= ret ) {
                            break;
                     }
                     ret = mmax(ret, mmin(perfect[R], R-L+1));

                     // |P(repeat[R])| < |P(repeat[R]+1)| < ... < |P(R)|, 所以直接跳到P(repeat[R]-1)处
                     R = repeat[R]-1;
              }
              printf("%d\n", ret);
       }

       return 1;
}
