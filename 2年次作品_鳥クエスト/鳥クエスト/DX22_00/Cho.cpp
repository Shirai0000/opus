#include "Cho.h"

CI::CI(void)
{
	set_openlist();   //初期化

}

//初期化
void CI::set_openlist()
{
	this->head = NMAX;
	this->tail = NMAX;
}

int CI::dequeue(void)
{
	int date;

	date = this->queue[this->head];
	this->head++;
	return date;
}


//次に探索する数字を格納
void CI::enqueue(int v)
{
	if (this->head == NMAX) {
		this->head = 0;
		this->tail = 0;
		this->queue[0] = v;
	}
	else {
		this->tail++;
		this->queue[this->tail] = v;
	}
}

//マップ
void CI::Setmap(int _map[MAPX][MAPY])
{


	for (int len = 0; len < MAPX; len++)
	{
		for (int sen = 0; sen < MAPY; sen++)
		{
			map[len][sen] = _map[len][sen];
		}
	}
}
