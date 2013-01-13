/************************************************************** 
    Problem: 1028 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:572 ms 
    Memory:1332 kb 
****************************************************************/
  
#include<iostream>  
#include<cstdio>  
#include<cmath> 
#include<cstdlib>  
#include<cstring>  
#include<algorithm>  
using namespace std; 
const int MAX_N=5001; 
     
int n,m;  
int a[MAX_N];  
int b[MAX_N];  
int ans[MAX_N];  
int ansn; 
  
int check(int x,int mm){      
       
    for (int i=1;i<=n;i++){  
        b[i]%=3; 
        if (!b[i]) continue; 
        if (i+2<=n){ 
            if (b[i+1]>=b[i]) b[i+1]-=b[i]; else return 0; 
            if (b[i+2]>=b[i]) b[i+2]-=b[i]; else return 0; 
            b[i]=0; 
        } 
        else return 0; 
    }     
    return 1;  
}  
     
int check(int x){ 
    for (int i=1;i<=n;i++){     
        for (int j=1;j<=n;j++) b[j]=a[j];  
        b[x]++; 
        if (b[i]>=2){ 
           b[i]-=2; 
           if (check(x,i)) return 1; 
        } 
           
    } 
    return 0; 
} 
  
int main(){  
    scanf("%d%d",&n,&m);  
    m=m*3+1; 
    for (int i=1;i<=m;i++){  
        int x; 
        scanf("%d",&x); 
        a[x]++; 
    }  
    for (int i=1;i<=n;i++){  
        if (check(i))  
            ans[++ansn]=i;  
    }  
    if (ansn>0){ 
       for (int i=1;i<ansn;i++)  
           printf("%d ",ans[i]);  
       printf("%d\n",ans[ansn]);  
    } 
    else printf("NO\n"); 
} 
/* 
  
Metion: 
    (1) 贪心的方法：及时贪心 
    (2) 注意及时减少复杂度的囧(数据离散化减少复杂度) 
    (3) 一个int的函数必须要有返回的值  
*/

