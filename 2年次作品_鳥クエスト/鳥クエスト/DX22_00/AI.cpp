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
	//誤差修正
	if ((int)(this->Xpos * 100) % 10 > 8)
	{
		this->Xpos += 0.1;
		this->Xpos -= 0.09;
	}
	//誤差修正
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

//今の座標を設定
void AI::Setpos(float _x, float  _y)
{
	this->Xpos = _x;
	this->Ypos = _y;
}


//行っていないが行けることがわかっている道を表示
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


//最短ルートを作る
void AI::saitan(int map[MAPX][MAPY],float *_x,float *_y)
{
	////初期化//////////
	AI a;
	CI X;
	CI Y;
	CI Z;
	CI W;
	CI LX;
	CI LY;
	////////////////////

	int suu = 0;
	SetMapflag();   //マップフラグの値を初期化
	suu++;
	//cout << "Search" << suu << endl;  //サーチ回数
	HrzSearch((int)this->Xpos, (int)this->Ypos, &Z, &W, &X, &Y);               //探索(初期位置)
	a.show_openlist(&X, &Y);           //行っていないが行けることがわかっている道を表示

	do {
		suu++;
		//cout << "Search" << suu << endl;  //サーチ回数
		HrzSearch(X.dequeue(), Y.dequeue(), &Z, &W, &X, &Y);
		a.show_openlist(&X, &Y);

	} while (!(CI::flag[(int)this->targetX][(int)this->targetY] == 1));

	delet(&LX, &LY, &Z, &W);              //いらないルートを削除
	footprints(&LX, &LY);       //最短ルートを表示
	*_x = (float)LX.queue[1];
	*_y = (float)LY.queue[1];
	//footprints(&Z, &W);

}


//最短ルートに必要ない座標を削除
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

	

	CI KX;  //仮X
	CI KY;  //仮Y
	//順番並び替え
	for (int len = LX->tail; len >= 0; len--)
	{

		KX.queue[LX->tail-len] = LX->queue[len];
		KY.queue[LY->tail - len] = LY->queue[len];
	}
	//並び変えたものを基に戻す
	for (int len = 0; len < LX->tail >= len; len++)
	{
		LX->queue[len] = KX.queue[len];
		LY->queue[len] = KY.queue[len];
	}

	for (int len = 0; len < LX->tail; len++)
	{
		//X軸を変えたらターゲットに直接行ける範囲にいないか
		if(((LX->queue[len] - 1 == this->targetX) || (LX->queue[len] + 1 == this->targetX)) && (LY->queue[len] == this->targetY))
		{
			LX->queue[len + 1] = this->targetX;
			LY->queue[len + 1] = this->targetY;
			
		}
		//Y軸を変えたらターゲットに直接行ける範囲にいないか
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

//座標を表示
void AI::footprints(CI * A, CI * B)
{
	for (int len = 0; len <= A->tail; len++)
	{
		//cout << A->queue[len] << "," << B->queue[len] << "  ";
	}
}

//サーチ
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

	///////縦、横に新しく行ける道がないか探索/////////////////

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

	//探索結果道がなかった場合
	if (go == 0)
	{
		//footdelete(Z, W);
	}

	///////////////////////////////////////////////
}

//新しい道が見つけられない場合
void AI::footdelete(CI * A, CI * B)
{
	//一つ戻す
	A->tail--;
	B->tail--;
}

//マップフラグの値を初期化
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

//ターゲットを指定
void AI::SetTarget(float _x, float _y)
{
	this->targetX = _x;
	this->targetY = _y;
}

void AI::SetHP(int _hp)
{
	this->HP = _hp;
}









