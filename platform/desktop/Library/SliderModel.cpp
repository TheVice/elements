
#include "SliderModel.h"
#include <algorithm>
#include <limits>

namespace Library
{

const float SliderModel::sDefaultMin = 0.0f;
const float SliderModel::sDefaultMax = 1.0f;

SliderModel::SliderModel() :
	slider_model(),
	mMin(sDefaultMin),
	mDelta(sDefaultMax - sDefaultMin),
	mValue(sDefaultMin)
{
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

ValueSliderModel::ValueSliderModel(float& aModelValue) :
	SliderModel(),
	mModelValue(aModelValue)
{
	setRealValue(mModelValue);
}

ValueSliderModel::ValueSliderModel(float& aModelValue, float aMin, float aMax) :
	SliderModel(aMin, aMax),
	mModelValue(aModelValue)
{
	setRealValue(mModelValue);
}

float ValueSliderModel::get_value() const
{
	const auto value = getRealValue();

	if (std::abs(value - mModelValue) > (100 * std::numeric_limits<float>::epsilon()))
	{
		mModelValue = value;
	}

	return SliderModel::get_value();
}

}
