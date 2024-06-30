#pragma once
#include "Cho.h"
#define KETA (10)   //有効桁数
#define AIR  (5)   //敵AI半径


class AI
{
protected:
	float Xpos;           //現在の座標
	float Ypos;           //現在の座標
	int HP;               //HP
	float speed;          //移動速度  1を割った数で余りがでない数字
	float destinationX;   //行先座標
	float destinationY;   //行先座標
	float targetX;        //ターゲット座標(プレイヤー、罠、本拠地)
	float targetY;        //ターゲット座標(プレイヤー、罠、本拠地)
public:
	AI(void);
	virtual void Update();
	void Setpos(float _x, float _y);   //AIの今の座標を設定
	void SetTarget(float _x,float _y);              //ターゲットの座標を設定
	void SetHP(int _hp);                           //HPを設定


	////////最短ルートを発見するための関数///////////////////
	void show_openlist(CI *A, CI *B);
	virtual void saitan(int map[MAPX][MAPY], float * _x, float *_y);      //最短ルートを発見
	void delet(CI*LX, CI*LY, CI *A, CI *B);                       //最短ルートに必要ない座標を排除
	void footprints(CI *A, CI *B);
	virtual void HrzSearch(int nowX, int nowY, CI *Z, CI *W, CI *X, CI *Y);
	void footdelete(CI *A, CI *B);
	void SetMapflag();             //マップフラグを初期化
	//////////////////////////////////////////////////////////
};






