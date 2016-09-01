
#include "CapsView.h"
#include "metrics/metrics.h"
#include "ui/controls/label.h"
#include "checkbox.h"
#include <Game.h>

namespace Desktop
{
RTTI_DEFINITIONS(CapsView)

CapsView::CapsView(Library::Game& aGame) :
	DrawableUiGameComponent(aGame),
	mControls()
{
}

CapsView::~CapsView()
{
}

void CapsView::Initialize()
{
	DrawableUiGameComponent::Initialize();
	const auto screenSize = eps::math::uvec2(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	const auto density = eps::metrics::instance().density();
	int x = 0;
	int y = screenSize.y;
	const int step_x = screenSize.x / 3;

	for (const auto& cap : mCaps)
	{
		y = y - 20;
		auto checkBox = mUiSystem->add<Desktop::checkbox>();

		if (auto directCheckbox = std::static_pointer_cast<Desktop::checkbox>(checkBox.lock()))
		{
			directCheckbox->set_position(density * x, density * (3 + y));
			directCheckbox->set_size(density * 13, density * 13);
			directCheckbox->set_state(glIsEnabled(cap.second) ? Desktop::checkbox::state::CHECKED :
									  Desktop::checkbox::state::UNCHECKED);
		}

		mControls[cap.first] = checkBox;

		if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mUiSystem->add<eps::ui::label>().lock()))
		{
			directLabel->set_position(density * (15 + x), density * y);
			directLabel->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(density * 18));
			directLabel->set_text(cap.first);
			directLabel->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		}

		if (y < 0 && x + step_x < static_cast<int>(screenSize.x))
		{
			y = screenSize.y;
			x += step_x;
		}
		else if (x + step_x > static_cast<int>(screenSize.x))
		{
			break;
		}
	}
}

void CapsView::Update(const Library::GameTime& aGameTime)
{
	DrawableUiGameComponent::Update(aGameTime);

	for (const auto& cap : mCaps)
	{
		if (auto directCheckbox = std::static_pointer_cast<Desktop::checkbox>(mControls[cap.first].lock()))
		{
			bool isCapEnable = directCheckbox->get_state() == Desktop::checkbox::state::CHECKED;

			if (isCapEnable)
			{
				glEnable(cap.second);
			}
			else
			{
				glDisable(cap.second);
			}
		}
	}
}

