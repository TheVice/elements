
#include "ParticlesDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/passes/pass_base.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "SettingsReader.h"
#include "Game.h"
#ifdef _WIN32
#include "Win32Controls.h"
#include <atomic>

static std::atomic<int> mShearX(0);
static std::atomic<int> mShearY(0);
static std::atomic<int> mShearZ(0);
static std::atomic<int> mScaleX(0);
static std::atomic<int> mScaleY(0);
static std::atomic<int> mScaleZ(0);
static std::atomic<int> mTranslateX(0);
static std::atomic<int> mTranslateY(0);
static std::atomic<int> mTranslateZ(0);
static std::atomic<int> mSize_(0);
static std::atomic<bool> mChanged(false);
static std::atomic<bool> mStop(false);

enum ElementIDs
{
	TextShearX = 1,
	TextShearY,
	TextShearZ,
	TextScaleX,
	TextScaleY,
	TextScaleZ,
	TextTranslateX,
	TextTranslateY,
	TextTranslateZ,
	TextSize,
	//
	EditShearX = 100,
	EditShearY,
	EditShearZ,
	EditScaleX,
	EditScaleY,
	EditScaleZ,
	EditTranslateX,
	EditTranslateY,
	EditTranslateZ,
	EditSize,
	//
	UpDownShearX = 1000,
	UpDownShearY,
	UpDownShearZ,
	UpDownScaleX,
	UpDownScaleY,
	UpDownScaleZ,
	UpDownTranslateX,
	UpDownTranslateY,
	UpDownTranslateZ,
	UpDownSize
};

