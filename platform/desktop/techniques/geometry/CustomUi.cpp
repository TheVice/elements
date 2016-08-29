
#include "CustomUi.h"
#include "ui/controls/button.h"
#include "ui/controls/label.h"
#include "ui/controls/panel.h"
#include "SliderModel.h"
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

#define SLIDER_MODEL_COUNT			29

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
}),
mSliderModels(SLIDER_MODEL_COUNT),
mIsRestoreNeed(false)
{
}

CustomUi::~CustomUi()
{
}

#define RESTORE_BUTTON				"RestoreButton"

#define MATRIX_MVP_00_SLIDER		0
#define MATRIX_MVP_01_SLIDER		1
#define MATRIX_MVP_02_SLIDER		2
#define MATRIX_MVP_10_SLIDER		3
#define MATRIX_MVP_11_SLIDER		4
#define MATRIX_MVP_12_SLIDER		5
#define MATRIX_MVP_20_SLIDER		6
#define MATRIX_MVP_21_SLIDER		7
#define MATRIX_MVP_22_SLIDER		8
#define MATRIX_MVP_30_SLIDER		9
#define MATRIX_MVP_31_SLIDER		10
#define MATRIX_MVP_32_SLIDER		11

#define MATRIX_NORMAL_00_SLIDER 	12
#define MATRIX_NORMAL_01_SLIDER		13
#define MATRIX_NORMAL_10_SLIDER		14
#define MATRIX_NORMAL_11_SLIDER		15
#define MATRIX_NORMAL_20_SLIDER		16
#define MATRIX_NORMAL_21_SLIDER		17

#define VEC_POS_LT_X_SLIDER			18
#define VEC_POS_LT_Y_SLIDER			19
#define VEC_POS_LT_Z_SLIDER			20

#define VEC_NORMAL_LT_X_SLIDER		21
#define VEC_NORMAL_LT_Y_SLIDER		22
#define VEC_NORMAL_LT_Z_SLIDER		23

#define VEC_TANGENT_LT_X_SLIDER		24
#define VEC_TANGENT_LT_Y_SLIDER		25
#define VEC_TANGENT_LT_Z_SLIDER		26

#define VEC_UV_LT_X_SLIDER			27
#define VEC_UV_LT_Y_SLIDER			28

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

#define VEC_POS_LT_X_LABEL "LT_Panel/mPosLT_x_Label"
#define VEC_POS_LT_Y_LABEL "LT_Panel/mPosLT_y_Label"
#define VEC_POS_LT_Z_LABEL "LT_Panel/mPosLT_z_Label"

#define VEC_NORMAL_LT_X_LABEL "LT_Panel/mNormalLT_x_Label"
#define VEC_NORMAL_LT_Y_LABEL "LT_Panel/mNormalLT_y_Label"
#define VEC_NORMAL_LT_Z_LABEL "LT_Panel/mNormalLT_z_Label"

#define VEC_TANGENT_LT_X_LABEL "LT_Panel/mTangentLT_x_Label"
#define VEC_TANGENT_LT_Y_LABEL "LT_Panel/mTangentLT_y_Label"
#define VEC_TANGENT_LT_Z_LABEL "LT_Panel/mTangentLT_z_Label"

#define VEC_UV_LT_X_LABEL "LT_Panel/mUvLT_x_Label"
#define VEC_UV_LT_Y_LABEL "LT_Panel/mUvLT_y_Label"

#define IS_CONTROL_EXIST(CONTROL_NAME)														\
	if (!mControls.count(CONTROL_NAME))														\
	{																						\
		throw std::runtime_error(std::string(CONTROL_NAME) + std::string(" not exist"));	\
	}

