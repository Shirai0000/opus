#pragma once
#define NMAX   (64)             //���W���i�[����ő�l
#define MAPX       (10)           //�}�b�vX
#define MAPY       (10)           //�}�b�vY
#define MAPTIPX    (10)           //�}�b�v�`�b�vX�̑傫��
#define MAPTIPY    (10)           //�}�b�v�`�b�vY�̑傫��
#define MAPSTARTX  (0)           //�}�b�v�`�b�v���n�܂�X���W
#define MAPSTARTY  (0)           //�}�b�v�`�b�v���n�܂�Y���W

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

	
	static int flag[MAPX][MAPY];  //��x�ʂ�����
	static int map[MAPX][MAPY];  //�}�b�v

	static void Setmap(int _map[MAPX][MAPY]);  //�}�b�v����n��


	
};