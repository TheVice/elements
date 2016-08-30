
#include "CustomUi.h"
#include "ui/controls/button.h"
#include "ui/controls/label.h"
#include "ui/controls/panel.h"
#include "SliderModel.h"
#include "CustomControls.h"
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
}),
mSliderModels(SLIDER_MODEL_COUNT),
mIsRestoreNeed(false)
{
}

CustomUi::~CustomUi()
{
}

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
	//
	IS_CONTROL_EXIST(LEFT_TOP_BUTTON)
	IS_CONTROL_EXIST(RIGHT_TOP_BUTTON)
	IS_CONTROL_EXIST(LEFT_BOTTOM_BUTTON)
	IS_CONTROL_EXIST(RIGHT_BOTTOM_BUTTON)
	//
	IS_CONTROL_EXIST(LEFT_TOP_PANEL)
	IS_CONTROL_EXIST(RIGHT_TOP_PANEL)
	IS_CONTROL_EXIST(LEFT_BOTTOM_PANEL)
	IS_CONTROL_EXIST(RIGHT_BOTTOM_PANEL)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[RESTORE_BUTTON].lock()))
	{
		directButton->set_click([this]
		{
			this->mIsRestoreNeed = !this->mIsRestoreNeed;
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[LEFT_TOP_BUTTON].lock()))
	{
		directButton->set_click([this]
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_TOP_PANEL].lock()))
			{
				ltPanel->set_visible(!ltPanel->get_visible());
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_TOP_PANEL].lock()))
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_BOTTOM_PANEL].lock()))
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_BOTTOM_PANEL].lock()))
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[RIGHT_TOP_BUTTON].lock()))
	{
		directButton->set_click([this]
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_TOP_PANEL].lock()))
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_TOP_PANEL].lock()))
			{
				rtPanel->set_visible(!rtPanel->get_visible());
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_BOTTOM_PANEL].lock()))
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_BOTTOM_PANEL].lock()))
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[RIGHT_BOTTOM_BUTTON].lock()))
	{
		directButton->set_click([this]
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_TOP_PANEL].lock()))
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_TOP_PANEL].lock()))
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_BOTTOM_PANEL].lock()))
			{
				rbPanel->set_visible(!rbPanel->get_visible());
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_BOTTOM_PANEL].lock()))
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[LEFT_BOTTOM_BUTTON].lock()))
	{
		directButton->set_click([this]
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_TOP_PANEL].lock()))
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_TOP_PANEL].lock()))
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[RIGHT_BOTTOM_PANEL].lock()))
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[LEFT_BOTTOM_PANEL].lock()))
			{
				lbPanel->set_visible(!lbPanel->get_visible());
			}
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
	IS_CONTROL_EXIST(VEC_NORMAL_LT_X_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_LT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_LT_Z_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LT_X_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LT_Z_LABEL)
	IS_CONTROL_EXIST(VEC_UV_LT_X_LABEL)
	IS_CONTROL_EXIST(VEC_UV_LT_Y_LABEL)
	//
	IS_CONTROL_EXIST(VEC_POS_RT_X_LABEL)
	IS_CONTROL_EXIST(VEC_POS_RT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_POS_RT_Z_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_RT_X_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_RT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_RT_Z_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_RT_X_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_RT_Y_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_RT_Z_LABEL)
	IS_CONTROL_EXIST(VEC_UV_RT_X_LABEL)
	IS_CONTROL_EXIST(VEC_UV_RT_Y_LABEL)
	//
	IS_CONTROL_EXIST(VEC_POS_RB_X_LABEL)
	IS_CONTROL_EXIST(VEC_POS_RB_Y_LABEL)
	IS_CONTROL_EXIST(VEC_POS_RB_Z_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_RB_X_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_RB_Y_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_RB_Z_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_RB_X_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_RB_Y_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_RB_Z_LABEL)
	IS_CONTROL_EXIST(VEC_UV_RB_X_LABEL)
	IS_CONTROL_EXIST(VEC_UV_RB_Y_LABEL)
	//
	IS_CONTROL_EXIST(VEC_POS_LB_X_LABEL)
	IS_CONTROL_EXIST(VEC_POS_LB_Y_LABEL)
	IS_CONTROL_EXIST(VEC_POS_LB_Z_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_LB_X_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_LB_Y_LABEL)
	IS_CONTROL_EXIST(VEC_NORMAL_LB_Z_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LB_X_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LB_Y_LABEL)
	IS_CONTROL_EXIST(VEC_TANGENT_LB_Z_LABEL)
	IS_CONTROL_EXIST(VEC_UV_LB_X_LABEL)
	IS_CONTROL_EXIST(VEC_UV_LB_Y_LABEL)

	for (const auto& sliderModel : mSliderModels)
	{
		assert(sliderModel);
	}
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
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.x, VEC_NORMAL_LT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.y, VEC_NORMAL_LT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.z, VEC_NORMAL_LT_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.x, VEC_TANGENT_LT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.y, VEC_TANGENT_LT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.z, VEC_TANGENT_LT_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VEC_UV_LT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VEC_UV_LT_Y_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VEC_POS_RT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VEC_POS_RT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VEC_POS_RT_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.x, VEC_NORMAL_RT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.y, VEC_NORMAL_RT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.z, VEC_NORMAL_RT_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.x, VEC_TANGENT_RT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.y, VEC_TANGENT_RT_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.z, VEC_TANGENT_RT_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VEC_UV_RT_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VEC_UV_RT_Y_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VEC_POS_RB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VEC_POS_RB_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VEC_POS_RB_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.x, VEC_NORMAL_RB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.y, VEC_NORMAL_RB_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.z, VEC_NORMAL_RB_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.x, VEC_TANGENT_RB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.y, VEC_TANGENT_RB_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.z, VEC_TANGENT_RB_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VEC_UV_RB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VEC_UV_RB_Y_LABEL)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VEC_POS_LB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VEC_POS_LB_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VEC_POS_LB_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.x, VEC_NORMAL_LB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.y, VEC_NORMAL_LB_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.z, VEC_NORMAL_LB_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.x, VEC_TANGENT_LB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.y, VEC_TANGENT_LB_Y_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.z, VEC_TANGENT_LB_Z_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VEC_UV_LB_X_LABEL)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VEC_UV_LB_Y_LABEL)
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
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_pos.x, VEC_POS_RT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_pos.y, VEC_POS_RT_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_pos.z, VEC_POS_RT_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_normal.x, VEC_NORMAL_RT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_normal.y, VEC_NORMAL_RT_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_normal.z, VEC_NORMAL_RT_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_tangent.x, VEC_TANGENT_RT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_tangent.y, VEC_TANGENT_RT_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_tangent.z, VEC_TANGENT_RT_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_uv.x, VEC_UV_RT_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_uv.y, VEC_UV_RT_Y_SLIDER)
	//
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_pos.x, VEC_POS_RB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_pos.y, VEC_POS_RB_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_pos.z, VEC_POS_RB_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_normal.x, VEC_NORMAL_RB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_normal.y, VEC_NORMAL_RB_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_normal.z, VEC_NORMAL_RB_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_tangent.x, VEC_TANGENT_RB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_tangent.y, VEC_TANGENT_RB_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_tangent.z, VEC_TANGENT_RB_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_uv.x, VEC_UV_RB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_uv.y, VEC_UV_RB_Y_SLIDER)
	//
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_pos.x, VEC_POS_LB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_pos.y, VEC_POS_LB_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_pos.z, VEC_POS_LB_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_normal.x, VEC_NORMAL_LB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_normal.y, VEC_NORMAL_LB_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_normal.z, VEC_NORMAL_LB_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_tangent.x, VEC_TANGENT_LB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_tangent.y, VEC_TANGENT_LB_Y_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_tangent.z, VEC_TANGENT_LB_Z_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_uv.x, VEC_UV_LB_X_SLIDER)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_uv.y, VEC_UV_LB_Y_SLIDER)
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

		case VEC_POS_RT_X_SLIDER:
			modelValue = &mVertices[1].a_vertex_pos.x;
			break;

		case VEC_POS_RT_Y_SLIDER:
			modelValue = &mVertices[1].a_vertex_pos.y;
			break;

		case VEC_POS_RT_Z_SLIDER:
			modelValue = &mVertices[1].a_vertex_pos.z;
			break;

		case VEC_NORMAL_RT_X_SLIDER:
			modelValue = &mVertices[1].a_vertex_normal.x;
			break;

		case VEC_NORMAL_RT_Y_SLIDER	:
			modelValue = &mVertices[1].a_vertex_normal.y;
			break;

		case VEC_NORMAL_RT_Z_SLIDER:
			modelValue = &mVertices[1].a_vertex_normal.z;
			break;

		case VEC_TANGENT_RT_X_SLIDER:
			modelValue = &mVertices[1].a_vertex_tangent.x;
			break;

		case VEC_TANGENT_RT_Y_SLIDER:
			modelValue = &mVertices[1].a_vertex_tangent.y;
			break;

		case VEC_TANGENT_RT_Z_SLIDER:
			modelValue = &mVertices[1].a_vertex_tangent.z;
			break;

		case VEC_UV_RT_X_SLIDER:
			modelValue = &mVertices[1].a_vertex_uv.x;
			break;

		case VEC_UV_RT_Y_SLIDER:
			modelValue = &mVertices[1].a_vertex_uv.y;
			break;

		case VEC_POS_RB_X_SLIDER:
			modelValue = &mVertices[2].a_vertex_pos.x;
			break;

		case VEC_POS_RB_Y_SLIDER:
			modelValue = &mVertices[2].a_vertex_pos.y;
			break;

		case VEC_POS_RB_Z_SLIDER:
			modelValue = &mVertices[2].a_vertex_pos.z;
			break;

		case VEC_NORMAL_RB_X_SLIDER:
			modelValue = &mVertices[2].a_vertex_normal.x;
			break;

		case VEC_NORMAL_RB_Y_SLIDER	:
			modelValue = &mVertices[2].a_vertex_normal.y;
			break;

		case VEC_NORMAL_RB_Z_SLIDER:
			modelValue = &mVertices[2].a_vertex_normal.z;
			break;

		case VEC_TANGENT_RB_X_SLIDER:
			modelValue = &mVertices[2].a_vertex_tangent.x;
			break;

		case VEC_TANGENT_RB_Y_SLIDER:
			modelValue = &mVertices[2].a_vertex_tangent.y;
			break;

		case VEC_TANGENT_RB_Z_SLIDER:
			modelValue = &mVertices[2].a_vertex_tangent.z;
			break;

		case VEC_UV_RB_X_SLIDER:
			modelValue = &mVertices[2].a_vertex_uv.x;
			break;

		case VEC_UV_RB_Y_SLIDER:
			modelValue = &mVertices[2].a_vertex_uv.y;
			break;

		case VEC_POS_LB_X_SLIDER:
			modelValue = &mVertices[3].a_vertex_pos.x;
			break;

		case VEC_POS_LB_Y_SLIDER:
			modelValue = &mVertices[3].a_vertex_pos.y;
			break;

		case VEC_POS_LB_Z_SLIDER:
			modelValue = &mVertices[3].a_vertex_pos.z;
			break;

		case VEC_NORMAL_LB_X_SLIDER:
			modelValue = &mVertices[3].a_vertex_normal.x;
			break;

		case VEC_NORMAL_LB_Y_SLIDER	:
			modelValue = &mVertices[3].a_vertex_normal.y;
			break;

		case VEC_NORMAL_LB_Z_SLIDER:
			modelValue = &mVertices[3].a_vertex_normal.z;
			break;

		case VEC_TANGENT_LB_X_SLIDER:
			modelValue = &mVertices[3].a_vertex_tangent.x;
			break;

		case VEC_TANGENT_LB_Y_SLIDER:
			modelValue = &mVertices[3].a_vertex_tangent.y;
			break;

		case VEC_TANGENT_LB_Z_SLIDER:
			modelValue = &mVertices[3].a_vertex_tangent.z;
			break;

		case VEC_UV_LB_X_SLIDER:
			modelValue = &mVertices[3].a_vertex_uv.x;
			break;

		case VEC_UV_LB_Y_SLIDER:
			modelValue = &mVertices[3].a_vertex_uv.y;
			break;

		default:
			return sliderModel;
	}

	assert(modelValue);
	sliderModel = new CustomSliderModel(*modelValue, aMin, aMax);
	mSliderModels[aSliderId] = sliderModel;
	return sliderModel;
}

}
