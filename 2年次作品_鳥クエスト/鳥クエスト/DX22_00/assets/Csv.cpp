//----------------------------------------------------------------
//	Ｃ＋＋言語：
//		サンプル・プログラム
//	概要：
//		CSVデータを扱うクラス
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
// CSVフォーマットのデータ１行分(文字列)を整数集合に変換する。
// 数字に変換できないものは強制的に(0)に変換している。
//
vector<int>* conv_csv_line(string& _str)
{
	string	str;	//getline()で切り出した文字列を受け取る場所
	istringstream	iss(_str);	//文字列ストリーム入力
	vector<int>*	p_result = new vector<int>;	//切り出した数字を変換した整数(int)を入れる可変長配列。
	//getlineで文字列の最後まで','で区切られた文字列を変換する。
	//getline()は切り出せるものが無くなると'false'になる。
	while (getline(iss, str, ',')) {
		//文字列から数値への変換(stoi関数)では、数値以外の文字列を変換しようとした場合、
		//「例外」が発生するので「try～catch」で処理している。
		try {
			int num = stoi(str);	//数字文字列を数字に変換
			p_result->push_back(num);	//末尾に追加
		}
		catch (const invalid_argument& e) {
			//例外：変換出来ない値だった
			p_result->push_back(0);	//強制的に(0)に変換する。
			//std::cerr << e.what();	//デバッグ用エラー出力
		}
		catch (const out_of_range& e) {
			//例外：範囲外の値だった
			p_result->push_back(0);	//強制的に(0)に変換する。
			//std::cerr << e.what();	//デバッグ用エラー出力
		}
	}
	return p_result;	//変換後の整数集合へのポインタを返す。
}	//conv_csv_line

//----------------------------------------------------------------
// CSVデータの読み込み
//	読み込んだデータはint型の可変長配列'p_vec'に格納される。
//	戻り値：読み込んで変換した要素数（int型の数）を返す。
//	　　　　読み込み失敗した場合は(-1)を返す。
int Csv::read(void) {
	if (this->file_path == nullptr) {
		return -1;	//ファイル名が無い
	}
	if (this->p_vec != nullptr) {
		return (int)this->size();	//既に読み込み済みなので要素数を返す
	}
	//指定されたファイルから入力ファイルストリームを開く
	ifstream	ifs(this->file_path);
	if (!ifs) {
		return -1;	//失敗
	}
	//整数の可変用配列(vector<int>)を作成
	this->p_vec = new vector<int>;	//作成
	string	line;	//１行分読み込む文字列
	//入力ファイルストリームからgetline()で最後の行まで１行づつ読み込む。
	//getline()はファイルの終わりなると'false'になる。
	while (getline(ifs, line)) {
		vector<int>* line_vec = conv_csv_line(line);	//１行を','区切りのデータとして、複数の整数値に変換
		p_vec->insert(p_vec->end(), line_vec->begin(), line_vec->end());	//変換した１行分を'p_vec'の末尾に追加
		delete line_vec;	//追加したので変換に使ったオブジェクトは削除
		line_vec = nullptr;	//念のため'nullptr'でクリア
	}
	ifs.close();	//入力ファイルストリームを閉じる
	return (int)this->size();	//変換した要素数を返す
}	//read

//----------------------------------------------------------------
//	2022 HAL Osaka
//----------------------------------------------------------------
