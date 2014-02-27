#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void ){

	char mojiretsu[32];
	int mojisu=7;
	int i;
	int j;

	strcpy(mojiretsu,"ABCDEFG");

	for(i=1;i<mojisu;i++){
		for(j=0;j<i;j++){
			if(mojiretsu[j]==mojiretsu[i]){
				printf("true\n");
				return 0;
			}
		}
	}

	printf("false\n");

	return 0;
}