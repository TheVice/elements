
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

static std::atomic<int> mX1(0);
static std::atomic<int> mY1(0);
static std::atomic<int> mX2(0);
static std::atomic<int> mY2(0);
static std::atomic<int> mX3(0);
static std::atomic<int> mY3(0);
static std::atomic<int> mX4(0);
static std::atomic<int> mY4(0);

static std::atomic<bool> mChanged(false);
static std::atomic<bool> mStop(false);

/*
void CreateAndProcessWindow(int aX, int aY)
{
	auto game = std::make_unique<Rendering::RenderingGame2>(TEXT("Matrices"), aX, aY);
	game->Run();
//	try
//	{
//		game->Run();
//	}
//	catch (const std::runtime_error& aExc)
//	{
//#ifndef WIN32
//		std::cerr << aExc.what() << std::endl;
//#else
//		MessageBoxA(game->GetWindowHandle(), aExc.what(), "", MB_ABORTRETRYIGNORE);
//#endif
//	}
*/

enum ElementIDs
{
	TextShearX = 100,
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
	TextX1,
	TextY1,
	TextX2,
	TextY2,
	TextX3,
	TextY3,
	TextX4,
	TextY4,
	//
	EditShearX = 200,
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
	EditX1,
	EditY1,
	EditX2,
	EditY2,
	EditX3,
	EditY3,
	EditX4,
	EditY4,
	//
	UpDownShearX = 300,
	UpDownShearY,
	UpDownShearZ,
	UpDownScaleX,
	UpDownScaleY,
	UpDownScaleZ,
	UpDownTranslateX,
	UpDownTranslateY,
	UpDownTranslateZ,
	UpDownSize,
	//
	UpDownX1,
	UpDownY1,
	UpDownX2,
	UpDownY2,
	UpDownX3,
	UpDownY3,
	UpDownX4,
	UpDownY4
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

					case EditX1:
						value = GetNumericUpDownValue(aHwnd, UpDownX1);

						if (mX1.load() != value)
						{
							mX1.store(value);
							mChanged.store(true);
						}

						break;

					case EditY1:
						value = GetNumericUpDownValue(aHwnd, UpDownY1);

						if (mY1.load() != value)
						{
							mY1.store(value);
							mChanged.store(true);
						}

						break;

					case EditX2:
						value = GetNumericUpDownValue(aHwnd, UpDownX2);

						if (mX2.load() != value)
						{
							mX2.store(value);
							mChanged.store(true);
						}

						break;

					case EditY2:
						value = GetNumericUpDownValue(aHwnd, UpDownY2);

						if (mY2.load() != value)
						{
							mY2.store(value);
							mChanged.store(true);
						}

						break;

					case EditX3:
						value = GetNumericUpDownValue(aHwnd, UpDownX3);

						if (mX3.load() != value)
						{
							mX3.store(value);
							mChanged.store(true);
						}

						break;

					case EditY3:
						value = GetNumericUpDownValue(aHwnd, UpDownY3);

						if (mY3.load() != value)
						{
							mY3.store(value);
							mChanged.store(true);
						}

						break;

					case EditX4:
						value = GetNumericUpDownValue(aHwnd, UpDownX4);

						if (mX4.load() != value)
						{
							mX4.store(value);
							mChanged.store(true);
						}

						break;

					case EditY4:
						value = GetNumericUpDownValue(aHwnd, UpDownY4);

						if (mY4.load() != value)
						{
							mY4.store(value);
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
	const HWND window = MakeWindow(className, windowTitle, aInstance, aX, aY, 400, 320, WinProc);
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
		{
			int x1 = x + dx + numericUpDownWidth + 25;
			int y1 = y;
			int dx1 = x1 + 100;
			Text(x1, y1, TEXT("Vertex X1"), window, TextX1, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditX1, UpDownX1,
						  aInstance, -100, 100, mX1.load());
			//
			y1 += static_cast<int>(1.5 * dy);
			Text(x1, y1, TEXT("Vertex Y1"), window, TextY1, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditY1, UpDownY1,
						  aInstance, -100, 100, mY1.load());
			//
			y1 += static_cast<int>(1.5 * dy);
			Text(x1, y1, TEXT("Vertex X2"), window, TextX2, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditX2, UpDownX2,
						  aInstance, -100, 100, mX2.load());
			//
			y1 += static_cast<int>(1.5 * dy);
			Text(x1, y1, TEXT("Vertex Y2"), window, TextY2, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditY2, UpDownY2,
						  aInstance, -100, 100, mY2.load());
			//
			y1 += static_cast<int>(1.5 * dy);
			Text(x1, y1, TEXT("Vertex X3"), window, TextX3, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditX3, UpDownX3,
						  aInstance, -100, 100, mX3.load());
			//
			y1 += static_cast<int>(1.5 * dy);
			Text(x1, y1, TEXT("Vertex Y3"), window, TextY3, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditY3, UpDownY3,
						  aInstance, -100, 100, mY3.load());
			//
			y1 += static_cast<int>(1.5 * dy);
			Text(x1, y1, TEXT("Vertex X4"), window, TextX4, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditX4, UpDownX4,
						  aInstance, -100, 100, mX4.load());
			//
			y1 += static_cast<int>(1.5 * dy);
			Text(x1, y1, TEXT("Vertex Y4"), window, TextY4, aInstance, hdc);
			NumericUpDown(dx1, y1, numericUpDownWidth, numericUpDownHeight, window, EditY4, UpDownY4,
						  aInstance, -100, 100, mY4.load());
		}
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

	if (!eps::rendering::load_program("assets/shaders/experiments/liquid/particles.prog", mProgram))
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
	mX1.store(0);
	mY1.store(10);
	mX2.store(10);
	mY2.store(10);
	mX3.store(10);
	mY3.store(0);
	mX4.store(0);
	mY4.store(0);
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//
	mSettingsWindowThread = std::make_unique<std::thread>(CreateAndProcessWindow, GetModuleHandle(nullptr),
							CW_USEDEFAULT, CW_USEDEFAULT);
	/*glm::ivec2 windowPos;
	glfwGetWindowPos(mGame->GetWindow(), &windowPos.x, &windowPos.y);
	windowPos.x += mGame->GetScreenWidth();
	mSettingsWindowThread = std::make_unique<std::thread>(CreateAndProcessWindow, windowPos.x, windowPos.y);*/
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
		//
		const glm::vec2 positionVertices[] =
		{
			{ mX1.load() / 10, mY1.load() / 10 },
			{ mX2.load() / 10, mY2.load() / 10 },
			{ mX3.load() / 10, mY3.load() / 10 },
			{ mX4.load() / 10, mY4.load() / 10 }
		};
		//
		const glm::vec2 textureVertices[] =
		{
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f }
		};
		//
		GLfloat vertices[] =
		{
			positionVertices[0].x, positionVertices[0].y, textureVertices[0].x, textureVertices[0].y,
			positionVertices[1].x, positionVertices[1].y, textureVertices[1].x, textureVertices[1].y,
			positionVertices[2].x, positionVertices[2].y, textureVertices[2].x, textureVertices[2].y,
			positionVertices[3].x, positionVertices[3].y, textureVertices[3].x, textureVertices[3].y
		};
		//
		mSquare.construct(vertices);
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
