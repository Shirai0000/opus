#include"mainloop.h"
#include"title.h"
#include"game.h"
#include"stageserect.h"
#include"result.h"

#define SENUMBER (2)

typedef struct 
{
	int SE[SENUMBER];
}OTO;


void resultInput();
void resultDraw(int *,int *,INFORMATION *,int *,OTO *);
void resultFramewait(void);
void resultUpdate(int *, int *,int *,INFORMATION *,OTO *);

int result(int *stage,INFORMATION *infor)
{
	int myreturn = 0;
	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	OTO se=
	{
		LoadSoundMem("�������W���O��07.mp3"),         //�s�k           0
		LoadSoundMem("�������W���O��03.mp3"),         //����           1

	};
	// �`����ʂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	
	int Key;
	int next = 0;
	
	
	if (infor->clear[*stage % 10] == 1)
	{
		//����bgm
		PlaySoundMem(se.SE[1], DX_PLAYTYPE_BACK, TRUE);
	}
	else {
		//�s�kbgm
		PlaySoundMem(se.SE[0], DX_PLAYTYPE_BACK, TRUE);
		
	}
	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && myreturn == 0)
	{
		// ��ʂ�������
		ClearDrawScreen();

		// �L�[���͂𓾂�
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);


		resultInput();
		resultUpdate(&myreturn, &next,stage,infor,&se);

		// �}�b�v�ƃv���C���[��`��
		resultDraw(&next,stage,infor,&myreturn,&se);

		// ����ʂ̓��e��\��ʂɉf��
		resultFramewait();
	}
	return myreturn;
}


void resultInput()
{
	
}


void resultUpdate(int *myreturn, int *next,int *stage,INFORMATION *infor,OTO *se)
{

	int MouseXPos = 0;		//�}�E�X��X���W
	int MouseYPos = 0;		//�}�E�X��Y���W
	GetMousePoint(&MouseXPos, &MouseYPos);

	
		if ((STARTPOINTX < MouseXPos) && (MouseXPos < STARTPOINTX + 100) && (STARTPOINTY < MouseYPos) && (MouseYPos < STARTPOINTY + 50))
		{

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = COURSE;

			}

		}


		if ((STARTPOINTX + 100 < MouseXPos) && (MouseXPos < STARTPOINTX + 200) && (STARTPOINTY < MouseYPos) && (MouseYPos < STARTPOINTY + 50))
		{

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = FINISH;
			}
		}
	
	
		
	
		if ((STARTPOINTX < MouseXPos) && (MouseXPos < STARTPOINTX + 100) && (STARTPOINTY + 100 < MouseYPos) && (MouseYPos < STARTPOINTY + 150))
		{

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = COURSE;

			}

		}


		if ((STARTPOINTX + 100 < MouseXPos) && (MouseXPos < STARTPOINTX + 200) && (STARTPOINTY + 100 < MouseYPos) && (MouseYPos < STARTPOINTY + 150))
		{

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = FINISH;
			}
		}
	




}


// �}�b�v�ƃv���C���[�̕`��֐�
void resultDraw(int *next,int *stage,INFORMATION *infor,int *myreturn,OTO *se)
{
	int MouseXPos = 0;		//�}�E�X��X���W
	int MouseYPos = 0;		//�}�E�X��Y���W
	GetMousePoint(&MouseXPos, &MouseYPos);
	int fontSize = 50;
	SetFontSize(fontSize);
	if (infor->clear[*stage % 10] == 1)
	{
		DrawFormatString(200, 100, GetColor(255, 255, 255), "%s", "congratulation");
	}
	else {
		//�s�kbgm
		PlaySoundMem(se->SE[0], DX_PLAYTYPE_BACK, TRUE);
		DrawFormatString(200, 100, GetColor(255, 0, 0), "%s", "�Q�[���I�[�o�[");

	}
	fontSize = 18;
	SetFontSize(fontSize);
	LoadGraphScreen(0, 0, "red_ocean.jpg", TRUE);
		DrawFormatString(200, 200, GetColor(255, 255, 255), "%s", "�Q�[���I����ʂɂ��ǂ�܂���?");
		DrawBox(STARTPOINTX, STARTPOINTY, STARTPOINTX + 100, STARTPOINTY + 50, GetColor(255, 0, 0), TRUE);
		DrawBox(STARTPOINTX + 100, STARTPOINTY, STARTPOINTX + 200, STARTPOINTY + 50, GetColor(0, 0, 255), TRUE);
		DrawFormatString(150, 300, GetColor(255, 255, 255), "%s", "�n�C");
		DrawFormatString(250, 300, GetColor(255, 255, 255), "%s", "�Q�[�����I���");

		if ((STARTPOINTX < MouseXPos) && (MouseXPos < STARTPOINTX + 100) && (STARTPOINTY < MouseYPos) && (MouseYPos < STARTPOINTY + 50))
		{
			DrawBox(STARTPOINTX, STARTPOINTY, STARTPOINTX + 100, STARTPOINTY + 50, GetColor(0, 255, 0), TRUE);
			DrawFormatString(150, 300, GetColor(255, 255, 255), "%s", "�n�C");

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = STAGESERECT;

			}

		}


		if ((STARTPOINTX + 100 < MouseXPos) && (MouseXPos < STARTPOINTX + 200) && (STARTPOINTY < MouseYPos) && (MouseYPos < STARTPOINTY + 50))
		{
			DrawBox(STARTPOINTX + 100, STARTPOINTY, STARTPOINTX + 200, STARTPOINTY + 50, GetColor(0, 255, 0), TRUE);
			DrawFormatString(250, 300, GetColor(255, 255, 255), "%s", "�Q�[�����I���");

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = FINISH;
			}
		}

	




}

void resultFramewait()
{
	ScreenFlip();
}