#pragma once
#include "BillboardObject.h"

// �����G�t�F�N�g
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

