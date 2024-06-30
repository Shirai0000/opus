#pragma once
#include "BillboardObject.h"

// 爆発エフェクト
class Explosion :
	public BillboardObject
{

public:
	Explosion(int,int);
	void Update() override;

	bool IsFinished()
	{
		return mFinished;
	}
	int tateFrame;
	int yokoFrame;

private:
	int mTime;

	bool mFinished = false;

	void SettateFrame(int);
	void SetyokoFrame(int);
};

