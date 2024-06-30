
#include"mainloop.h"
#include"title.h"
#include"game.h"
#include"stageserect.h"
#include"result.h"
#include"waittime.h"

#define GAZOUMAISUU (10)

typedef struct
{
	int PlayerX;
	int PlayerY;
	int scrollX;
	int jumppower;//�W�����v�l
	int OldkeyX;
	int OldkeyY;
}PLAYER;


typedef struct
{
	int gazou[GAZOUMAISUU];
	int goal[4];
}E;

typedef struct
{
	int c[100];
	int d[100];
	int e[100];
	int b[100];
	int a[100];
}ZANZOU;

int serectMAP[MAPYOKO][MAPTATE] =
{
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0} ,
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  52, 52, 52, 1, 0, 0, 0, 51, 51, 51, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  52, 52, 52, 1, 0, 0, 0, 51, 51, 51, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,


	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 63, 1, 0, 0, 0, 0, 0, 62, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,

	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,


	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 64, 1, 0, 0, 0, 0, 0, 61, YUKA, 0, 0, 0} ,

	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  53, 53, 53, 1, 0, 0, 0, 50, 50, 50, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  53, 53, 53, 1, 0, 0, 0, 50, 50, 50, YUKA, 0, 0, 0} ,

	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, YUKA, 0, 0, 0} ,
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, YUKA, 0, 0, 0} ,
	

};


int serectscreen[MAPYOKO][MAPTATE] =
{
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 15, 0} ,
	{ 1, 1, 14, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,


	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,

	{ 1, 40, 40, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 45, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 0, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 0, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 0, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 0, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,

	{ 1, 40, 0, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 0, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 0, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 40, 40, 40, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,

	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 10, 10, 10, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 10, 10, 10, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 10, 10, 10, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,


};

//�C���v�b�g�֐�
void serectInput(Key *);

void serectDraw(PLAYER *,int *,int *,E *e,ZANZOU *seen,INFORMATION *infor,int *,int *,int *);
//�A�E�g�v�b�g�֐�
void serectUpdate(int *,int *,int *,int *,int *,PLAYER *,Key *,INFORMATION *,E *e);

//�t���[���E�G�C�g�֐�
void serectFramewait(void);

int stageserect(int *stage,INFORMATION * infor)
{
	int myreturn = 0;
	int next = 0;
	int Key1;
	int MouseXPos = 0;		//�}�E�X��X���W
	int MouseYPos = 0;		//�}�E�X��Y���W
	Key key;
	PLAYER pla;
	E e = {
		LoadGraph("kannbann1-1.png"),        //1-1�Ŕ@�@�@�@�@�@0
		LoadGraph("kannbann1-2.png"),        //1-2�Ŕ�            1
		LoadGraph("kannbann1-3.png"),        //1-3�Ŕ�            2
		LoadGraph("kannbann1-4.png"),        //1-4�Ŕ�            3
		LoadGraph("mori.png"),               //�X                4
		LoadGraph("kannbann_kuria.png"),        //�ŔN���A     5
		LoadGraph("go-ru.png"),                //�S�[��          6
	};
	//������
	pla.scrollX = 0;
	pla.PlayerX = 300;
	pla.PlayerY = 250;
	pla.OldkeyX = 0;
	pla.OldkeyY = 250;

	ZANZOU seen[AFTIMAGENUM];

	for (int i = 0; i < 50; i++)
	{
		seen[0].a[i] = GetRand(639);
		seen[0].b[i] = GetRand(479);
		seen[0].c[i] = GetRand(255);
		seen[0].d[i] = GetRand(255);
		seen[0].e[i] = GetRand(255);
	}
	for (int sen = 0; sen < AFTIMAGENUM; sen++)
	{
		for (int i = 0; i < 50; i++)
		{
			seen[sen].a[i] = seen[0].a[i];
			seen[sen].b[i] = seen[0].b[i];
			seen[sen].c[i] = seen[0].c[i];
			seen[sen].d[i] = seen[0].d[i];
			seen[sen].e[i] = seen[0].e[i];
		}
	}

	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && myreturn == 0)
	{
		//�C���v�b�g�֐�
		serectInput(&key);

		//�A�b�v�f�[�g�֐�
		serectUpdate(&MouseXPos,&MouseYPos,&next,stage,&myreturn,&pla,&key,infor,&e);

		//draw�֐�
		serectDraw(&pla,&next,stage,&e,seen,infor,&MouseXPos,&MouseYPos,&myreturn);

		//�t���[���E�G�C�g�֐�
		serectFramewait();

		//�L�[���͂𓾂�
		Key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);


		//��ʏ���
		ClearDrawScreen();

	}
	return myreturn;
}



