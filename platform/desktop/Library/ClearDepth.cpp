
#include "ClearDepth.h"
#include <elements/rendering/core/opengl.h>
#include <glm/gtc/constants.hpp>

namespace Library
{
RTTI_DEFINITIONS(ClearDepth)

ClearDepth::ClearDepth(Game& aGame) :
	DrawableGameComponent(aGame)
{
}

ClearDepth::~ClearDepth()
{
}

bool ClearDepth::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	return true;
}

void ClearDepth::Draw()
{
	static const GLfloat one = glm::one<GLfloat>();
	//
	//glClearBufferfv(GL_DEPTH, 0, &one);
	glClearDepthf(one);
	glClear(GL_DEPTH_BUFFER_BIT);
}

}
