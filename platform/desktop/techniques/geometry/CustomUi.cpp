
#include "CustomUi.h"
#include "ui/controls/button.h"
#include "ui/controls/label.h"
#include "ui/controls/panel.h"
#include "SliderModel.h"
#include <bitset>
#include <sstream>
#include <iomanip>

class CustomSliderModel : public Desktop::SliderModel
{
private:
	static const float sEpsilon;
	float& mModelValue;

public:
	CustomSliderModel(float& aModelValue) :
		SliderModel(),
		mModelValue(aModelValue)
	{
		setRealValue(mModelValue);
	}

	CustomSliderModel(float& aModelValue, float aMin, float aMax) :
		SliderModel(aMin, aMax),
		mModelValue(aModelValue)
	{
		setRealValue(mModelValue);
	}

	float get_value() const override
	{
		const float value = getRealValue();

		if (std::abs(value - mModelValue) > sEpsilon)
		{
			mModelValue = value;
		}

		return SliderModel::get_value();
	}
};

const float CustomSliderModel::sEpsilon = 100 * std::numeric_limits<float>::epsilon();

namespace Rendering
{
RTTI_DEFINITIONS(CustomUi)

CustomUi::CustomUi(Library::Game& aGame, const std::string& aAssetPath) :
	Ui(aGame, aAssetPath),
	mMatrixMvp(),
	mMatrixNormal()
{
}

CustomUi::~CustomUi()
{
}

#define IS_CONTROL_EXIST(CONTROL_NAME)	\
	if (!mControls.count(CONTROL_NAME))	\
	{																\
		throw std::runtime_error(std::string(CONTROL_NAME) + std::string(" not exist"));	\
	}

void CustomUi::Initialize()
{
	Ui::Initialize();
	//
	IS_CONTROL_EXIST("mMatrixMvp00_Label")
	IS_CONTROL_EXIST("mMatrixMvp01_Label")
	IS_CONTROL_EXIST("mMatrixMvp02_Label")
	//
	IS_CONTROL_EXIST("mMatrixMvp10_Label")
	IS_CONTROL_EXIST("mMatrixMvp11_Label")
	IS_CONTROL_EXIST("mMatrixMvp12_Label")
	//
	IS_CONTROL_EXIST("mMatrixMvp20_Label")
	IS_CONTROL_EXIST("mMatrixMvp21_Label")
	IS_CONTROL_EXIST("mMatrixMvp22_Label")
	//
	IS_CONTROL_EXIST("mMatrixMvp30_Label")
	IS_CONTROL_EXIST("mMatrixMvp31_Label")
	IS_CONTROL_EXIST("mMatrixMvp32_Label")
}

void CustomUi::Update(const Library::GameTime& aGameTime)
{
	Ui::Update(aGameTime);

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp00_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[0][0];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp01_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[0][1];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp02_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[0][2];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp10_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[1][0];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp11_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[1][1];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp12_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[1][2];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp20_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[2][0];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp21_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[2][1];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp22_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[2][2];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp30_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[3][0];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp31_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[3][1];
		directLabel->set_text(message.str());
	}

	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls["mMatrixMvp32_Label"].lock()))
	{
		std::ostringstream message;
		message << std::setprecision(2) << mMatrixMvp[3][2];
		directLabel->set_text(message.str());
	}
}

void CustomUi::SetMatrixMvp(const glm::mat4& aMatrixMvp)
{
	mMatrixMvp = aMatrixMvp;
}

const glm::mat4& CustomUi::GetMatrixMvp() const
{
	return mMatrixMvp;
}

Desktop::SliderModel* CustomUi::GetSliderModel(int aSliderId, float aMin, float aMax)
{
	Desktop::SliderModel* sliderModel = nullptr;
	static std::bitset<12> mvpSet;

	if (aSliderId > static_cast<int>(mvpSet.size() - 1) || mvpSet.test(aSliderId))
	{
		return sliderModel;
	}

	switch (aSliderId)
	{
		case 0:
			sliderModel = new CustomSliderModel(mMatrixMvp[0][0], aMin, aMax);
			break;

		case 1:
			sliderModel = new CustomSliderModel(mMatrixMvp[0][1], aMin, aMax);
			break;

		case 2:
			sliderModel = new CustomSliderModel(mMatrixMvp[0][2], aMin, aMax);
			break;

		case 3:
			sliderModel = new CustomSliderModel(mMatrixMvp[1][0], aMin, aMax);
			break;

		case 4:
			sliderModel = new CustomSliderModel(mMatrixMvp[1][1], aMin, aMax);
			break;

		case 5:
			sliderModel = new CustomSliderModel(mMatrixMvp[1][2], aMin, aMax);
			break;

		case 6:
			sliderModel = new CustomSliderModel(mMatrixMvp[2][0], aMin, aMax);
			break;

		case 7:
			sliderModel = new CustomSliderModel(mMatrixMvp[2][1], aMin, aMax);
			break;

		case 8:
			sliderModel = new CustomSliderModel(mMatrixMvp[2][2], aMin, aMax);
			break;

		case 9:
			sliderModel = new CustomSliderModel(mMatrixMvp[3][0], aMin, aMax);
			break;

		case 10:
			sliderModel = new CustomSliderModel(mMatrixMvp[3][1], aMin, aMax);
			break;

		case 11:
			sliderModel = new CustomSliderModel(mMatrixMvp[3][2], aMin, aMax);
			break;

		default:
			return sliderModel;
	}

	mvpSet.set(aSliderId);
	//
	return sliderModel;
}

}