//�L�[
void serectInput(Key *key)
{
	key[0].KeyUp = CheckHitKey(KEY_INPUT_UP);                    //��L�[�������ꂽ�ꍇ
	key[0].KeyDown = CheckHitKey(KEY_INPUT_DOWN);                //���L�[�������ꂽ�ꍇ
	key[0].KeyReturn = CheckHitKey(KEY_INPUT_RETURN);            //���^�[���L�[�������ꂽ�ꍇ
	key[0].KeyRight = CheckHitKey(KEY_INPUT_RIGHT);             //�E�L�[�������ꂽ�ꍇ
	key[0].KeyLeft = CheckHitKey(KEY_INPUT_LEFT);                //���L�[�������ꂽ�ꍇ
	key[0].KeyZ = CheckHitKey(KEY_INPUT_Z);                      //z�L�[�������ꂽ�ꍇ
	key[0].KeyA = CheckHitKey(KEY_INPUT_A);                      //a�L�[�������ꂽ�ꍇ
	key[0].KeyR = CheckHitKey(KEY_INPUT_R);                      //r�L�[�������ꂽ�ꍇ
}

void serectUpdate(int *MouseXPos,int *MouseYPos,int *next,int *stage,int *myreturn,PLAYER *pla,Key *key,INFORMATION *infor,E *e)
{
	
	
		//�X
		DrawExtendGraph(0, 0, 640, 480, e->gazou[4], TRUE);
		if (key->KeyDown == 1)pla->PlayerY += 3;    //���L�[�������ꂽ�ꍇ
		if (key->KeyLeft == 1) pla->PlayerX -= 3;   //���L�[�������ꂽ�ꍇ
		if (key->KeyRight == 1)pla->PlayerX += 3;   //�E�L�[�������ꂽ�ꍇ

		if (!(pla->PlayerX == CENTERX))
		{
			if (pla->PlayerX > CENTERX)
			{
				int s = 0;
				s = pla->PlayerX - CENTERX;
				pla->scrollX -= s;
				pla->PlayerX = CENTERX;
			}
			if (pla->PlayerX < CENTERX)
			{
				int r = 0;
				r = CENTERX - pla->PlayerX;
				pla->scrollX += r;
				pla->PlayerX = CENTERX;
			}

		}

		



		//�W�����v
		// ��������36
		pla->PlayerY -= pla->jumppower;

		// ���������x��������
		pla->jumppower -= 1;

		// �����n�ʂɂ��Ă�����~�܂�
		if (pla->PlayerY > 380)
		{
			pla->PlayerY = 380;
			pla->jumppower = 0;
		}

		// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
		if (CheckHitKey(KEY_INPUT_RETURN) && pla->PlayerY == pla->OldkeyY) pla->jumppower = 10;


		for (int len = 0; len < MAPYOKO; len++)
		{

			for (int sen = 0; sen < MAPTATE; sen++)
			{
				if (serectMAP[len][sen] == 1)
				{
					if ((len * 20 + pla->scrollX <= pla->PlayerX + 20) && (pla->PlayerX <= (len + 1) * 20 + pla->scrollX) && (sen * 20 <= pla->PlayerY + 20) && (pla->PlayerY <= (sen + 1) * 20))
					{
						//�����u���b�N�ɓ���������O�̍��W�ɖ߂�
						pla->scrollX = pla->OldkeyX;
						pla->PlayerY = pla->OldkeyY;
						pla->jumppower = 0;
					}
				}
				if (serectMAP[len][sen] == 50)
				{
					if ((len * 20 + pla->scrollX <= pla->PlayerX + 20) && (pla->PlayerX <= (len + 1) * 20 + pla->scrollX) && (sen * 20 <= pla->PlayerY + 20) && (pla->PlayerY <= (sen + 1) * 20))
					{
						*myreturn = WAITTIME;
						*stage = 11;
					}
				}
				if (serectMAP[len][sen] == 51)
				{
					if ((len * 20 + pla->scrollX <= pla->PlayerX + 20) && (pla->PlayerX <= (len + 1) * 20 + pla->scrollX) && (sen * 20 <= pla->PlayerY + 20) && (pla->PlayerY <= (sen + 1) * 20))
					{
						*myreturn = WAITTIME;
						*stage = 12;
					}
				}
				if (serectMAP[len][sen] == 52)
				{
					if ((len * 20 + pla->scrollX <= pla->PlayerX + 20) && (pla->PlayerX <= (len + 1) * 20 + pla->scrollX) && (sen * 20 <= pla->PlayerY + 20) && (pla->PlayerY <= (sen + 1) * 20))
					{
						*myreturn = WAITTIME;
						*stage = 13;
					}
				}
				if (serectMAP[len][sen] == 53)
				{
					if ((len * 20 + pla->scrollX <= pla->PlayerX + 20) && (pla->PlayerX <= (len + 1) * 20 + pla->scrollX) && (sen * 20 <= pla->PlayerY + 20) && (pla->PlayerY <= (sen + 1) * 20))
					{
						*myreturn = WAITTIME;
						*stage = 14;
					}
				}
			}
		}




		//���̃v���C���[�̍��W������
		pla->OldkeyX = pla->scrollX;
		pla->OldkeyY = pla->PlayerY;
	
}

