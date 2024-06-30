#pragma once

//　タイトル・ゲーム・リザルト画面の親クラス
//  I = Interface　インターフェイス
// →このクラス事態をnewして使うことはない
//  →子クラスのテンプレートとしての役割
class IScene
{

public:
	// 画面初期化
	virtual void Init();
	//画面終了時解放
	virtual void Release();
	//画面更新
	//子クラスで必ずオーバーライドする
	virtual void Update() = 0;
	//画面描画
	virtual void Draw();
};

