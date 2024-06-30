#pragma once
#include "DxLib.h"






#define OUT   -1
#define NONE   0
#define TITLE  1
#define MAIN   66
#define MAP    3
#define SAVE   4
#define LOAD   5
#define HENSEI   6
#define AITEM  7
#define INITIALSETTING 8
#define RESULT       9
#define COURSE       10
#define STAGESERECT  11
#define GAME         12
#define WAITTIME     13


#define FINISH 100



#define     TATE   300
#define    YOKO	  160
#define  GARD     10
#define  RECORD_MAX  25
#define  STARTPOINTX  140
#define  STARTPOINTY  290
#define  STAGESUU     4

typedef struct {
	int mouseR;
}mouse;

typedef struct {
	int time;
	char name[20];
}record;



typedef struct {
	int clear[4];
	int tutoria;
}INFORMATION;


typedef struct
{
	int KeyUp;      //上キー
	int KeyDown;    //下キー
	int KeyReturn;  //リターンキー
	int KeyRight;   //右キー
	int KeyLeft;    //左キー
	int KeyZ;       //zキー
	int KeyA;       //aキー
	int KeyR;       //rキー
}Key;


#define MAPYOKO  (140)

#define MAPTATE  (40)


#define CENTERX    (300)

#define CENTERY    (350)

#define YUKA (1000) //当たり判定のない床

//// 残像データの数
#define AFTIMAGENUM	65

#define StartPointX (200)
#define StartPointY (100)