void serectDraw(PLAYER *pla,int *next,int *stage,E *e,ZANZOU *seen,INFORMATION *infor,int *MouseXPos,int *MouseYPos,int *myreturn)
{
	//���ԏK��
	DATEDATA Date;
	GetDateTime(&Date);
	// �}�E�X�̍��W���擾
		GetMousePoint(&*MouseXPos, &*MouseYPos);

	for (int sen = 0; sen < 100; sen++)
	{
		++seen[0].b[sen];
	}


	for (int len = 0; len < AFTIMAGENUM; len++)
	{
		for (int sen = 0; sen < 100; sen++)
		{
			if (seen[len].b[sen] >= 480)
			{
				seen[len].b[sen] = 0;
			}
			if (seen[len].a[sen] >= 640)
			{
				seen[len].a[sen] = 0;
			}
		}
	}



	
	if (Date.Sec % 2 == 1)
	{
		//seen[0].old[1] = seen[0].a[0];
		//if (seen[0].b[0] <= seen[0].old[0]+5)
		//{


		for (int sen = 0; sen < 100; sen++)
		{
			--seen[0].a[sen];
		}
		//}


	}
	else
	{
		//seen[0].old[0] = seen[0].b[0];
		//if (seen[0].a[0] <= seen[0].old[1]+5)
		//{
		for (int sen = 0; sen < 100; sen++)
		{
			++seen[0].a[sen];
		}
		//}
	}


	//int i = 0;
	//
	//for (i = 0; i < 640; i++)
	//{
	//	DrawLine(i, 0, i+1, 400, GetColor(255*i/640, 0,0));
	//}
	//
	//for (i = 0; i < 420; i++)
	//{
	//	DrawLine(0, i,640,i+1, GetColor(255 * i / 640, 0, 0));
	//
	//}



	// �v���C���[��`�悷��
	for (int i = AFTIMAGENUM - 1; i >= 0; i -= 2)
	{

		for (int len = 0; len < 100; len++)
		{
			DrawPixel(seen[i].a[len], seen[i].b[len], GetColor(seen[i].c[len], seen[i].d[len] - seen[i].d[len] * i / AFTIMAGENUM, seen[i].e[len]));
		}
	}

	// �c���f�[�^����Â��炷
	for (int i = AFTIMAGENUM - 1; i > 0; i--)
	{

		for (int o = 0; o < 100; o++)
		{
			seen[i].a[o] = seen[i - 1].a[o];
			seen[i].b[o] = seen[i - 1].b[o];
			seen[i].c[o] = seen[i - 1].c[o];
			seen[i].d[o] = seen[i - 1].d[o];
			seen[i].e[o] = seen[i - 1].e[o];
		}
	}






	for (int len = 0; len < 4; len++)
	{
		e->goal[len] = -1;
	}

	
		for (int len = 0; len < MAPYOKO; len++)
		{

			for (int sen = 0; sen < MAPTATE; sen++)
			{
				if (serectMAP[len][sen] == 1)
				{
					DrawBox(20 * len + pla->scrollX, 20 * sen, 20 * (len + 1) + pla->scrollX, 20 * (sen + 1), GetColor(255, 255, 0), TRUE);
				}
				if (serectMAP[len][sen] == 50)
				{
					//DrawBox(20 * len + pla->scrollX, 20 * sen, 20 * (len + 1) + pla->scrollX, 20 * (sen + 1), GetColor(25, 25, 25), TRUE);
					if (e->goal[0] == -1)
					{
						DrawRotaGraph((len-2) * 20 + pla->scrollX, (sen+2) * 20, 0.2f, 0, e->gazou[6], TRUE);
						e->goal[0] = 1;
					}
				}
				if (serectMAP[len][sen] == 51)
				{
					//DrawBox(20 * len + pla->scrollX, 20 * sen, 20 * (len + 1) + pla->scrollX, 20 * (sen + 1), GetColor(25, 25, 25), TRUE);
					if (e->goal[1] == -1)
					{
						DrawRotaGraph((len-2) * 20 + pla->scrollX, (sen+2) * 20, 0.2f, 0, e->gazou[6], TRUE);
						e->goal[1] = 1;
					}
				}
				if (serectMAP[len][sen] == 52)
				{
					//DrawBox(20 * len + pla->scrollX, 20 * sen, 20 * (len + 1) + pla->scrollX, 20 * (sen + 1), GetColor(25, 25, 25), TRUE);
					if (e->goal[2] == -1)
					{
						DrawRotaGraph((len-2) * 20 + pla->scrollX, (sen+2) * 20, 0.2f, 0, e->gazou[6], TRUE);
						e->goal[2] = 1;
					}
				}
				if (serectMAP[len][sen] == 53)
				{
					//DrawBox(20 * len + pla->scrollX, 20 * sen, 20 * (len + 1) + pla->scrollX, 20 * (sen + 1), GetColor(25, 25, 25), TRUE);
					if (e->goal[3] == -1)
					{
						DrawRotaGraph((len-2) * 20 + pla->scrollX, (sen+2) * 20, 0.2f, 0, e->gazou[6], TRUE);
						e->goal[3] = 1;
					}
				}
				if (serectMAP[len][sen] == 61)
				{
					DrawRotaGraph(len * 20 + pla->scrollX,sen * 20, 0.2f, 0, e->gazou[0], TRUE);
					if (infor->clear[1] == 1)
					{
						DrawRotaGraph(len * 20 + pla->scrollX, sen * 20, 0.2f, 0, e->gazou[5], TRUE);
					}
				}
				if (serectMAP[len][sen] == 62)
				{
					DrawRotaGraph(len * 20 + pla->scrollX, sen * 20, 0.2f, 0, e->gazou[1], TRUE);
					if (infor->clear[2] == 1)
					{
						DrawRotaGraph(len * 20 + pla->scrollX, sen * 20, 0.2f, 0, e->gazou[5], TRUE);
					}
				}
				if (serectMAP[len][sen] == 63)
				{
					DrawRotaGraph(len * 20 + pla->scrollX, sen * 20, 0.2f, 0, e->gazou[2], TRUE);
					if (infor->clear[3] == 1)
					{
						DrawRotaGraph(len * 20 + pla->scrollX, sen * 20, 0.2f, 0, e->gazou[5], TRUE);
					}
				}
				if (serectMAP[len][sen] == 64)
				{
					DrawRotaGraph(len * 20 + pla->scrollX, sen * 20, 0.2f, 0, e->gazou[3], TRUE);
					if (infor->clear[4] == 1)
					{
						DrawRotaGraph(len * 20 + pla->scrollX, sen * 20, 0.2f, 0, e->gazou[5], TRUE);
					}
				}
				if (serectscreen[len][sen] == 1)
				{
					DrawBox(20 * len, 20 * sen, 20 * (len + 1), 20 * (sen + 1), GetColor(255, 255, 0), TRUE);
				}
				if (serectscreen[len][sen] == 10)
				{
					DrawBox(20 * len, 20 * sen, 20 * (len + 1), 20 * (sen + 1), GetColor(0, 255, 0), TRUE);

				}
				if (serectscreen[len][sen] == 14)
				{
					DrawFormatString(20 * len, 20 * sen, GetColor(255, 255, 255), "%d",0);
					DrawFormatString(20 * len + 20, 20 * sen + 20, GetColor(255, 255, 255), "%d",0);
				}
				if (serectscreen[len][sen] == 15)
				{
					int fontSize = 50;
					SetFontSize(fontSize);
					//�e�ɓ����Ă��镶���\��
					
					fontSize = 18;
					SetFontSize(fontSize);
				}
				if (serectscreen[len][sen] == 40)
				{
					DrawBox(20 * len, 20 * sen, 20 * (len + 1), 20 * (sen + 1), GetColor(0, 0, 255), TRUE);
				}
				if (serectscreen[len][sen] == 45)
				{
					
				    DrawFormatString(len * 20, sen * 20, GetColor(255, 255, 255), "%s","�X�e�[�W�Z���N�g");
					

				}
			}
		}

		////�I�v�V�����{�^��///////////////////////////////////////////////////////
		for (int len = 0; len < MAPYOKO; len++)
		{

			for (int sen = 0; sen < MAPTATE; sen++)
			{
				if (serectscreen[len][sen] == 10)
				{

					if ((len * 20 <= *MouseXPos) && (*MouseXPos <= (len + 1) * 20) && (sen * 20 <= *MouseYPos) && (*MouseYPos <= (sen + 1) * 20))
					{
						if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
						{

							*myreturn = FINISH;

						}
					}
				}
			}
		}
		DrawFormatString(570, 20, GetColor(255, 255, 255), "%s", "�Q�[��\n������\n��");
		DrawBox(pla->PlayerX, pla->PlayerY, pla->PlayerX + 20, pla->PlayerY + 20, GetColor(255, 255, 255), TRUE);
	

}


void serectFramewait()
{
	ScreenFlip();
}



