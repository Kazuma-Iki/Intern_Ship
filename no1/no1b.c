#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	char retsu1[256];
	char retsu2[256];
	int mojisu1;
	int mojisu2;
	int i;
	int j;

	strcpy(retsu1,"KAZUMAIKI"); mojisu1=9;
	strcpy(retsu2,"UMAI");      mojisu2=4;

	for(i=0;i<mojisu1-(mojisu2-1);i++){
		if(retsu1[i]==retsu2[0]){
			int flag=1;
			for(j=1;j<mojisu2;j++){
				if(retsu1[i+j]==retsu2[j]){
				}else{
					flag=0;
					break;
				}
			}
			if(flag){
				printf("true\n");
				return 0;
			}
		}
	}


	printf("false\n");

	return 0;
}