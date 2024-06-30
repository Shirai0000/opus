//----------------------------------------------------------------
//	�b�{�{����F
//		�T���v���E�v���O����
//	�T�v�F
//		CSV�f�[�^�������N���X
//
//	2022 HAL Osaka
//----------------------------------------------------------------
#include	"Csv.h"
#include	<iostream>
#include	<string>
#include	<fstream>
#include	<sstream>
#include	<stdexcept>
using namespace std;

//----------------------------------------------------------------
// CSV�t�H�[�}�b�g�̃f�[�^�P�s��(������)�𐮐��W���ɕϊ�����B
// �����ɕϊ��ł��Ȃ����̂͋����I��(0)�ɕϊ����Ă���B
//
vector<int>* conv_csv_line(string& _str)
{
	string	str;	//getline()�Ő؂�o������������󂯎��ꏊ
	istringstream	iss(_str);	//������X�g���[������
	vector<int>*	p_result = new vector<int>;	//�؂�o����������ϊ���������(int)������ϒ��z��B
	//getline�ŕ�����̍Ō�܂�','�ŋ�؂�ꂽ�������ϊ�����B
	//getline()�͐؂�o������̂������Ȃ��'false'�ɂȂ�B
	while (getline(iss, str, ',')) {
		//�����񂩂琔�l�ւ̕ϊ�(stoi�֐�)�ł́A���l�ȊO�̕������ϊ����悤�Ƃ����ꍇ�A
		//�u��O�v����������̂Łutry�`catch�v�ŏ������Ă���B
		try {
			int num = stoi(str);	//����������𐔎��ɕϊ�
			p_result->push_back(num);	//�����ɒǉ�
		}
		catch (const invalid_argument& e) {
			//��O�F�ϊ��o���Ȃ��l������
			p_result->push_back(0);	//�����I��(0)�ɕϊ�����B
			//std::cerr << e.what();	//�f�o�b�O�p�G���[�o��
		}
		catch (const out_of_range& e) {
			//��O�F�͈͊O�̒l������
			p_result->push_back(0);	//�����I��(0)�ɕϊ�����B
			//std::cerr << e.what();	//�f�o�b�O�p�G���[�o��
		}
	}
	return p_result;	//�ϊ���̐����W���ւ̃|�C���^��Ԃ��B
}	//conv_csv_line

//----------------------------------------------------------------
// CSV�f�[�^�̓ǂݍ���
//	�ǂݍ��񂾃f�[�^��int�^�̉ϒ��z��'p_vec'�Ɋi�[�����B
//	�߂�l�F�ǂݍ���ŕϊ������v�f���iint�^�̐��j��Ԃ��B
//	�@�@�@�@�ǂݍ��ݎ��s�����ꍇ��(-1)��Ԃ��B
int Csv::read(void) {
	if (this->file_path == nullptr) {
		return -1;	//�t�@�C����������
	}
	if (this->p_vec != nullptr) {
		return (int)this->size();	//���ɓǂݍ��ݍς݂Ȃ̂ŗv�f����Ԃ�
	}
	//�w�肳�ꂽ�t�@�C��������̓t�@�C���X�g���[�����J��
	ifstream	ifs(this->file_path);
	if (!ifs) {
		return -1;	//���s
	}
	//�����̉ϗp�z��(vector<int>)���쐬
	this->p_vec = new vector<int>;	//�쐬
	string	line;	//�P�s���ǂݍ��ޕ�����
	//���̓t�@�C���X�g���[������getline()�ōŌ�̍s�܂łP�s�Âǂݍ��ށB
	//getline()�̓t�@�C���̏I���Ȃ��'false'�ɂȂ�B
	while (getline(ifs, line)) {
		vector<int>* line_vec = conv_csv_line(line);	//�P�s��','��؂�̃f�[�^�Ƃ��āA�����̐����l�ɕϊ�
		p_vec->insert(p_vec->end(), line_vec->begin(), line_vec->end());	//�ϊ������P�s����'p_vec'�̖����ɒǉ�
		delete line_vec;	//�ǉ������̂ŕϊ��Ɏg�����I�u�W�F�N�g�͍폜
		line_vec = nullptr;	//�O�̂���'nullptr'�ŃN���A
	}
	ifs.close();	//���̓t�@�C���X�g���[�������
	return (int)this->size();	//�ϊ������v�f����Ԃ�
}	//read

//----------------------------------------------------------------
//	2022 HAL Osaka
//----------------------------------------------------------------
