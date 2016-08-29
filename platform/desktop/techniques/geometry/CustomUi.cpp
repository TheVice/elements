
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

#define SLIDER_MODEL_COUNT 24

Desktop::SliderModel* CustomUi::GetSliderModel(int aSliderId, float aMin, float aMax)
{
	Desktop::SliderModel* sliderModel = nullptr;
	static std::bitset<SLIDER_MODEL_COUNT> sliderModelsSet;

	if (aSliderId > (SLIDER_MODEL_COUNT - 1) || sliderModelsSet.test(aSliderId))
	{
		return sliderModel;
	}

	float* modelValue = nullptr;

	switch (aSliderId)
	{
		case 0:
			modelValue = &mMatrixMvp[0][0];
			break;

		case 1:
			modelValue = &mMatrixMvp[0][1];
			break;

		case 2:
			modelValue = &mMatrixMvp[0][2];
			break;

		case 3:
			modelValue = &mMatrixMvp[1][0];
			break;

		case 4:
			modelValue = &mMatrixMvp[1][1];
			break;

		case 5:
			modelValue = &mMatrixMvp[1][2];
			break;

		case 6:
			modelValue = &mMatrixMvp[2][0];
			break;

		case 7:
			modelValue = &mMatrixMvp[2][1];
			break;

		case 8:
			modelValue = &mMatrixMvp[2][2];
			break;

		case 9:
			modelValue = &mMatrixMvp[3][0];
			break;

		case 10:
			modelValue = &mMatrixMvp[3][1];
			break;

		case 11:
			modelValue = &mMatrixMvp[3][2];
			break;

		case 12:
			modelValue = &mMatrixNormal[0][0];
			break;

		case 13:
			modelValue = &mMatrixNormal[0][1];
			break;

		case 14:
			modelValue = &mMatrixNormal[1][0];
			break;

		case 15:
			modelValue = &mMatrixNormal[1][1];
			break;

		case 16:
			modelValue = &mMatrixNormal[2][0];
			break;

		case 17:
			modelValue = &mMatrixNormal[2][1];
			break;

		case 18:
			modelValue = &mVertices[0].a_vertex_normal.x;
			break;

		default:
			return sliderModel;
	}

	sliderModel = new CustomSliderModel(*modelValue, aMin, aMax);
	sliderModelsSet.set(aSliderId);
	return sliderModel;
}

}
