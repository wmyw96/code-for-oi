#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
typedef long long LL;
const LL MOD = 19940417;
LL n, m;
LL ans, ansm;
 
LL calc(LL i){
   if (i == 0) return 0;
   LL x = i;
   LL y = i + 1;
   LL z = 2 * i + 1;
   LL xx = x, yy = y, zz = z;
   if (x % 2 == 0) xx /= 2; else yy /= 2;
   if (x % 3 == 0) xx /= 3; 
      else if (x % 3 == 1) zz /= 3;
           else yy /= 3;
   return (xx * yy % MOD * zz % MOD);
}
 
LL abs1(LL x){
   if (x > 0) return x; else return MOD + x;
}
 
int main(){     
    cin >> n >> m;
    if (n > m) swap(n, m);
    LL ansm = (LL)(m) * (m) % MOD;
    for (LL i = 1; i <= m;){
        LL p = m / i;
        LL ii = m / p;
        ansm -= ((i + ii) * (ii - i + 1) / 2 * p) % MOD;
        if (ansm < 0) ansm += MOD;
        i = ii + 1;
    }
    LL ans = (LL)(n) * (n) % MOD * ansm % MOD;
    for (LL i = 1; i <= n;){
        LL p = n / i;
        LL ii = n / p;
        ans -= ((i + ii) * (ii - i + 1) / 2 * p % MOD * ansm) % MOD;
        if (ans < 0) ans += MOD;
        i = ii + 1;
    }  
    LL s = min(n, m);
     
    LL ans1 = 0;
    ans1 = (LL)s % MOD * n % MOD * m % MOD;
    LL ans5 = (LL)s % MOD * n % MOD * m % MOD;
    for (LL i = 1; i <= s;){
        LL p = n / i;
        LL ii = n / p;
        ii = min(ii, s);
        ans1 -= (((ii + i) * (ii - i + 1) / 2) % MOD * p % MOD * (LL)m) % MOD;
        if (ans1 < 0) ans1 += MOD;
        ans1 %= MOD;
        i = ii + 1;
    }
     
    for (LL i = 1; i <= s;){
        LL p = m / i;
        LL ii = m / p;
        ii = min(ii, s);
        ans1 -= (((ii + i) * (ii - i + 1) / 2) % MOD * p % MOD * (LL)n) % MOD;
        if (ans1 < 0) ans1 += MOD;
        ans1 %= MOD;
        i = ii + 1;
    }    
     
    for (LL i = 1; i <= s; ){
        LL pn = n / i, pm = m / i;
        LL in = n / pn, im = m / pm;
        LL ii = min(min(in, im), (LL)s);
        ans1 += ((LL)abs1(calc(ii) - calc(i - 1)) % MOD * pn % MOD * pm) % MOD;
        ans1 %= MOD;
        i = ii + 1;
    }    
     
    ans -= ans1;
    if (ans < 0) ans += MOD;
     
    cout<<ans<<endl;
}
