#include <stdio.h>
int main(){
	int temp;
	int a[10]={1,2,3,4,5,6,7,8,9.10};
	for(int i = 0; i < 10 ;i++){
		for(int j=0;j<10-i;j++){
			if(a[j] < a[j+1]){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	for(int i = 0 ; i< 10; i++){
		printf("%d\n",a[i]);
	}
}
