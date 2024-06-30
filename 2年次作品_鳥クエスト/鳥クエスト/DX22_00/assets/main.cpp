//----------------------------------------------------------------
//	Ｃ＋＋言語：
//		サンプル・プログラム
//	概要：
//		CSVデータを読み取り表示する
//
//	2022 HAL Osaka
//----------------------------------------------------------------
#include	<iostream>
#include	<iomanip>
#include	"Csv.h"

//マップチップ配置データ（CSVデータ）のタテヨコ数
constexpr int MAP_WIDTH = 20;
constexpr int MAP_HEIGHT = 15;

int main(void)
{
	//CSVファイルからMAPデータを読み込む
	Csv csv{ "map01.csv" };	//csvファイル名指定して"Csv"クラス変数を作成。
	int data_size = csv.read();	//CSVファイルを読み込む。戻り値は読み込んだデータ数（intデータの数）
	if (data_size < 0) {
		//read()の戻り値が０やマイナス値ならエラー。
		std::cout << "CSV読み込み失敗。" << std::endl;
		return 0;
	}
	//読み取ったデータのポインタ（配列の先頭アドレス）を取得。
	const int* p_csv_data = csv.data();	//読み取ったデータは"p_csv_data[0]～[data_size-1]"に入っている。
	//CSVデータは整数の１次元配列に変換されるので、扱う側でタテヨコ方向の数を決める。
	//この場合は、横方向の数は'MAP_WIDTH'、縦方向の数は'MAP_HEIGHT'として扱っている。
	std::cout << "データの総数:" << data_size << std::endl;
	std::cout << "横幅:" << MAP_WIDTH << std::endl;
	std::cout << "縦幅:" << MAP_HEIGHT << std::endl;
	//２次元として表示し確認する。
	for (int y = 0; y < MAP_HEIGHT; y++) {
		//縦方向の数だけ繰り返す
		for (int x = 0; x < MAP_WIDTH; x++) {
			//横方向の数だけ繰り返す。
			int idx = (y * MAP_WIDTH + x);
			//１次元配列のサイズを超えない様にする。超えた場合は何もしない。
			if (idx < data_size) {
				std::cout << std::setfill(' ') << std::setw(2) << p_csv_data[idx] << ",";
			}
		}
		std::cout << std::endl;	//改行
	}
	//
	std::cout << "終了：何かキー入力";
	std::cin.seekg(std::ios::beg);
	std::cin.get();
	return 0;
}

//----------------------------------------------------------------
//	2022 HAL Osaka
//----------------------------------------------------------------
