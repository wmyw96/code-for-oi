#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
using namespace std;

int main(){
	freopen("3415.in", "w", stdout);
	srand(time(0));
	/*int n = 10;
	int m = 10;
	int T = 10;
	while (T--){
		printf("%d\n", rand() % 5 + 1);
		for (int i = 1; i <= n; ++i) printf("%c", rand() % 2 + 'a'); printf("\n");
		for (int i = 1; i <= m; ++i) printf("%c", rand() % 2 + 'a'); printf("\n");
	}*/

	int T = 6;
	while (T--){	
		int n = rand() + 60000;
		int m = rand() + 60000;
		printf("%d\n", rand() % 5 + 1);
		for (int i = 1; i <= n; ++i) printf("%c", 'a'); printf("\n");
		for (int i = 1; i <= m; ++i) printf("%c", 'a'); printf("\n");
	}
	printf("0\n");
} 