void ProcessWindow(HWND aWindow, int aCmdShow, const TCHAR* aClassName, HINSTANCE aInstance)
{
	ShowWindow(aWindow, aCmdShow);
	UpdateWindow(aWindow);
	MSG message;

	while (!mStop.load() && GetMessage(&message, HWND_DESKTOP, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnregisterClass(aClassName, aInstance);
	mStop.store(true);
}

LRESULT WINAPI WinProc(HWND aHwnd, UINT aMsg, WPARAM aWparam, LPARAM aLparam)
{
	switch (aMsg)
	{
		case WM_COMMAND:
			if (HIWORD(aWparam) == EN_CHANGE)
			{
				int value = 0;

				switch (LOWORD(aWparam))
				{
					case EditShearX:
						value = GetNumericUpDownValue(aHwnd, UpDownShearX);

						if (mShearX.load() != value)
						{
							mShearX.store(value);
							mChanged.store(true);
						}

						break;

					case EditShearY:
						value = GetNumericUpDownValue(aHwnd, UpDownShearY);

						if (mShearY.load() != value)
						{
							mShearY.store(value);
							mChanged.store(true);
						}

						break;

					case EditShearZ:
						value = GetNumericUpDownValue(aHwnd, UpDownShearZ);

						if (mShearZ.load() != value)
						{
							mShearZ.store(value);
							mChanged.store(true);
						}

						break;

					case EditScaleX:
						value = GetNumericUpDownValue(aHwnd, UpDownScaleX);

						if (mScaleX.load() != value)
						{
							mScaleX.store(value);
							mChanged.store(true);
						}

						break;

					case EditScaleY:
						value = GetNumericUpDownValue(aHwnd, UpDownScaleY);

						if (mScaleY.load() != value)
						{
							mScaleY.store(value);
							mChanged.store(true);
						}

						break;

					case EditScaleZ:
						value = GetNumericUpDownValue(aHwnd, UpDownScaleZ);

						if (mScaleZ.load() != value)
						{
							mScaleZ.store(value);
							mChanged.store(true);
						}

						break;

					case EditTranslateX:
						value = GetNumericUpDownValue(aHwnd, UpDownTranslateX);

						if (mTranslateX.load() != value)
						{
							mTranslateX.store(value);
							mChanged.store(true);
						}

						break;

					case EditTranslateY:
						value = GetNumericUpDownValue(aHwnd, UpDownTranslateY);

						if (mTranslateY.load() != value)
						{
							mTranslateY.store(value);
							mChanged.store(true);
						}

						break;

					case EditTranslateZ:
						value = GetNumericUpDownValue(aHwnd, UpDownTranslateZ);

						if (mTranslateZ.load() != value)
						{
							mTranslateZ.store(value);
							mChanged.store(true);
						}

						break;

					case EditSize:
						value = GetNumericUpDownValue(aHwnd, UpDownSize);

						if (mSize_.load() != value)
						{
							mSize_.store(value);
							mChanged.store(true);
						}

						break;

					default:
						break;
				}
			}

			break;

		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(aHwnd, aMsg, aWparam, aLparam);
}

void CreateAndProcessWindow(HINSTANCE aInstance, int aX, int aY)
{
	auto className = TEXT("Win32Controls");
	auto windowTitle = TEXT("Matrix Elements");
	const HWND window = MakeWindow(className, windowTitle, aInstance, aX, aY, 300, 320, WinProc);
	//
	{
		int x = 10;
		int y = 10;
		int dx = 120;
		int dy = 0;
		int numericUpDownWidth = 60;
		int numericUpDownHeight = 0;
		HDC hdc = GetDC(window);
		//
		dy = Text(x, y, TEXT("X Shear:"), window, TextShearX, aInstance, hdc).cy;
		numericUpDownHeight = static_cast<int>(1.25 * dy);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditShearX, UpDownShearX,
					  aInstance, -1000, 1000, mShearX.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("Y Shear:"), window, TextShearY, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditShearY, UpDownShearY,
					  aInstance, -1000, 1000, mShearY.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("Z Shear:"), window, TextShearZ, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditShearZ, UpDownShearZ,
					  aInstance, -1000, 1000, mShearZ.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("X Scale:"), window, TextScaleX, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditScaleX, UpDownScaleX,
					  aInstance, -1000, 1000, mScaleX.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("Y Scale:"), window, TextScaleY, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditScaleY, UpDownScaleY,
					  aInstance, -1000, 1000, mScaleY.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("Z Scale:"), window, TextScaleZ, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditScaleZ, UpDownScaleZ,
					  aInstance, -1000, 1000, mScaleZ.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("X Translate:"), window, TextTranslateX, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditTranslateX, UpDownTranslateX,
					  aInstance, -1000, 1000, mTranslateX.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("Y Translate:"), window, TextTranslateY, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditTranslateY, UpDownTranslateY,
					  aInstance, -1000, 1000, mTranslateY.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("Z Translate:"), window, TextTranslateZ, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditTranslateZ, UpDownTranslateZ,
					  aInstance, -1000, 1000, mTranslateZ.load());
		//
		y += static_cast<int>(1.5 * dy);
		Text(x, y, TEXT("Size:"), window, TextSize, aInstance, hdc);
		NumericUpDown(dx, y, numericUpDownWidth, numericUpDownHeight, window, EditSize, UpDownSize,
					  aInstance, -1000, 1000, mSize_.load());
		//
		ReleaseDC(window, hdc);
	}
	//
	ProcessWindow(window, SW_SHOW, className, aInstance);
}

#define GetShear(MAT4) (glm::vec3(MAT4[1].x, MAT4[0].y, MAT4[0].z))
#define GetScale(MAT4) (glm::vec3(MAT4[0].x, MAT4[1].y, MAT4[2].z))
#define GetTranslate(MAT4) (glm::vec3(MAT4[3].x, MAT4[3].y, MAT4[3].z))

#define SetShear(VEC3, MAT4) ({MAT4[1].x = VEC3.x; MAT4[0].y = VEC3.y; MAT4[0].z = VEC3.z;})
#define SetScale(VEC3, MAT4) ({MAT4[0].x = VEC3.x; MAT4[1].y = VEC3.y; MAT4[2].z = VEC3.z;})
#define SetTranslate(VEC3, MAT4) ({MAT4[3].x = VEC3.x; MAT4[3].y = VEC3.y; MAT4[3].z = VEC3.z;})
#endif

namespace Rendering
{
RTTI_DEFINITIONS(ParticlesDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	//
	FragmentUniformTransformation = 0,
	FragmentUniformSize = 1
};

ParticlesDemo::ParticlesDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mProgram(),
	  mSquare(),
	  mTransform(),
#ifdef _WIN32
	  mSize(),
	  mSettingsWindowThread(nullptr)
#else
	  mSize()
#endif
{
}

ParticlesDemo::~ParticlesDemo()
{
#ifdef _WIN32
	mStop.store(true);
	mSettingsWindowThread->join();
#endif
}

void ParticlesDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("shaders/experiments/liquid/particles.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

#ifdef _WIN32
	auto shear = GetShear(mTransform);
	auto scale = GetScale(mTransform);
	auto translate = GetTranslate(mTransform);
	//
	mShearX.store(100 * shear.x);
	mShearY.store(100 * shear.y);
	mShearZ.store(100 * shear.z);
	//
	mScaleX.store(100 * scale.x);
	mScaleY.store(100 * scale.y);
	mScaleZ.store(100 * scale.z);
	//
	mTranslateX.store(100 * translate.x);
	mTranslateY.store(100 * translate.y);
	mTranslateZ.store(100 * translate.z);
	//
	mSize_.store(100 * mSize);
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//
	mSettingsWindowThread = std::make_unique<std::thread>(CreateAndProcessWindow, GetModuleHandle(nullptr),
							CW_USEDEFAULT, CW_USEDEFAULT);
#endif
}
#ifdef _WIN32
void ParticlesDemo::Update(const Library::GameTime&)
{
	if (mStop.load())
	{
		mGame->Exit();
	}

	if (mChanged.load())
	{
		SetShear(glm::vec3(mShearX.load() / 100, mShearY.load() / 100, mShearZ.load() / 100), mTransform);
		SetScale(glm::vec3(mScaleX.load() / 100, mScaleY.load() / 100, mScaleZ.load() / 100), mTransform);
		SetTranslate(glm::vec3(mTranslateX.load() / 100, mTranslateY.load() / 100, mTranslateZ.load() / 100),
					 mTransform);
		mSize = mSize_.load() / 100;
	}
}
#endif
void ParticlesDemo::Draw(const Library::GameTime&)
{
	EPS_STATE_PROGRAM(mProgram.get_product());
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformSize), mSize);
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition));
}

}
