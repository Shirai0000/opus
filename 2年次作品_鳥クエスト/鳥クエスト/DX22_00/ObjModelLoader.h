#pragma once

#include "ModelData.h"
#include <vector>

/*
	3Dモデルデータ「OBJファイル」読み込みサンプル

	制限：
	�@OBJファイル内のグループが１つにまとまっていること
	�AOBJファイル内の面情報（face）が三角形のみで構成されていること
	�Bマテリアル情報（.mtlファイル）は読み込まない
*/

class ObjModelLoader
{

public:
	// OBJファイルとテクスチャを読み込んでModelDataとして返す
	ModelData Load(const char* pObjFileName, const wchar_t* pTexFileName);

private:
	void FinSkip();
	void FinVertex();
	void FinNormal();
	void FinUv();
	void FinFace();

	struct F3 {
		float x, y, z;
	};

	struct F2 {
		float x, y;
	};

	std::vector<F3> mPositionList;
	std::vector<F3> mNormalList;
	std::vector<F2> mUvList;
	std::vector<ModelVertex> mVertexList;

	FILE* mFp;

};

