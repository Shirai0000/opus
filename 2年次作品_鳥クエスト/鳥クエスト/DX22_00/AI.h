#pragma once
#include "Cho.h"
#define KETA (10)   //�L������
#define AIR  (5)   //�GAI���a


class AI
{
protected:
	float Xpos;           //���݂̍��W
	float Ypos;           //���݂̍��W
	int HP;               //HP
	float speed;          //�ړ����x  1�����������ŗ]�肪�łȂ�����
	float destinationX;   //�s����W
	float destinationY;   //�s����W
	float targetX;        //�^�[�Q�b�g���W(�v���C���[�A㩁A�{���n)
	float targetY;        //�^�[�Q�b�g���W(�v���C���[�A㩁A�{���n)
public:
	AI(void);
	virtual void Update();
	void Setpos(float _x, float _y);   //AI�̍��̍��W��ݒ�
	void SetTarget(float _x,float _y);              //�^�[�Q�b�g�̍��W��ݒ�
	void SetHP(int _hp);                           //HP��ݒ�


	////////�ŒZ���[�g�𔭌����邽�߂̊֐�///////////////////
	void show_openlist(CI *A, CI *B);
	virtual void saitan(int map[MAPX][MAPY], float * _x, float *_y);      //�ŒZ���[�g�𔭌�
	void delet(CI*LX, CI*LY, CI *A, CI *B);                       //�ŒZ���[�g�ɕK�v�Ȃ����W��r��
	void footprints(CI *A, CI *B);
	virtual void HrzSearch(int nowX, int nowY, CI *Z, CI *W, CI *X, CI *Y);
	void footdelete(CI *A, CI *B);
	void SetMapflag();             //�}�b�v�t���O��������
	//////////////////////////////////////////////////////////
};






