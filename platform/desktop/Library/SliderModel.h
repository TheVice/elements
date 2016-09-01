#ifndef _SLIDER_MODEL_H_
#define _SLIDER_MODEL_H_

#include "ui/controls/slider.h"

namespace Library
{

class SliderModel : public eps::ui::slider_model
{
public:
	SliderModel();
	SliderModel(float aMin, float aMax);

	float get_value() const override;
	void set_value(float aValue) override;

	float getRealValue() const;
	void setRealValue(float aValue);

private:
	const float mMin;
	const float mDelta;
	float mValue;

private:
	static const float sDefaultMin;
	static const float sDefaultMax;
};

}

#endif
