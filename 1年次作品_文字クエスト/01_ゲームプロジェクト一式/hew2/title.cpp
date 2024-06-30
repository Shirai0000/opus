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
	//フォントサイズ変更///////
	int fontSize = 16;
	SetFontSize(fontSize);
	/////////////////////////
	//カラー（赤）
	unsigned int color;
	color = GetColor(255, 0, 0);
	//カラー（青）
	unsigned int color2;
	color2 = GetColor(0, 0, 255);
	//カラー（緑）
	unsigned int color3;
	color3 = GetColor(0, 255, 0);
	//カラー（橙）
	unsigned int color4;
	color4 = GetColor(122, 122, 0);
	//カラー(薄青)
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
		//入力
		titleInput(key, mouse);
		//更新
		titleUpdate(&go, key, &title1, &myreturn, mouse,&a);

		//描画
		titleDraw(&go, &title1, &myreturn, mouse, key);

		titleFramewait();

		//キー入力を得る
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		ClearDrawScreen();
	}






	return myreturn;
}









void titleDraw(int *go, int *title1, int *myreturn, mouse *mouse,key *key)
{

	//カラー（赤）
	unsigned int color;
	color = GetColor(255, 0, 0);
	//カラー（青）
	unsigned int color2;
	color2 = GetColor(0, 0, 255);
	//カラー（緑）
	unsigned int color3;
	color3 = GetColor(0, 255, 0);
	//カラー（橙）
	unsigned int color4;
	color4 = GetColor(122, 122, 0);
	//カラー(薄青)
	unsigned int color5;
	color5 = GetColor(0, 122, 122);
	DATEDATA Date;
	GetDateTime(&Date);
	//エンターが押されるまで
	if (*title1 == 0)
	{
		DrawFormatString(100, 100, GetColor(255,0,255), "%s", "文字クエスト");
		//一秒ごとに表示する
		if (Date.Sec % 2 == 0)
			DrawFormatString(200, 200, GetColor(255,0,255), "%s", "Press ENTER to start");
	}
	
	if (*title1 == 1)
	{
	
		int MouseXPos = 0;		//マウスのX座標
		int MouseYPos = 0;		//マウスのY座標
		int ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0, dx = 0, dy = 0;
		//マウスの座標を取得
		GetMousePoint(&MouseXPos, &MouseYPos);

		//マウスが範囲に入った場合色変え
		DrawBox(StartPointX, StartPointY, StartPointX + 200, StartPointY + 50, color3, TRUE);
		DrawFormatString(StartPointX, StartPointY + 25, GetColor(255,100,100), "%s", "スタート");
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
		DrawFormatString(StartPointX , StartPointY + 115, GetColor(255,100,100), "%s", "ゲームをやめる");
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
	// 上を押していたら上に進む
	if (key[0].KeyUp == 1) *go -= 200;

	// 下を押していたら下に進む
	if (key[0].KeyDown == 1) *go += 200;
	//リターンキーを押した場合
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