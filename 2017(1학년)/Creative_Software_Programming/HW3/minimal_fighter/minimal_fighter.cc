#include "minimal_fighter.h"

MinimalFighter::MinimalFighter()
{
	mHp = 0;
	mPower = 0;
	mStatus = Invalid;
}

MinimalFighter::MinimalFighter(int _hp, int _power)
{
	mHp = _hp;
	mPower = _power;
	if (mHp <= 0) {
		mStatus = Dead;
	}
	else {
		mStatus = Alive;
	}
}

int MinimalFighter::hp() const
{
	return mHp;
}

int MinimalFighter::power() const
{
	return mPower;
}

FighterStatus MinimalFighter::status() const
{
	return mStatus;
}

void MinimalFighter::setHp(int _hp)
{
	mHp = _hp;
}

void MinimalFighter::hit(MinimalFighter * _enemy)
{
	setHp(mHp-_enemy->mPower);
	_enemy->setHp(_enemy->mHp - mPower);
	if (mHp <= 0) {
		mStatus = Dead;
	}
	if (_enemy->mHp <= 0) {
		_enemy->mStatus = Dead;
	}
}

void MinimalFighter::attack(MinimalFighter * _target)
{
	_target->setHp(_target->mHp - mPower);
	mPower = 0;

	if (mHp <= 0) {
		mStatus = Dead;
	}
	if (_target->mHp <= 0) {
		_target->mStatus = Dead;
	}
}

void MinimalFighter::fight(MinimalFighter * _enemy)
{
	while (1) {
		setHp(mHp - _enemy->mPower);
		_enemy->setHp(_enemy->mHp - mPower);
		if (mHp <= 0) {
			mStatus = Dead;
		}
		if (_enemy->mHp <= 0) {
			_enemy->mStatus = Dead;
		}
		if (_enemy->mHp <= 0 || mHp <= 0)
			break;
	}
}