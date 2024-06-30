#include "Explosion.h"

extern DWORD gDeltaTime;

Explosion::Explosion(int _x, int _y)
{
	SettateFrame(_x);
	SetyokoFrame(_y);
}

void Explosion::Update()
{
	if (mFinished)
		return;

	const float speed = 0.009f;
	const int maxFrame = tateFrame * yokoFrame;
	const float u = 1.0f / tateFrame;
	const float v = 1.0f / yokoFrame;

	mTime += gDeltaTime;

	int time = static_cast<int>(mTime * speed);

	if (time >= maxFrame)
	{
		//time = mTime = 0;
		mFinished = true;
	}

	Model* pModel = GetModel();
	pModel->mUvOffset.x = static_cast<float>(time % yokoFrame) * u;
	pModel->mUvOffset.y = static_cast<float>(time / yokoFrame) * v;

	BillboardObject::Update();
}

void Explosion::SettateFrame(int x)
{
	tateFrame = x;
}

void Explosion::SetyokoFrame(int y)
{
	yokoFrame = y;
}
