#include"mainloop.h"
#include"title.h"
#include"game.h"
#include"stageserect.h"
#include"result.h"
#include"waittime.h"


int waittime(int *stage,INFORMATION *infor)
{
	int myreturn = 0;
	int fontSize = 50;
	SetFontSize(fontSize);
	int r = 120;
	int key;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && myreturn == 0)
	{
		if (r > 0)
		{
			if (*stage == 0)
			{
				DrawFormatString(200, 200, GetColor(255, 255, 255), "%s", "チュートリアル");
			}
			else
			{
				DrawFormatString(200, 200, GetColor(255, 255, 255), "%d -　%dステージ", *stage / 10, *stage % 10);
			}
		}
		if (r == 0)
		{
			myreturn = GAME;
		}
	
		--r;

		ScreenFlip();


		//キー入力を得る
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);


		//画面消す
		ClearDrawScreen();

	}
	fontSize = 18;
	SetFontSize(fontSize);
	return myreturn;
}


