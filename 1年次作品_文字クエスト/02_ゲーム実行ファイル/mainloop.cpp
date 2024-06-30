//------------------------
// クラス記号：AT11A127
// 出席番号：12
// 氏名：白井嘉高
//------------------------


#include"mainloop.h"
#include"title.h"
#include"game.h"
#include"stageserect.h"
#include"result.h"
#include"waittime.h"



int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpLC, int nSC)
{
	ChangeWindowMode(TRUE);		//ウィンドウモードで起動


	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;	  // エラーが起きたら直ちに終了
	}
	BOOL next = FALSE;

	//まずはタイトルから
	int progress = TITLE;
	int stage = 11;
	INFORMATION infor;
	infor.tutoria = 0;
	for (int len = 0; len < 4; len++)
	{
		infor.clear[len] = 0;
	}

	record reco[RECORD_MAX];

	while (!next) {
		switch (progress) {
		case	TITLE:	//タイトル
			progress = title();
			break;
		case   GAME:		//ゲーム
			progress = game(&stage,&infor);
			break;
		case   STAGESERECT:
			progress = stageserect(&stage,&infor);
			break;
		case RESULT:
			progress = result(&stage,&infor);
	
			break;
		case WAITTIME:
			progress = waittime(&stage,&infor);
			break;
		case	NONE:		//★何もしない場合はアプリ終了
		case	FINISH:	//★アプリ終了
		default:
			//不明な値はエラーなのでアプリを終了させる。
			next = TRUE;	//★ループ終了：アプリ終了
			break;
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;

}