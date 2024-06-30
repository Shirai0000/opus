//------------------------
// �N���X�L���FAT11A127
// �o�Ȕԍ��F12
// �����F����Í�
//------------------------


#include"mainloop.h"
#include"title.h"
#include"game.h"
#include"stageserect.h"
#include"result.h"
#include"waittime.h"



int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpLC, int nSC)
{
	ChangeWindowMode(TRUE);		//�E�B���h�E���[�h�ŋN��


	if (DxLib_Init() == -1)    // �c�w���C�u��������������
	{
		return -1;	  // �G���[���N�����璼���ɏI��
	}
	BOOL next = FALSE;

	//�܂��̓^�C�g������
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
		case	TITLE:	//�^�C�g��
			progress = title();
			break;
		case   GAME:		//�Q�[��
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
		case	NONE:		//���������Ȃ��ꍇ�̓A�v���I��
		case	FINISH:	//���A�v���I��
		default:
			//�s���Ȓl�̓G���[�Ȃ̂ŃA�v�����I��������B
			next = TRUE;	//�����[�v�I���F�A�v���I��
			break;
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;

}