
#include "SliderModel.h"

namespace Desktop
{

const float SliderModel::sDefaultMin = 0.0f;
const float SliderModel::sDefaultMax = 1.0f;

SliderModel::SliderModel() :
	slider_model(),
	mMin(sDefaultMin),
	mDelta(sDefaultMax - sDefaultMin),
	mValue(sDefaultMin)
{
	assert(sDefaultMin < sDefaultMin);
}

SliderModel::SliderModel(float aMin, float aMax) :
	slider_model(),
	mMin(aMin),
	mDelta(aMax - aMin),
	mValue(sDefaultMin)
{
	assert(aMin < aMax);
}

float SliderModel::get_value() const
{
	return mValue;
}

void SliderModel::set_value(float aValue)
{
	mValue = aValue;
}

float SliderModel::getRealValue() const
{
	return mMin + (mDelta * mValue) / sDefaultMax;
}

void SliderModel::setRealValue(float aValue)
{
	mValue = (sDefaultMax * (aValue - mMin)) / mDelta;
}

}
