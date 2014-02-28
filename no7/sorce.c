#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define K_NUM (10)//隕石の個数
#define N_NUM (10)//盤の大きさ

///名古屋大学大学院　工学研究科　計算理工学専攻　伊木一真

typedef struct{
	int x;
	int y;
}Pos;

int meteor_X_huriwake(Pos* pos);
int IsAinB(int A[N_NUM],int A_size,int B[N_NUM],int B_size);
int active_eraser(int same_x_group_ele_num[N_NUM],int active_group[N_NUM],int x_shurui,int hougansuru_mono[N_NUM]);
int iranaimono_excluder(int same_x_group[N_NUM][N_NUM],int same_x_group_ele_num[N_NUM],int active_group[N_NUM],int sansho,int x_shurui);

int main(void){

	int i;
	int j;
	int x_shurui;
	Pos pos[K_NUM];
	Pos kouho[N_NUM*N_NUM];
	static int same_x_group[N_NUM][N_NUM];
	int same_x_group_ele_num[N_NUM];
	int active_group[N_NUM];
	int pre_x=-1;
	int current_x_shurui_num=-1;
	int hitsuyo=0;
	char arrai[N_NUM][N_NUM];

	srand((unsigned)time(NULL));

	//m個の隕石の座標を(x1,y1),…(xm,ym)とする．
	//この時，x,yそれぞれの座標が，全ての要素番号において異なる時
	//この隕石のグループをバラバラなグループと命名する．
	//隕石群の中の最も大きなバラバラなグループがm個である場合
	//m回のレーザーで

	for(i=0;i<N_NUM;i++){
		for(j=0;j<N_NUM;j++){//隕石の位置の候補を埋める．
			kouho[i*N_NUM+j].x=i;
			kouho[i*N_NUM+j].y=j;
			arrai[i][j]='X';
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
	}//そしてその位置の候補をシャッフルする．盤が大きいほどシャッフル回数は増える．
	for(i=0;i<K_NUM;i++){//そしてシャッフルした位置の候補を先頭から隕石の位置として代入していく．
		pos[i]=kouho[i];
	}


	x_shurui=meteor_X_huriwake(pos);//隕石をX座標でソートして，揃える．そしてX座標の種類数を格納．

	for(i=0;i<K_NUM;i++){
		printf("隕石%2d個目(%d,%d)\n",i+1,pos[i].x,pos[i].y);
		arrai[pos[i].y][pos[i].x]='O';
	}//隕石の位置を表示．
	for(i=0;i<N_NUM;i++){
		for(j=0;j<N_NUM;j++){
			if(arrai[i][j]=='O'){
				printf("●");
			}else{
				printf("○");
			}
		}
		printf("\n");
	}//分かりやすく表示．

	//これで，隕石の位置は同一のx座標を持つものごとにグループ分けされた．
	//そのx座標を，0番目のx座標，1番目のx座標…と呼ぶことにする．
	//そして，各グループのy座標の値をそれぞれまとめておく．
	for(i=0;i<K_NUM;i++){
		if(pre_x!=pos[i].x){
			current_x_shurui_num++;
		}
		//same_x_groupの一階層目の要素番号は，そのグループが何種類目のX座標を持つもの同士集まっているかを格納する．
		//二階層目にそのX座標を持つ隕石のy座標を格納していく．
		//same_x_group_ele_numのA番目には，A番目のX座標を持つ隕石がいくつあるかが最終的に格納される．
		same_x_group[current_x_shurui_num][same_x_group_ele_num[current_x_shurui_num]]=pos[i].y;
		same_x_group_ele_num[current_x_shurui_num]++;
		pre_x=pos[i].x;
	}
	for(i=0;i<x_shurui;i++){
		active_group[i]=1;
	}//そして，各グループにアクティブ性という変数を用意する．それを一つの配列で表す．
	//active_groupのA番目が1であればA番目のX座標を持つもので集まったグループはアクティブであることを意味する．

	//これでy座標のグループが出来上がった．
	//後は，このグループを順に参照し，それぞれにおいて
	//それに包含されるグループを探し，そのグループ数が，参照グループの要素数を上回っている場合
	//最も要素数の少ないグループから順に外していく．
	//最後まで残ったグループの個数が必要なレーザーの発射回数になる．

	for(i=0;i<x_shurui;i++){
		for(j=0;j<x_shurui;j++){
			if(active_group[i]){
				iranaimono_excluder(same_x_group,same_x_group_ele_num,active_group,i,x_shurui);
			}
		}
	}
	
	for(i=0;i<x_shurui;i++){
		if(active_group[i]){
			hitsuyo++;
		}
	}
	printf("必要なレーザ発射回数は%d回です\n",hitsuyo);
	getchar();

	return 0;
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

int iranaimono_excluder(int same_x_group[N_NUM][N_NUM],int same_x_group_ele_num[N_NUM],int active_group[N_NUM],int sansho,int x_shurui){

	int hougansurumono[N_NUM];//sansho番目のグループが包含するグループであればその要素数を，そうでなければ0を格納．
	int hougansuru_num=0;
	int i;
	if(active_group[sansho]==0){
		return 0;
	}

	for(i=0;i<x_shurui;i++){
		if(active_group[i]==0){
			continue;
		}
		if(i==sansho){
			hougansurumono[i]=0;
		}else{
			if(IsAinB(same_x_group[i],same_x_group_ele_num[i],same_x_group[sansho],same_x_group_ele_num[sansho])){
				hougansurumono[i]=1;
				hougansuru_num++;
			}else{
				hougansurumono[i]=0;
			}
		}
	}
	if((hougansuru_num+1)>same_x_group_ele_num[sansho]){//包含するグループと自身を合わせたグループ個数が自身の要素数を上回っている場合
		//その差分の数だけ要素数の少ないグループから消していく（active_groupの対応要素番目を0にする）．順番は気にしない．
		for(i=0;i<(hougansuru_num+1)-same_x_group_ele_num[sansho];i++){
			active_eraser(same_x_group_ele_num,active_group,x_shurui,hougansurumono);
		}
	}
	return 0;
}

int IsAinB(int A[N_NUM],int A_size,int B[N_NUM],int B_size){
	//集合AがBに含まれていれば，1を返す．そうでない場合は0を返す．
	int i;
	int j;
	if(A_size>B_size){
		return 0;
	}
	
	for(i=0;i<A_size;i++){
		int atta_flag=0;
		for(j=0;j<B_size;j++){
			if(A[i]==B[j]){
				atta_flag=1;
				break;
			}
		}
		if(!atta_flag){
			return 0;
		}
	}



	return 1;
}

int active_eraser(int same_x_group_ele_num[N_NUM],int active_group[N_NUM],int x_shurui,int hougansuru_mono[N_NUM]){

	//最も要素数の少ないグループのアクティブ性をオフにする．

	int i;
	int current_yousosu=N_NUM+1;
	int current_target=-1;

	for(i=0;i<x_shurui;i++){
		if(hougansuru_mono[i]&&(current_yousosu>same_x_group_ele_num[i])){
			current_yousosu=same_x_group_ele_num[i];
			current_target=i;
		}
	}

	if(current_target!=-1){
		active_group[current_target]=0;
	}
	return 0;
}