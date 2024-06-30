#include"mainloop.h"
#include"title.h"
#include"game.h"
#include"stageserect.h"

typedef struct
{
	int KeyUp;
	int KeyDown;
	int KeyReturn;
	int KeyRight;
	int KeyReft;
	int SpaceKey;
}key;
void titleUpdate(int *, key *, int *, int *, mouse *,int *);
void titleDraw(int *, int *, int *, mouse *mouse, key *);
void titleInput(key *key, mouse *mouse);
void titleFramewait(void);


int title()
{
	SetGraphMode(640, 480, 16);
	//�t�H���g�T�C�Y�ύX///////
	int fontSize = 16;
	SetFontSize(fontSize);
	/////////////////////////
	//�J���[�i�ԁj
	unsigned int color;
	color = GetColor(255, 0, 0);
	//�J���[�i�j
	unsigned int color2;
	color2 = GetColor(0, 0, 255);
	//�J���[�i�΁j
	unsigned int color3;
	color3 = GetColor(0, 255, 0);
	//�J���[�i��j
	unsigned int color4;
	color4 = GetColor(122, 122, 0);
	//�J���[(����)
	unsigned int color5;
	color5 = GetColor(0, 122, 122);

	int title1 = 0;
	key key[1] = {
		{0,0,0,0}
	};

	mouse mouse[1] =
	{
		{0}
	};

	int go = 0;
	int Key;
	int myreturn = 0;


	int a = LoadGraph("taitol.png");



	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && myreturn == 0)
	{
		//����
		titleInput(key, mouse);
		//�X�V
		titleUpdate(&go, key, &title1, &myreturn, mouse,&a);

		//�`��
		titleDraw(&go, &title1, &myreturn, mouse, key);

		titleFramewait();

		//�L�[���͂𓾂�
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		ClearDrawScreen();
	}






	return myreturn;
}









void titleDraw(int *go, int *title1, int *myreturn, mouse *mouse,key *key)
{

	//�J���[�i�ԁj
	unsigned int color;
	color = GetColor(255, 0, 0);
	//�J���[�i�j
	unsigned int color2;
	color2 = GetColor(0, 0, 255);
	//�J���[�i�΁j
	unsigned int color3;
	color3 = GetColor(0, 255, 0);
	//�J���[�i��j
	unsigned int color4;
	color4 = GetColor(122, 122, 0);
	//�J���[(����)
	unsigned int color5;
	color5 = GetColor(0, 122, 122);
	DATEDATA Date;
	GetDateTime(&Date);
	//�G���^�[���������܂�
	if (*title1 == 0)
	{
		DrawFormatString(100, 100, GetColor(255,0,255), "%s", "�����N�G�X�g");
		//��b���Ƃɕ\������
		if (Date.Sec % 2 == 0)
			DrawFormatString(200, 200, GetColor(255,0,255), "%s", "Press ENTER to start");
	}
	
	if (*title1 == 1)
	{
	
		int MouseXPos = 0;		//�}�E�X��X���W
		int MouseYPos = 0;		//�}�E�X��Y���W
		int ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0, dx = 0, dy = 0;
		//�}�E�X�̍��W���擾
		GetMousePoint(&MouseXPos, &MouseYPos);

		//�}�E�X���͈͂ɓ������ꍇ�F�ς�
		DrawBox(StartPointX, StartPointY, StartPointX + 200, StartPointY + 50, color3, TRUE);
		DrawFormatString(StartPointX, StartPointY + 25, GetColor(255,100,100), "%s", "�X�^�[�g");
		if ((StartPointX < MouseXPos) && (MouseXPos < StartPointX + 200) && (StartPointY < MouseYPos) && (MouseYPos < StartPointY + 50))
		{
			DrawBox(StartPointX, StartPointY, StartPointX + 200, StartPointY + 50, color5, TRUE);
			DrawFormatString(StartPointX + 100, StartPointY + 25, GetColor(255,100,100), "%s", "new game");
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = STAGESERECT;
			}

		}


		DrawBox(StartPointX, StartPointY + 100, StartPointX + 200, StartPointY + 150, color3, TRUE);
		DrawFormatString(StartPointX , StartPointY + 115, GetColor(255,100,100), "%s", "�Q�[������߂�");
		if ((StartPointX < MouseXPos) && (MouseXPos < StartPointX + 200) && (StartPointY + 100 < MouseYPos) && (MouseYPos < StartPointY + 150))
		{
			DrawBox(StartPointX, StartPointY + 100, StartPointX + 200, StartPointY + 150, color5, TRUE);
			DrawFormatString(StartPointX + 100, StartPointY + 115, GetColor(255,100,100), "%s", "exiting");
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = FINISH;
			}
		}

	}

	
}




void titleFramewait(void)
{
	ScreenFlip();
}

void titleInput(key *key, mouse *mouse)
{

	key[0].KeyUp = CheckHitKey(KEY_INPUT_UP);
	key[0].KeyDown = CheckHitKey(KEY_INPUT_DOWN);
	key[0].KeyReturn = CheckHitKey(KEY_INPUT_RETURN);
	key[0].SpaceKey = CheckHitKey(KEY_INPUT_SPACE);
	mouse[0].mouseR = (GetMouseInput() & MOUSE_INPUT_LEFT);


}

void titleUpdate(int *go, key *key, int *title1, int *myreturn, mouse *mouse,int *a)
{

	DrawExtendGraph(0, 0, 640, 480,*a, TRUE);
	// ��������Ă������ɐi��
	if (key[0].KeyUp == 1) *go -= 200;

	// ���������Ă����牺�ɐi��
	if (key[0].KeyDown == 1) *go += 200;
	//���^�[���L�[���������ꍇ
	if (key[0].KeyReturn)
	{
		if (*title1 == 0)
		{
			*title1 = 1;
		}
		if (*title1 == 2)
		{
			*title1 = 3;
		}


	}
	if (mouse[0].mouseR == 1)
	{
		if (*title1 == 3)
		{
			*myreturn = COURSE;
		}
	}
	if (key[0].SpaceKey == 1)
	{
		
	}

}