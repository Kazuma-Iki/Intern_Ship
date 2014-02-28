#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define K_NUM (10)//覐΂̌�
#define N_NUM (10)//�Ղ̑傫��

///���É���w��w�@�@�H�w�����ȁ@�v�Z���H�w��U�@�ɖ؈�^

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

	//m��覐΂̍��W��(x1,y1),�c(xm,ym)�Ƃ���D
	//���̎��Cx,y���ꂼ��̍��W���C�S�Ă̗v�f�ԍ��ɂ����ĈقȂ鎞
	//����覐΂̃O���[�v���o���o���ȃO���[�v�Ɩ�������D
	//覐ΌQ�̒��̍ł��傫�ȃo���o���ȃO���[�v��m�ł���ꍇ
	//m��̃��[�U�[��

	for(i=0;i<N_NUM;i++){
		for(j=0;j<N_NUM;j++){//覐΂̈ʒu�̌��𖄂߂�D
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
	}//�����Ă��̈ʒu�̌����V���b�t������D�Ղ��傫���قǃV���b�t���񐔂͑�����D
	for(i=0;i<K_NUM;i++){//�����ăV���b�t�������ʒu�̌���擪����覐΂̈ʒu�Ƃ��đ�����Ă����D
		pos[i]=kouho[i];
	}


	x_shurui=meteor_X_huriwake(pos);//覐΂�X���W�Ń\�[�g���āC������D������X���W�̎�ސ����i�[�D

	for(i=0;i<K_NUM;i++){
		printf("覐�%2d��(%d,%d)\n",i+1,pos[i].x,pos[i].y);
		arrai[pos[i].y][pos[i].x]='O';
	}//覐΂̈ʒu��\���D
	for(i=0;i<N_NUM;i++){
		for(j=0;j<N_NUM;j++){
			if(arrai[i][j]=='O'){
				printf("��");
			}else{
				printf("��");
			}
		}
		printf("\n");
	}//������₷���\���D

	//����ŁC覐΂̈ʒu�͓����x���W�������̂��ƂɃO���[�v�������ꂽ�D
	//����x���W���C0�Ԗڂ�x���W�C1�Ԗڂ�x���W�c�ƌĂԂ��Ƃɂ���D
	//�����āC�e�O���[�v��y���W�̒l�����ꂼ��܂Ƃ߂Ă����D
	for(i=0;i<K_NUM;i++){
		if(pre_x!=pos[i].x){
			current_x_shurui_num++;
		}
		//same_x_group�̈�K�w�ڂ̗v�f�ԍ��́C���̃O���[�v������ޖڂ�X���W�������̓��m�W�܂��Ă��邩���i�[����D
		//��K�w�ڂɂ���X���W������覐΂�y���W���i�[���Ă����D
		//same_x_group_ele_num��A�Ԗڂɂ́CA�Ԗڂ�X���W������覐΂��������邩���ŏI�I�Ɋi�[�����D
		same_x_group[current_x_shurui_num][same_x_group_ele_num[current_x_shurui_num]]=pos[i].y;
		same_x_group_ele_num[current_x_shurui_num]++;
		pre_x=pos[i].x;
	}
	for(i=0;i<x_shurui;i++){
		active_group[i]=1;
	}//�����āC�e�O���[�v�ɃA�N�e�B�u���Ƃ����ϐ���p�ӂ���D�������̔z��ŕ\���D
	//active_group��A�Ԗڂ�1�ł����A�Ԗڂ�X���W�������̂ŏW�܂����O���[�v�̓A�N�e�B�u�ł��邱�Ƃ��Ӗ�����D

	//�����y���W�̃O���[�v���o���オ�����D
	//��́C���̃O���[�v�����ɎQ�Ƃ��C���ꂼ��ɂ�����
	//����ɕ�܂����O���[�v��T���C���̃O���[�v�����C�Q�ƃO���[�v�̗v�f���������Ă���ꍇ
	//�ł��v�f���̏��Ȃ��O���[�v���珇�ɊO���Ă����D
	//�Ō�܂Ŏc�����O���[�v�̌����K�v�ȃ��[�U�[�̔��ˉ񐔂ɂȂ�D

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
	printf("�K�v�ȃ��[�U���ˉ񐔂�%d��ł�\n",hitsuyo);
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

	int hougansurumono[N_NUM];//sansho�Ԗڂ̃O���[�v����܂���O���[�v�ł���΂��̗v�f�����C�����łȂ����0���i�[�D
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
	if((hougansuru_num+1)>same_x_group_ele_num[sansho]){//��܂���O���[�v�Ǝ��g�����킹���O���[�v�������g�̗v�f���������Ă���ꍇ
		//���̍����̐������v�f���̏��Ȃ��O���[�v��������Ă����iactive_group�̑Ή��v�f�Ԗڂ�0�ɂ���j�D���Ԃ͋C�ɂ��Ȃ��D
		for(i=0;i<(hougansuru_num+1)-same_x_group_ele_num[sansho];i++){
			active_eraser(same_x_group_ele_num,active_group,x_shurui,hougansurumono);
		}
	}
	return 0;
}

int IsAinB(int A[N_NUM],int A_size,int B[N_NUM],int B_size){
	//�W��A��B�Ɋ܂܂�Ă���΁C1��Ԃ��D�����łȂ��ꍇ��0��Ԃ��D
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

	//�ł��v�f���̏��Ȃ��O���[�v�̃A�N�e�B�u�����I�t�ɂ���D

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