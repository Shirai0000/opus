#pragma once
#define NMAX   (64)             //座標を格納する最大値
#define MAPX       (10)           //マップX
#define MAPY       (10)           //マップY
#define MAPTIPX    (10)           //マップチップXの大きさ
#define MAPTIPY    (10)           //マップチップYの大きさ
#define MAPSTARTX  (0)           //マップチップが始まるX座標
#define MAPSTARTY  (0)           //マップチップが始まるY座標

class CI
{
public:

	int queue[NMAX];
	int head;   
	int tail;
public:
	CI(void);
	void set_openlist(void);
	int dequeue(void);
	void enqueue(int v);

	
	static int flag[MAPX][MAPY];  //一度通った道
	static int map[MAPX][MAPY];  //マップ

	static void Setmap(int _map[MAPX][MAPY]);  //マップ情報を渡す


	
};