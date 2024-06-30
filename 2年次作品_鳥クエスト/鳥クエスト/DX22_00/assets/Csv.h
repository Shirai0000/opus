#pragma once
//----------------------------------------------------------------
//	�b�{�{����F
//		�T���v���E�v���O����
//	�T�v�F
//		CSV�f�[�^�������N���X
//
//	2022 HAL Osaka
//----------------------------------------------------------------
#include	<vector>

//----------------------------------------------------------------
//	CSV�f�[�^�������N���X
//		CSV�t�@�C���i�����j��ǂݍ��݁A���������񂩂琔�l�f�[�^�i�����j�ɕϊ�����
//
class Csv {
private:
	std::vector<int>* p_vec;	//�f�[�^�{�́Bint�^�̉ϒ��z��
	const char* const file_path;	//CSV�t�@�C���̃p�X(�t�@�C����)
public:
	//----------------
	//�R���X�g���N�^
	//	_file_name�F�ǂݍ��ރt�@�C�����i�t�@�C���p�X�j���w�肷��
	Csv(const char* const _file_name)
		:file_path{ _file_name }, p_vec{nullptr}
	{
	}

	//----------------
	//�f�X�g���N�^
	virtual ~Csv() {
		if (this->p_vec != nullptr) {
			delete this->p_vec;	//�m�ۂ����f�[�^�o�b�t�@�iint�^�ϒ��z��j���폜����
			this->p_vec = nullptr;	//�폜�����̂�nullptr�����Ă���
		}
	}

	//----------------
	//�ǂݍ��񂾃f�[�^�̃A�h���X��int�^�ϒ��z��̃|�C���^�Ƃ��ĕԂ�
	inline int* data(void) const { return this->p_vec->data();}

	//----------------
	//�ǂݍ��񂾃f�[�^�̗v�f�����擾
	inline const size_t size(void) const { return this->p_vec->size();}

	//----------------
	//�R���X�g���N�^�Ŏw�肳�ꂽCSV�t�@�C������f�[�^��ǂݍ��ށB
	int read(void);

	//----------------
	//csv�t�@�C���Ƀf�[�^�������o���B
	//int write(void){/*������*/}
};	//Csv

//----------------------------------------------------------------
//	2022 HAL Osaka
//----------------------------------------------------------------
