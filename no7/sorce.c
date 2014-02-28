#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define K_NUM (10)
#define N_NUM (10)

typedef struct{
	int x;
	int y;
}Pos;

int meteor_X_huriwake(Pos* pos);

int main(void){

	int i;
	int j;
	int x_shurui;
	Pos pos[K_NUM];
	Pos kouho[N_NUM*N_NUM];
	static int same_x_group[N_NUM][N_NUM];
	int same_x_group_ele_num[N_NUM];
	int pre_x=-1;
	int current_x_shurui_num=-1;

	srand((unsigned)time(NULL));

	for(i=0;i<N_NUM;i++){
		for(j=0;j<N_NUM;j++){
			kouho[i*N_NUM+j].x=i;
			kouho[i*N_NUM+j].y=j;
		}
		same_x_group_ele_num[i]=0;
	}
	for(i=0;i<N_NUM*N_NUM*4;i++){
		int randi=rand()%(N_NUM*N_NUM);
		int randj=rand()%(N_NUM*N_NUM);
		Pos temp;
		temp.x=kouho[randi].x;        temp.y=kouho[randi].y;
		kouho[randi].x=kouho[randj].x;kouho[randi].y=kouho[randj].y;
		kouho[randj].x=temp.x;    kouho[randj].y=temp.y;
	}
	for(i=0;i<K_NUM;i++){
		pos[i]=kouho[i];
	}

	x_shurui=meteor_X_huriwake(pos);

	//これで，隕石の位置はx座標ごとにグループ分けされた．
	for(i=0;i<K_NUM;i++){
		if(pre_x!=pos[i].x){
			current_x_shurui_num++;
		}
		same_x_group[current_x_shurui_num][]

		pre_x=pos[i].x;
	}
}

int meteor_X_huriwake(Pos* pos){

	int i;
	int j;
	int x_shurui=0;
	int pre_x=-1;

	for(i=0;i<K_NUM-1;i++){
		for(j=i+1;j<K_NUM;j++){
			if(pos[i].x>pos[j].x){
				Pos temp;
				  temp.x=pos[i].x;  temp.y=pos[i].y;
				pos[i].x=pos[j].x;pos[i].y=pos[j].y;
				  pos[j].x=temp.x;  pos[j].y=temp.y;
			}
		}
	}
	for(i=0;i<K_NUM;i++){
		if(pos[i].x!=pre_x){
			x_shurui++;
		}
		pre_x=pos[i].x;
	}
	return x_shurui;
}

