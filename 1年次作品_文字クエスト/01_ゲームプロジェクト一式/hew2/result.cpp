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

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	OTO se=
	{
		LoadSoundMem("魔王魂ジングル07.mp3"),         //敗北           0
		LoadSoundMem("魔王魂ジングル03.mp3"),         //勝利           1

	};
	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	
	int Key;
	int next = 0;
	
	
	if (infor->clear[*stage % 10] == 1)
	{
		//勝利bgm
		PlaySoundMem(se.SE[1], DX_PLAYTYPE_BACK, TRUE);
	}
	else {
		//敗北bgm
		PlaySoundMem(se.SE[0], DX_PLAYTYPE_BACK, TRUE);
		
	}
	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && myreturn == 0)
	{
		// 画面を初期化
		ClearDrawScreen();

		// キー入力を得る
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);


		resultInput();
		resultUpdate(&myreturn, &next,stage,infor,&se);

		// マップとプレイヤーを描画
		resultDraw(&next,stage,infor,&myreturn,&se);

		// 裏画面の内容を表画面に映す
		resultFramewait();
	}
	return myreturn;
}


void resultInput()
{
	
}


void resultUpdate(int *myreturn, int *next,int *stage,INFORMATION *infor,OTO *se)
{

	int MouseXPos = 0;		//マウスのX座標
	int MouseYPos = 0;		//マウスのY座標
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


// マップとプレイヤーの描画関数
void resultDraw(int *next,int *stage,INFORMATION *infor,int *myreturn,OTO *se)
{
	int MouseXPos = 0;		//マウスのX座標
	int MouseYPos = 0;		//マウスのY座標
	GetMousePoint(&MouseXPos, &MouseYPos);
	int fontSize = 50;
	SetFontSize(fontSize);
	if (infor->clear[*stage % 10] == 1)
	{
		DrawFormatString(200, 100, GetColor(255, 255, 255), "%s", "congratulation");
	}
	else {
		//敗北bgm
		PlaySoundMem(se->SE[0], DX_PLAYTYPE_BACK, TRUE);
		DrawFormatString(200, 100, GetColor(255, 0, 0), "%s", "ゲームオーバー");

	}
	fontSize = 18;
	SetFontSize(fontSize);
	LoadGraphScreen(0, 0, "red_ocean.jpg", TRUE);
		DrawFormatString(200, 200, GetColor(255, 255, 255), "%s", "ゲーム選択画面にもどりますか?");
		DrawBox(STARTPOINTX, STARTPOINTY, STARTPOINTX + 100, STARTPOINTY + 50, GetColor(255, 0, 0), TRUE);
		DrawBox(STARTPOINTX + 100, STARTPOINTY, STARTPOINTX + 200, STARTPOINTY + 50, GetColor(0, 0, 255), TRUE);
		DrawFormatString(150, 300, GetColor(255, 255, 255), "%s", "ハイ");
		DrawFormatString(250, 300, GetColor(255, 255, 255), "%s", "ゲームを終わる");

		if ((STARTPOINTX < MouseXPos) && (MouseXPos < STARTPOINTX + 100) && (STARTPOINTY < MouseYPos) && (MouseYPos < STARTPOINTY + 50))
		{
			DrawBox(STARTPOINTX, STARTPOINTY, STARTPOINTX + 100, STARTPOINTY + 50, GetColor(0, 255, 0), TRUE);
			DrawFormatString(150, 300, GetColor(255, 255, 255), "%s", "ハイ");

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			{
				*myreturn = STAGESERECT;

			}

		}


		if ((STARTPOINTX + 100 < MouseXPos) && (MouseXPos < STARTPOINTX + 200) && (STARTPOINTY < MouseYPos) && (MouseYPos < STARTPOINTY + 50))
		{
			DrawBox(STARTPOINTX + 100, STARTPOINTY, STARTPOINTX + 200, STARTPOINTY + 50, GetColor(0, 255, 0), TRUE);
			DrawFormatString(250, 300, GetColor(255, 255, 255), "%s", "ゲームを終わる");

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