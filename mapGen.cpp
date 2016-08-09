#include<iostream>
#include<cstdlib>
#define LEN 20
#define WID 20


int main(){
	int a[101][101] = {0};
	srand (time(NULL));
	for(int i = 1 ;i< LEN*WID/2;i++) {
	a[(rand()*(i+1))%LEN][(rand()*(i+1))%WID] = -1;
	}
	for(int i =0;i<LEN;i++){
		for(int j =0;j<WID;j++){
			std::cout.width(3);std::cout << a[i][j];}
		std::cout << std::endl;
	}
	return 0;
}
