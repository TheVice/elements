
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
	mMatrixNormal(),
	mVertices(
{
	VertexStructure(),
					VertexStructure(),
					VertexStructure(),
					VertexStructure()
})
{
}

CustomUi::~CustomUi()
{
}

#define MATRIX_MVP_00_LABEL "MatrixMvp_Panel/mMatrixMvp00_Label"
#define MATRIX_MVP_01_LABEL "MatrixMvp_Panel/mMatrixMvp01_Label"
#define MATRIX_MVP_02_LABEL "MatrixMvp_Panel/mMatrixMvp02_Label"
#define MATRIX_MVP_10_LABEL "MatrixMvp_Panel/mMatrixMvp10_Label"
#define MATRIX_MVP_11_LABEL "MatrixMvp_Panel/mMatrixMvp11_Label"
#define MATRIX_MVP_12_LABEL "MatrixMvp_Panel/mMatrixMvp12_Label"
#define MATRIX_MVP_20_LABEL "MatrixMvp_Panel/mMatrixMvp20_Label"
#define MATRIX_MVP_21_LABEL "MatrixMvp_Panel/mMatrixMvp21_Label"
#define MATRIX_MVP_22_LABEL "MatrixMvp_Panel/mMatrixMvp22_Label"
#define MATRIX_MVP_30_LABEL "MatrixMvp_Panel/mMatrixMvp30_Label"
#define MATRIX_MVP_31_LABEL "MatrixMvp_Panel/mMatrixMvp31_Label"
#define MATRIX_MVP_32_LABEL "MatrixMvp_Panel/mMatrixMvp32_Label"
#define MATRIX_NORMAL_00_LABEL "mMatrixNormal_Panel/mMatrixNormal00_Label"
#define MATRIX_NORMAL_01_LABEL "mMatrixNormal_Panel/mMatrixNormal01_Label"
#define MATRIX_NORMAL_10_LABEL "mMatrixNormal_Panel/mMatrixNormal10_Label"
#define MATRIX_NORMAL_11_LABEL "mMatrixNormal_Panel/mMatrixNormal11_Label"
#define MATRIX_NORMAL_20_LABEL "mMatrixNormal_Panel/mMatrixNormal20_Label"
#define MATRIX_NORMAL_21_LABEL "mMatrixNormal_Panel/mMatrixNormal21_Label"

#define IS_CONTROL_EXIST(CONTROL_NAME)														\
	if (!mControls.count(CONTROL_NAME))														\
	{																						\
		throw std::runtime_error(std::string(CONTROL_NAME) + std::string(" not exist"));	\
	}

void CustomUi::Initialize()
{
	Ui::Initialize();
	//
	IS_CONTROL_EXIST(MATRIX_MVP_00_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_01_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_02_LABEL)
	//
	IS_CONTROL_EXIST(MATRIX_MVP_10_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_11_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_12_LABEL)
	//
	IS_CONTROL_EXIST(MATRIX_MVP_20_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_21_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_22_LABEL)
	//
	IS_CONTROL_EXIST(MATRIX_MVP_30_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_31_LABEL)
	IS_CONTROL_EXIST(MATRIX_MVP_32_LABEL)
	//
	IS_CONTROL_EXIST(MATRIX_NORMAL_00_LABEL)
	IS_CONTROL_EXIST(MATRIX_NORMAL_01_LABEL)
	//
	IS_CONTROL_EXIST(MATRIX_NORMAL_10_LABEL)
	IS_CONTROL_EXIST(MATRIX_NORMAL_11_LABEL)
	//
	IS_CONTROL_EXIST(MATRIX_NORMAL_20_LABEL)
	IS_CONTROL_EXIST(MATRIX_NORMAL_21_LABEL)
	//
	IS_CONTROL_EXIST("mNormalLT_x_Label")
}

#define DISPLAY_VALUE_AT_LABEL(VALUE, LABEL)													\
	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls[LABEL].lock()))	\
	{																							\
		std::ostringstream message;																\
		message << std::setprecision(2) << VALUE;												\
		directLabel->set_text(message.str());													\
	}

