#include "AI.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;



AI::AI(void)
{
	this->Setpos(1,1);
	this->destinationX = 1;
	this->destinationY = 1;
	this->speed = 0.5f;
	this->targetX = 5;
	this->targetY = 8;
}

void AI::Update(void)
{
	//�덷�C��
	if ((int)(this->Xpos * 100) % 10 > 8)
	{
		this->Xpos += 0.1;
		this->Xpos -= 0.09;
	}
	//�덷�C��
	if ((int)(this->Ypos * 100) % 10 > 8)
	{
		this->Ypos += 0.1;
		this->Ypos -= 0.09;
	}

	if (((int)(this->destinationX*KETA) == (int)(this->Xpos*KETA)) && ((int)(this->destinationY*KETA) == (int)(this->Ypos*KETA)))
	{
		for (int len = 0; len < MAPX; len++)
		{
			for (int sen = 0; sen < MAPY; sen++)
			{
				if (CI::map[len][sen] == 3)
				{
					CI::map[len][sen] = 0;
				}
			}
		}
		if (((int)(this->destinationX*KETA) == (int)(this->targetX*KETA)) && ((int)(this->destinationY*KETA) == (int)(this->targetY*KETA)))
		{
			do{
				this->targetX = rand() % 10;
				this->targetY = rand() % 10;
			}
			while (CI::map[(int)this->targetX][(int)this->targetY] == 1);
		}
		CI::map[(int)this->Xpos][(int)this->Ypos] = 3;
		CI::map[(int)this->targetX][(int)this->targetY] = 5;
		this->saitan(CI::map, &this->destinationX, &this->destinationY);
	}
	if ((int)(this->Xpos*KETA) > (int)(this->destinationX*KETA))
	{
		this->Xpos -= this->speed;
	}
	if ((int)(this->Xpos*KETA) < (int)(this->destinationX*KETA))
	{
		this->Xpos += this->speed;
	}
	if ((int)(this->Ypos*KETA) > (int)(this->destinationY*KETA))
	{
		this->Ypos -= this->speed;
	}
	if ((int)(this->Ypos*KETA) < (int)(this->destinationY*KETA))
	{
		this->Ypos += this->speed;
	}
	
}

//���̍��W��ݒ�
void AI::Setpos(float _x, float  _y)
{
	this->Xpos = _x;
	this->Ypos = _y;
}


//�s���Ă��Ȃ����s���邱�Ƃ��킩���Ă��铹��\��
void AI::show_openlist(CI * A, CI * B)
{
	//cout << endl;
	//cout << "nopenlist:";
	for (int i = A->head; i <= A->tail; i++) {
		//printf("%d,%d    ", A.queue[i],B.queue[i]);
		//cout << A->queue[i] << "," << B->queue[i] << "  ";
	}
	//cout << endl << endl;
}


//�ŒZ���[�g�����
void AI::saitan(int map[MAPX][MAPY],float *_x,float *_y)
{
	////������//////////
	AI a;
	CI X;
	CI Y;
	CI Z;
	CI W;
	CI LX;
	CI LY;
	////////////////////

	int suu = 0;
	SetMapflag();   //�}�b�v�t���O�̒l��������
	suu++;
	//cout << "Search" << suu << endl;  //�T�[�`��
	HrzSearch((int)this->Xpos, (int)this->Ypos, &Z, &W, &X, &Y);               //�T��(�����ʒu)
	a.show_openlist(&X, &Y);           //�s���Ă��Ȃ����s���邱�Ƃ��킩���Ă��铹��\��

	do {
		suu++;
		//cout << "Search" << suu << endl;  //�T�[�`��
		HrzSearch(X.dequeue(), Y.dequeue(), &Z, &W, &X, &Y);
		a.show_openlist(&X, &Y);

	} while (!(CI::flag[(int)this->targetX][(int)this->targetY] == 1));

	delet(&LX, &LY, &Z, &W);              //����Ȃ����[�g���폜
	footprints(&LX, &LY);       //�ŒZ���[�g��\��
	*_x = (float)LX.queue[1];
	*_y = (float)LY.queue[1];
	//footprints(&Z, &W);

}


