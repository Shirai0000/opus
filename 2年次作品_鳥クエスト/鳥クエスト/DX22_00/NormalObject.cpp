#include "NormalObject.h"

NormalObject::NormalObject()
{
	// �r���{�[�h�Ȃ����f��
	mModel = new Model();
	mHit = new HitSphere(mModel->mPos, 1.0f);
}