void CustomUi::Update(const Library::GameTime& aGameTime)
{
	Ui::Update(aGameTime);
	//
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[0][0], MATRIX_MVP_00_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[0][1], MATRIX_MVP_01_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[0][2], MATRIX_MVP_02_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[1][0], MATRIX_MVP_10_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[1][1], MATRIX_MVP_11_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[1][2], MATRIX_MVP_12_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[2][0], MATRIX_MVP_20_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[2][1], MATRIX_MVP_21_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[2][2], MATRIX_MVP_22_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[3][0], MATRIX_MVP_30_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[3][1], MATRIX_MVP_31_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixMvp[3][2], MATRIX_MVP_32_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mMatrixNormal[0][0], MATRIX_NORMAL_00_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixNormal[0][1], MATRIX_NORMAL_01_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mMatrixNormal[1][0], MATRIX_NORMAL_10_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixNormal[1][1], MATRIX_NORMAL_11_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mMatrixNormal[2][0], MATRIX_NORMAL_20_LABEL)
	DISPLAY_VALUE_AT_LABEL(mMatrixNormal[2][1], MATRIX_NORMAL_21_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.x, "mNormalLT_x_Label")
}

void CustomUi::SetMatrixMvp(const glm::mat4& aMatrixMvp)
{
	mMatrixMvp = aMatrixMvp;
}

const glm::mat4& CustomUi::GetMatrixMvp() const
{
	return mMatrixMvp;
}

void CustomUi::SetMatrixNormal(const glm::mat3& aMatrixNormal)
{
	mMatrixNormal = aMatrixNormal;
}

const glm::mat3& CustomUi::GetMatrixNormal() const
{
	return mMatrixNormal;
}

void CustomUi::_setNormalLT_x(float aValue)
{
	mVertices[0].a_vertex_normal.x = aValue;
}

float CustomUi::_getNormalLT_x()
{
	return mVertices[0].a_vertex_normal.x;
}

Desktop::SliderModel* CustomUi::GetSliderModel(int aSliderId, float aMin, float aMax)
{
	Desktop::SliderModel* sliderModel = nullptr;
	static std::bitset<12> mvpSet;
	static std::bitset<6> normalSet;
	static std::bitset<6> topLeftVertexSet;

	if (aSliderId < static_cast<int>(mvpSet.size()))
	{
		if (mvpSet.test(aSliderId))
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
	}
	else if (aSliderId < static_cast<int>(mvpSet.size() + normalSet.size()))
	{
		const auto localSliderId = aSliderId - mvpSet.size();

		if (normalSet.test(localSliderId))
		{
			return sliderModel;
		}

		switch (localSliderId)
		{
			case 0:
				sliderModel = new CustomSliderModel(mMatrixNormal[0][0], aMin, aMax);
				break;

			case 1:
				sliderModel = new CustomSliderModel(mMatrixNormal[0][1], aMin, aMax);
				break;

			case 2:
				sliderModel = new CustomSliderModel(mMatrixNormal[1][0], aMin, aMax);
				break;

			case 3:
				sliderModel = new CustomSliderModel(mMatrixNormal[1][1], aMin, aMax);
				break;

			case 4:
				sliderModel = new CustomSliderModel(mMatrixNormal[2][0], aMin, aMax);
				break;

			case 5:
				sliderModel = new CustomSliderModel(mMatrixNormal[2][1], aMin, aMax);
				break;

			default:
				return sliderModel;
		}

		normalSet.set(localSliderId);
	}
	else if (aSliderId < static_cast<int>(mvpSet.size() + normalSet.size() + topLeftVertexSet.size()))
	{
		const auto localSliderId = aSliderId - mvpSet.size() - normalSet.size();

		if (topLeftVertexSet.test(localSliderId))
		{
			return sliderModel;
		}

		switch (localSliderId)
		{
			case 0:
				sliderModel = new CustomSliderModel(mVertices[0].a_vertex_normal.x, aMin, aMax);
				break;

			default:
				return sliderModel;
		}

		topLeftVertexSet.set(localSliderId);
	}

	return sliderModel;
}

}