const std::map<std::string, unsigned int> CapsView::mCaps =
{
	{ "GL_ALPHA_TEST", GL_ALPHA_TEST },
	{ "GL_AUTO_NORMAL", GL_AUTO_NORMAL },
	{ "GL_BLEND", GL_BLEND },
	//
	{ "GL_CLIP_PLANE0", GL_CLIP_PLANE0 },
	{ "GL_CLIP_PLANE1", GL_CLIP_PLANE1 },
	{ "GL_CLIP_PLANE2", GL_CLIP_PLANE2 },
	{ "GL_CLIP_PLANE3", GL_CLIP_PLANE3 },
	{ "GL_CLIP_PLANE4", GL_CLIP_PLANE4 },
	{ "GL_CLIP_PLANE5", GL_CLIP_PLANE5 },
	//
	{ "GL_COLOR_ARRAY", GL_COLOR_ARRAY },
	{ "GL_COLOR_LOGIC_OP", GL_COLOR_LOGIC_OP },
	{ "GL_COLOR_MATERIAL", GL_COLOR_MATERIAL },
	{ "GL_COLOR_SUM", GL_COLOR_SUM },
	{ "GL_COLOR_TABLE", GL_COLOR_TABLE },
	{ "GL_CONVOLUTION_1D", GL_CONVOLUTION_1D },
	{ "GL_CONVOLUTION_2D", GL_CONVOLUTION_2D },
	{ "GL_CULL_FACE", GL_CULL_FACE },
	{ "GL_DEPTH_TEST", GL_DEPTH_TEST },
	{ "GL_DITHER", GL_DITHER },
	{ "GL_EDGE_FLAG_ARRAY", GL_EDGE_FLAG_ARRAY },
	{ "GL_FOG", GL_FOG },
	{ "GL_FOG_COORD_ARRAY", GL_FOG_COORD_ARRAY },
	{ "GL_HISTOGRAM", GL_HISTOGRAM },
	{ "GL_INDEX_ARRAY", GL_INDEX_ARRAY },
	{ "GL_INDEX_LOGIC_OP", GL_INDEX_LOGIC_OP },
	//
	{ "GL_LIGHT0", GL_LIGHT0 },
	{ "GL_LIGHT1", GL_LIGHT1 },
	{ "GL_LIGHT2", GL_LIGHT2 },
	{ "GL_LIGHT3", GL_LIGHT3 },
	{ "GL_LIGHT4", GL_LIGHT4 },
	{ "GL_LIGHT5", GL_LIGHT5 },
	{ "GL_LIGHT6", GL_LIGHT6 },
	{ "GL_LIGHT7", GL_LIGHT7 },
	//
	{ "GL_LIGHTING", GL_LIGHTING },
	{ "GL_LINE_SMOOTH", GL_LINE_SMOOTH },
	{ "GL_LINE_STIPPLE", GL_LINE_STIPPLE },
	{ "GL_MAP1_COLOR_4", GL_MAP1_COLOR_4 },
	{ "GL_MAP1_INDEX", GL_MAP1_INDEX },
	{ "GL_MAP1_NORMAL", GL_MAP1_NORMAL },
	{ "GL_MAP1_TEXTURE_COORD_1", GL_MAP1_TEXTURE_COORD_1 },
	{ "GL_MAP1_TEXTURE_COORD_2", GL_MAP1_TEXTURE_COORD_2 },
	{ "GL_MAP1_TEXTURE_COORD_3", GL_MAP1_TEXTURE_COORD_3 },
	{ "GL_MAP1_TEXTURE_COORD_4", GL_MAP1_TEXTURE_COORD_4 },
	{ "GL_MAP2_COLOR_4", GL_MAP2_COLOR_4 },
	{ "GL_MAP2_INDEX", GL_MAP2_INDEX },
	{ "GL_MAP2_NORMAL", GL_MAP2_NORMAL },
	{ "GL_MAP2_TEXTURE_COORD_1", GL_MAP2_TEXTURE_COORD_1 },
	{ "GL_MAP2_TEXTURE_COORD_2", GL_MAP2_TEXTURE_COORD_2 },
	{ "GL_MAP2_TEXTURE_COORD_3", GL_MAP2_TEXTURE_COORD_3 },
	{ "GL_MAP2_TEXTURE_COORD_4", GL_MAP2_TEXTURE_COORD_4 },
	{ "GL_MAP2_VERTEX_3", GL_MAP2_VERTEX_3 },
	{ "GL_MAP2_VERTEX_4", GL_MAP2_VERTEX_4 },
	{ "GL_MINMAX", GL_MINMAX },
	{ "GL_MULTISAMPLE", GL_MULTISAMPLE },
	{ "GL_NORMAL_ARRAY", GL_NORMAL_ARRAY },
	{ "GL_NORMALIZE", GL_NORMALIZE },
	{ "GL_POINT_SMOOTH", GL_POINT_SMOOTH },
	{ "GL_POINT_SPRITE", GL_POINT_SPRITE },
	{ "GL_POLYGON_SMOOTH", GL_POLYGON_SMOOTH },
	{ "GL_POLYGON_OFFSET_FILL", GL_POLYGON_OFFSET_FILL },
	{ "GL_POLYGON_OFFSET_LINE", GL_POLYGON_OFFSET_LINE },
	{ "GL_POLYGON_OFFSET_POINT", GL_POLYGON_OFFSET_POINT },
	{ "GL_POLYGON_STIPPLE", GL_POLYGON_STIPPLE },
	{ "GL_POST_COLOR_MATRIX_COLOR_TABLE", GL_POST_COLOR_MATRIX_COLOR_TABLE },
	{ "GL_POST_CONVOLUTION_COLOR_TABLE", GL_POST_CONVOLUTION_COLOR_TABLE },
	{ "GL_RESCALE_NORMAL", GL_RESCALE_NORMAL },
	{ "GL_SAMPLE_ALPHA_TO_COVERAGE", GL_SAMPLE_ALPHA_TO_COVERAGE },
	{ "GL_SAMPLE_ALPHA_TO_ONE", GL_SAMPLE_ALPHA_TO_ONE },
	{ "GL_SAMPLE_COVERAGE", GL_SAMPLE_COVERAGE },
	{ "GL_SCISSOR_TEST", GL_SCISSOR_TEST },
	{ "GL_SECONDARY_COLOR_ARRAY", GL_SECONDARY_COLOR_ARRAY },
	{ "GL_SEPARABLE_2D", GL_SEPARABLE_2D },
	{ "GL_STENCIL_TEST", GL_STENCIL_TEST },
	{ "GL_TEXTURE_1D", GL_TEXTURE_1D },
	{ "GL_TEXTURE_2D", GL_TEXTURE_2D },
	{ "GL_TEXTURE_3D", GL_TEXTURE_3D },
	{ "GL_TEXTURE_COORD_ARRAY", GL_TEXTURE_COORD_ARRAY },
	{ "GL_TEXTURE_CUBE_MAP", GL_TEXTURE_CUBE_MAP },
	{ "GL_TEXTURE_GEN_Q", GL_TEXTURE_GEN_Q },
	{ "GL_TEXTURE_GEN_R", GL_TEXTURE_GEN_R },
	{ "GL_TEXTURE_GEN_S", GL_TEXTURE_GEN_S },
	{ "GL_TEXTURE_GEN_T", GL_TEXTURE_GEN_T },
	{ "GL_VERTEX_ARRAY", GL_VERTEX_ARRAY },
	{ "GL_VERTEX_PROGRAM_POINT_SIZE", GL_VERTEX_PROGRAM_POINT_SIZE },
	{ "GL_VERTEX_PROGRAM_TWO_SIDE", GL_VERTEX_PROGRAM_TWO_SIDE }
};

}
