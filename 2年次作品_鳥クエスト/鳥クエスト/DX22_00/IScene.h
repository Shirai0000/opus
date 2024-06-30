#pragma once

//�@�^�C�g���E�Q�[���E���U���g��ʂ̐e�N���X
//  I = Interface�@�C���^�[�t�F�C�X
// �����̃N���X���Ԃ�new���Ďg�����Ƃ͂Ȃ�
//  ���q�N���X�̃e���v���[�g�Ƃ��Ă̖���
class IScene
{

public:
	// ��ʏ�����
	virtual void Init();
	//��ʏI�������
	virtual void Release();
	//��ʍX�V
	//�q�N���X�ŕK���I�[�o�[���C�h����
	virtual void Update() = 0;
	//��ʕ`��
	virtual void Draw();
};

