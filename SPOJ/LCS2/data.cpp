#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){
	freopen("LCS.in","w",stdout);
	srand(time(0));
	for (int z = 1; z <= 6; ++z){
	for (int i = 1;i <= 90000 +rand()%1000;i++){
		char ch = rand() % 3 + 'a';
		//for (int j = 1; j <= rand() % 10 + 1; ++j) 
			printf("%c",ch);
	}
	printf("\n");
	}
}
