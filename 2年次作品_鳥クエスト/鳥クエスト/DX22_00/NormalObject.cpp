#include "NormalObject.h"

NormalObject::NormalObject()
{
	// ビルボードなしモデル
	mModel = new Model();
	mHit = new HitSphere(mModel->mPos, 1.0f);
}