void CustomUi::Initialize()
{
	Ui::Initialize();
	//
	IS_CONTROL_EXIST(RESTORE_BUTTON)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[RESTORE_BUTTON].lock()))
	{
		directButton->set_click([this]
		{
			this->mIsRestoreNeed = !this->mIsRestoreNeed;
		});
	}

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
	IS_CONTROL_EXIST(VEC_POS_LT_X_LABEL)
	IS_CONTROL_EXIST(VEC_POS_LT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_POS_LT_Z_LABEL)
	//
	IS_CONTROL_EXIST(VEC_NORMAL_LT_X_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_LT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_LT_Z_LABEL)
	//
	IS_CONTROL_EXIST(VEC_TANGENT_LT_X_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LT_Z_LABEL)
	//
	IS_CONTROL_EXIST(VEC_UV_LT_X_LABEL)
	IS_CONTROL_EXIST(VEC_UV_LT_Y_LABEL)
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
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VEC_POS_LT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VEC_POS_LT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VEC_POS_LT_Z_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.x, VEC_NORMAL_LT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.y, VEC_NORMAL_LT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.z, VEC_NORMAL_LT_Z_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.x, VEC_TANGENT_LT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.y, VEC_TANGENT_LT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.z, VEC_TANGENT_LT_Z_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VEC_UV_LT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VEC_UV_LT_Y_LABEL)
}

#define SET_REAL_SLIDER_VALUE(VALUE, SLIDER)	\
	mSliderModels[SLIDER]->setRealValue(VALUE);

void CustomUi::SetMatrixMvp(const glm::mat4& aMatrixMvp)
{
	mMatrixMvp = aMatrixMvp;
	//
	SET_REAL_SLIDER_VALUE(mMatrixMvp[0][0], MATRIX_MVP_00_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[0][1], MATRIX_MVP_01_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[0][2], MATRIX_MVP_02_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[1][0], MATRIX_MVP_10_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[1][1], MATRIX_MVP_11_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[1][2], MATRIX_MVP_12_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[2][0], MATRIX_MVP_20_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[2][1], MATRIX_MVP_21_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[2][2], MATRIX_MVP_22_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[3][0], MATRIX_MVP_30_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[3][1], MATRIX_MVP_31_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixMvp[3][2], MATRIX_MVP_32_SLIDER)
	//
	mIsRestoreNeed = false;
}

const glm::mat4& CustomUi::GetMatrixMvp() const
{
	return mMatrixMvp;
}

void CustomUi::SetMatrixNormal(const glm::mat3& aMatrixNormal)
{
	mMatrixNormal = aMatrixNormal;
	//
	SET_REAL_SLIDER_VALUE(mMatrixNormal[0][0], MATRIX_NORMAL_00_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixNormal[0][1], MATRIX_NORMAL_01_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixNormal[1][0], MATRIX_NORMAL_10_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixNormal[1][1], MATRIX_NORMAL_11_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixNormal[2][0], MATRIX_NORMAL_20_SLIDER)
	SET_REAL_SLIDER_VALUE(mMatrixNormal[1][1], MATRIX_NORMAL_21_SLIDER)
	//
	mIsRestoreNeed = false;
}

const glm::mat3& CustomUi::GetMatrixNormal() const
{
	return mMatrixNormal;
}

void CustomUi::SetVertices(const std::vector<VertexStructure>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_pos.x, VEC_POS_LT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_pos.y, VEC_POS_LT_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_pos.z, VEC_POS_LT_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_normal.x, VEC_NORMAL_LT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_normal.y, VEC_NORMAL_LT_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_normal.z, VEC_NORMAL_LT_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_tangent.x, VEC_TANGENT_LT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_tangent.y, VEC_TANGENT_LT_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_tangent.z, VEC_TANGENT_LT_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_uv.x, VEC_UV_LT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_uv.y, VEC_UV_LT_Y_SLIDER)
	//
	mIsRestoreNeed = false;
}

const std::vector<VertexStructure>& CustomUi::GetVertices() const
{
	return mVertices;
}

bool CustomUi::IsNeedRestrore() const
{
	return mIsRestoreNeed;
}

