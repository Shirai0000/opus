#include "HitSphere.h"

bool HitSphere::IsHit(HitSphere * pOther)
{
	// active‚ªfalse‚È‚ç“–‚½‚è”»’è‚ð‘f’Ê‚è‚³‚¹‚é
	if (active == false || pOther->active == false)
	{
		return false;
	}

	float x = pOther->mCenter.x - mCenter.x;
	float y = pOther->mCenter.y - mCenter.y;
	float z = pOther->mCenter.z - mCenter.z;
	float ctc = x * x + y * y + z * z; // center to center
	float h1_h2 = pOther->mHankei + mHankei;
	return ctc < h1_h2 * h1_h2;
}

bool HitSphere::SquareHit(HitSphere * pOther)
{
	bool kari = false;
	// active‚ªfalse‚È‚ç“–‚½‚è”»’è‚ð‘f’Ê‚è‚³‚¹‚é
	if (active == false || pOther->active == false)
	{
		return false;
	}
	if ((this->mCenter.y - this->high <= pOther->mCenter.y + pOther->high)&&(this->mCenter.y + this->high >= pOther->mCenter.y - pOther->high))
	{
		if ((this->mCenter.x - this->width <= pOther->mCenter.x + pOther->width) && (this->mCenter.x + this->width >= pOther->mCenter.x - pOther->width) && (this->mCenter.z - this->width <= pOther->mCenter.z + pOther->width) && (this->mCenter.z + this->width >= pOther->mCenter.z - pOther->width))
		{
			kari = true;
		}
	}
	return kari;
}

HitSphere::HitSphere(DirectX::XMFLOAT3 & center, float hankei)
	: mCenter(center)
{
	mHankei = hankei;
}
