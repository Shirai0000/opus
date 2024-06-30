//----------------------------------------------------------------
//	�b�{�{����F
//		�T���v���E�v���O����
//	�T�v�F
//		CSV�f�[�^��ǂݎ��\������
//
//	2022 HAL Osaka
//----------------------------------------------------------------
#include	<iostream>
#include	<iomanip>
#include	"Csv.h"

//�}�b�v�`�b�v�z�u�f�[�^�iCSV�f�[�^�j�̃^�e���R��
constexpr int MAP_WIDTH = 20;
constexpr int MAP_HEIGHT = 15;

int main(void)
{
	//CSV�t�@�C������MAP�f�[�^��ǂݍ���
	Csv csv{ "map01.csv" };	//csv�t�@�C�����w�肵��"Csv"�N���X�ϐ����쐬�B
	int data_size = csv.read();	//CSV�t�@�C����ǂݍ��ށB�߂�l�͓ǂݍ��񂾃f�[�^���iint�f�[�^�̐��j
	if (data_size < 0) {
		//read()�̖߂�l���O��}�C�i�X�l�Ȃ�G���[�B
		std::cout << "CSV�ǂݍ��ݎ��s�B" << std::endl;
		return 0;
	}
	//�ǂݎ�����f�[�^�̃|�C���^�i�z��̐擪�A�h���X�j���擾�B
	const int* p_csv_data = csv.data();	//�ǂݎ�����f�[�^��"p_csv_data[0]�`[data_size-1]"�ɓ����Ă���B
	//CSV�f�[�^�͐����̂P�����z��ɕϊ������̂ŁA�������Ń^�e���R�����̐������߂�B
	//���̏ꍇ�́A�������̐���'MAP_WIDTH'�A�c�����̐���'MAP_HEIGHT'�Ƃ��Ĉ����Ă���B
	std::cout << "�f�[�^�̑���:" << data_size << std::endl;
	std::cout << "����:" << MAP_WIDTH << std::endl;
	std::cout << "�c��:" << MAP_HEIGHT << std::endl;
	//�Q�����Ƃ��ĕ\�����m�F����B
	for (int y = 0; y < MAP_HEIGHT; y++) {
		//�c�����̐������J��Ԃ�
		for (int x = 0; x < MAP_WIDTH; x++) {
			//�������̐������J��Ԃ��B
			int idx = (y * MAP_WIDTH + x);
			//�P�����z��̃T�C�Y�𒴂��Ȃ��l�ɂ���B�������ꍇ�͉������Ȃ��B
			if (idx < data_size) {
				std::cout << std::setfill(' ') << std::setw(2) << p_csv_data[idx] << ",";
			}
		}
		std::cout << std::endl;	//���s
	}
	//
	std::cout << "�I���F�����L�[����";
	std::cin.seekg(std::ios::beg);
	std::cin.get();
	return 0;
}

//----------------------------------------------------------------
//	2022 HAL Osaka
//----------------------------------------------------------------