Desktop::SliderModel* CustomUi::GetSliderModel(int aSliderId, float aMin, float aMax)
{
	Desktop::SliderModel* sliderModel = nullptr;

	if (aSliderId > (SLIDER_MODEL_COUNT - 1) || mSliderModels[aSliderId])
	{
		return sliderModel;
	}

	float* modelValue = nullptr;

	switch (aSliderId)
	{
		case MATRIX_MVP_00_SLIDER:
			modelValue = &mMatrixMvp[0][0];
			break;

		case MATRIX_MVP_01_SLIDER:
			modelValue = &mMatrixMvp[0][1];
			break;

		case MATRIX_MVP_02_SLIDER:
			modelValue = &mMatrixMvp[0][2];
			break;

		case MATRIX_MVP_10_SLIDER:
			modelValue = &mMatrixMvp[1][0];
			break;

		case MATRIX_MVP_11_SLIDER:
			modelValue = &mMatrixMvp[1][1];
			break;

		case MATRIX_MVP_12_SLIDER:
			modelValue = &mMatrixMvp[1][2];
			break;

		case MATRIX_MVP_20_SLIDER:
			modelValue = &mMatrixMvp[2][0];
			break;

		case MATRIX_MVP_21_SLIDER:
			modelValue = &mMatrixMvp[2][1];
			break;

		case MATRIX_MVP_22_SLIDER:
			modelValue = &mMatrixMvp[2][2];
			break;

		case MATRIX_MVP_30_SLIDER:
			modelValue = &mMatrixMvp[3][0];
			break;

		case MATRIX_MVP_31_SLIDER:
			modelValue = &mMatrixMvp[3][1];
			break;

		case MATRIX_MVP_32_SLIDER:
			modelValue = &mMatrixMvp[3][2];
			break;

		case MATRIX_NORMAL_00_SLIDER :
			modelValue = &mMatrixNormal[0][0];
			break;

		case MATRIX_NORMAL_01_SLIDER:
			modelValue = &mMatrixNormal[0][1];
			break;

		case MATRIX_NORMAL_10_SLIDER:
			modelValue = &mMatrixNormal[1][0];
			break;

		case MATRIX_NORMAL_11_SLIDER:
			modelValue = &mMatrixNormal[1][1];
			break;

		case MATRIX_NORMAL_20_SLIDER:
			modelValue = &mMatrixNormal[2][0];
			break;

		case MATRIX_NORMAL_21_SLIDER:
			modelValue = &mMatrixNormal[2][1];
			break;

		case VEC_POS_LT_X_SLIDER:
			modelValue = &mVertices[0].a_vertex_pos.x;
			break;

		case VEC_POS_LT_Y_SLIDER:
			modelValue = &mVertices[0].a_vertex_pos.y;
			break;

		case VEC_POS_LT_Z_SLIDER:
			modelValue = &mVertices[0].a_vertex_pos.z;
			break;

		case VEC_NORMAL_LT_X_SLIDER:
			modelValue = &mVertices[0].a_vertex_normal.x;
			break;

		case VEC_NORMAL_LT_Y_SLIDER	:
			modelValue = &mVertices[0].a_vertex_normal.y;
			break;

		case VEC_NORMAL_LT_Z_SLIDER:
			modelValue = &mVertices[0].a_vertex_normal.z;
			break;

		case VEC_TANGENT_LT_X_SLIDER:
			modelValue = &mVertices[0].a_vertex_tangent.x;
			break;

		case VEC_TANGENT_LT_Y_SLIDER:
			modelValue = &mVertices[0].a_vertex_tangent.y;
			break;

		case VEC_TANGENT_LT_Z_SLIDER:
			modelValue = &mVertices[0].a_vertex_tangent.z;
			break;

		case VEC_UV_LT_X_SLIDER:
			modelValue = &mVertices[0].a_vertex_uv.x;
			break;

		case VEC_UV_LT_Y_SLIDER:
			modelValue = &mVertices[0].a_vertex_uv.y;
			break;

		default:
			return sliderModel;
	}

	sliderModel = new CustomSliderModel(*modelValue, aMin, aMax);
	mSliderModels[aSliderId] = sliderModel;
	return sliderModel;
}

}