//�ŒZ���[�g�ɕK�v�Ȃ����W���폜
void AI::delet(CI * LX, CI * LY, CI * A, CI * B)
{
	LX->tail = 0;
	LY->tail = 0;
	LX->queue[LX->tail] = this->targetX;
	LY->queue[LY->tail] = this->targetY;
	LX->tail++;
	LY->tail++;
	LX->queue[LX->tail] = A->queue[A->tail];
	LY->queue[LY->tail] = B->queue[B->tail];
	for (int len = A->tail; len != 0; len--)
	{
		
				if ((LX->queue[LX->tail] - 1 == A->queue[len - 1]) || (LX->queue[LX->tail] + 1 == A->queue[len - 1]) || (LY->queue[LY->tail] + 1 == B->queue[len - 1]) || (LY->queue[LY->tail] - 1 == B->queue[len - 1]))
				{
					if (((LX->queue[LX->tail] - 1 == A->queue[len - 1]) || (LX->queue[LX->tail] + 1 == A->queue[len - 1])) && (LY->queue[LY->tail] == B->queue[len - 1]))
					{
						LX->tail++;
						LY->tail++;
						LX->queue[LX->tail] = A->queue[len - 1];
						LY->queue[LY->tail] = B->queue[len - 1];
					}
					if ((LX->queue[LX->tail] == A->queue[len - 1]) && ((LY->queue[LY->tail] + 1 == B->queue[len - 1]) || (LY->queue[LY->tail] - 1 == B->queue[len - 1])))
					{
						LX->tail++;
						LY->tail++;
						LX->queue[LX->tail] = A->queue[len - 1];
						LY->queue[LY->tail] = B->queue[len - 1];
					}
				}
	}

	

	CI KX;  //��X
	CI KY;  //��Y
	//���ԕ��ёւ�
	for (int len = LX->tail; len >= 0; len--)
	{

		KX.queue[LX->tail-len] = LX->queue[len];
		KY.queue[LY->tail - len] = LY->queue[len];
	}
	//���ѕς������̂���ɖ߂�
	for (int len = 0; len < LX->tail >= len; len++)
	{
		LX->queue[len] = KX.queue[len];
		LY->queue[len] = KY.queue[len];
	}

	for (int len = 0; len < LX->tail; len++)
	{
		//X����ς�����^�[�Q�b�g�ɒ��ڍs����͈͂ɂ��Ȃ���
		if(((LX->queue[len] - 1 == this->targetX) || (LX->queue[len] + 1 == this->targetX)) && (LY->queue[len] == this->targetY))
		{
			LX->queue[len + 1] = this->targetX;
			LY->queue[len + 1] = this->targetY;
			
		}
		//Y����ς�����^�[�Q�b�g�ɒ��ڍs����͈͂ɂ��Ȃ���
		if ((LX->queue[len] == this->targetX) && ((LY->queue[len] + 1 == this->targetY) || (LY->queue[len] - 1 == this->targetY)))
		{
			LX->queue[len + 1] = this->targetX;
			LY->queue[len + 1] = this->targetY;
		}
	}

	for (int len = 0; len < LX->tail-1; len++)
	{
		if ((LX->queue[len] == LX->queue[len + 1])&&(LY->queue[len] == LY->queue[len+1]))
		{
		
			for (int sen = len+1; sen < LX->tail - 1; sen++)
			{
				LX->queue[sen] = LX->queue[sen + 1];
				LY->queue[sen] = LY->queue[sen + 1];
			}
			LX->tail--;
			LY->tail--;
		}
	}
}

//���W��\��
void AI::footprints(CI * A, CI * B)
{
	for (int len = 0; len <= A->tail; len++)
	{
		//cout << A->queue[len] << "," << B->queue[len] << "  ";
	}
}

//�T�[�`
void AI::HrzSearch(int nowX, int nowY, CI * Z, CI * W, CI * X, CI * Y)
{
	CI::flag[nowX][nowY] = 1;
	Z->enqueue(nowX);
	W->enqueue(nowY);
	//cout << "now:" << nowX << "," << nowY << endl;
	int  go = 0;

	//for (int j = 0; j < N; j++) {
	//	if (a[i][j] == 1 && flag[j] == 0) {
	//		enqueue(&X, j + 1);
	//	}
	//}

	///////�c�A���ɐV�����s���铹���Ȃ����T��/////////////////

	if (!(CI::map[nowX + 1][nowY] == 1)) 
	{
		if (CI::flag[nowX + 1][nowY] == 0)
		{
			X->enqueue(nowX + 1);
				Y->enqueue(nowY);
				CI::flag[nowX + 1][nowY] = 1;
				go = 1;
		}
	}
	if (!(CI::map[nowX][nowY + 1] == 1)) 
	{
		if (CI::flag[nowX][nowY + 1] == 0)
		{
			X->enqueue(nowX);
			Y->enqueue(nowY + 1);
			CI::flag[nowX][nowY + 1] = 1;
			go = 1;
		}
	}
	if (!(CI::map[nowX - 1][nowY] == 1)) 
	{
		if (CI::flag[nowX - 1][nowY] == 0)
		{
			X->enqueue(nowX - 1);
			Y->enqueue(nowY);
			CI::flag[nowX - 1][nowY] = 1;
			go = 1;
		}
	}
	if (!(CI::map[nowX][nowY - 1] == 1))
	{
		if (CI::flag[nowX][nowY - 1] == 0)
		{
			X->enqueue(nowX);
			Y->enqueue(nowY - 1);
			CI::flag[nowX][nowY - 1] = 1;
			go = 1;
		}
	}

	//�T�����ʓ����Ȃ������ꍇ
	if (go == 0)
	{
		//footdelete(Z, W);
	}

	///////////////////////////////////////////////
}

//�V���������������Ȃ��ꍇ
void AI::footdelete(CI * A, CI * B)
{
	//��߂�
	A->tail--;
	B->tail--;
}

//�}�b�v�t���O�̒l��������
void AI::SetMapflag()
{
	for (int len = 0; len < MAPX; len++)
	{
		for (int sen = 0; sen < MAPY; sen++)
		{
			CI::flag[len][sen] = 0;
		}
	}
}

//�^�[�Q�b�g���w��
void AI::SetTarget(float _x, float _y)
{
	this->targetX = _x;
	this->targetY = _y;
}

void AI::SetHP(int _hp)
{
	this->HP = _hp;
}









