#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stuck_empty(int ele_num);
int stuck_peek(int* stuck,int ele_num);
int stuck_pop(int* stuck,int* ele_num);
int stuck_push(int* stuck,int* ele_num,int value);
int stuck_size(int ele_num);
int cue_add(int* stuck1,int* stuck2,int* ele_num1,int* ele_num2,int value);
int cue_peek(int* stuck2,int ele_num2);
int cue_remove(int* stuck1,int* stuck2,int* ele_num1,int* ele_num2);
int cue_size(int ele_num1);

int main(void ){

	int stuck[1000];
	int ele_num=0;
	int cue_st1[1000];//まるでスタックの如し
	int cue_st2[1000];//こっちがメイン
	int cue_en1=0;
	int cue_en2=0;

//スタックのデモ
	printf("★★スタック★★\n");
	printf("%d\n",stuck_empty(ele_num));
	printf("%d\n",stuck_push(stuck,&ele_num,1));
	printf("%d\n",stuck_empty(ele_num));
	printf("%d\n",stuck_push(stuck,&ele_num,2));
	printf("%d\n",stuck_push(stuck,&ele_num,3));
	printf("%d\n",stuck_push(stuck,&ele_num,4));
	printf("%d\n",stuck_peek(stuck,ele_num));
	printf("%d\n",stuck_pop(stuck,&ele_num));
	printf("%d\n",stuck_pop(stuck,&ele_num));
	printf("%d\n",stuck_pop(stuck,&ele_num));
	printf("%d\n",stuck_size(ele_num));
//キューのデモ
	printf("★★キュー★★\n");
	printf("cue_size(cue_en2)");
	printf("%d\n",cue_size(cue_en2));
	printf("cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,1)");
	printf("%d\n",cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,1));
	printf("cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,2)");
	printf("%d\n",cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,2));
	printf("cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,3)");
	printf("%d\n",cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,3));
	printf("cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,4)");
	printf("%d\n",cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,4));
	printf("cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,5)");
	printf("%d\n",cue_add(cue_st1,cue_st2,&cue_en1,&cue_en2,5));
	printf("cue_size(cue_en2)");
	printf("%d\n",cue_size(cue_en2));//5
	printf("cue_peek(cue_st2,cue_en2)");
	printf("%d\n",cue_peek(cue_st2,cue_en2));//1
	printf("cue_remove(cue_st1,cue_st2,&cue_en1,&cue_en2)");
	printf("%d\n",cue_remove(cue_st1,cue_st2,&cue_en1,&cue_en2));//1
	printf("cue_size(cue_en2)");
	printf("%d\n",cue_size(cue_en2));//4
	printf("cue_peek(cue_st2,cue_en2)");
	printf("%d\n",cue_peek(cue_st2,cue_en2));//2
	printf("cue_remove(cue_st1,cue_st2,&cue_en1,&cue_en2)");
	printf("%d\n",cue_remove(cue_st1,cue_st2,&cue_en1,&cue_en2));//2
	printf("cue_size(cue_en2)");
	printf("%d\n",cue_size(cue_en2));//3
	printf("cue_peek(cue_st2,cue_en2)");
	printf("%d\n",cue_peek(cue_st2,cue_en2));//3
	printf("cue_size(cue_en2)");
	printf("%d\n",cue_size(cue_en2));//3

/*	do{
		int command;
		printf("指示をどうぞ\n");
		printf("1:キューに値を追加\n");
		printf("2:キューの先頭要素を確認\n");
		printf("3:キューの先頭要素を削除\n");
		printf("4:キューの要素を先頭から順にすべて表示\n");
		printf("それ以外:やめる");
		scanf("%d",&command);
		switch(command){
		case 1:

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}

	}while();*/

	getchar();

	return 0;
}

int stuck_empty(int ele_num){
	if(ele_num){
		return 0;
	}
	return 1;
}

int stuck_peek(int* stuck,int ele_num){
	if(ele_num){
		return stuck[0];
	}
	printf("スタックが空です．\n");
	return -1;
}

int stuck_pop(int* stuck,int* ele_num){
	if(*ele_num){
		int return_num=stuck[0];
		int i;
		for(i=0;i<*ele_num-1;i++){
			stuck[i]=stuck[i+1];
		}
		(*ele_num)--;
		return return_num;
	}
	printf("スタックが空です．\n");
	return -1;
}

int stuck_push(int* stuck,int* ele_num,int value){
	int i;
	for(i=*ele_num;i>0;i--){
		stuck[i]=stuck[i-1];
	}
	stuck[0]=value;
	(*ele_num)++;
	return value;
}

int stuck_size(int ele_num){
	return ele_num;
}

int cue_add(int* stuck1,int* stuck2,int* ele_num1,int* ele_num2,int value){
	int i;
	stuck_push(stuck1,ele_num1,value);
	(*ele_num2)=0;
	for(i=0;i<*ele_num1;i++){
		stuck_push(stuck2,ele_num2,stuck1[i]);
	}

	return value;
}

int cue_peek(int* stuck2,int ele_num2){
	return stuck_peek(stuck2,ele_num2);
}

int cue_remove(int* stuck1,int* stuck2,int* ele_num1,int* ele_num2){
	int i;
	int ret_num=stuck1[*ele_num1-1];
	(*ele_num1)--;
	(*ele_num2)=0;
	for(i=0;i<*ele_num1;i++){
		stuck_push(stuck2,ele_num2,stuck1[i]);
	}
	return ret_num;
}

int cue_size(int ele_num1){
	return ele_num1;
}

