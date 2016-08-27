
#include "TestCard.h"

namespace Desktop
{

void MakeColorBars(GLubyte* aImage, GLsizei aWidth, GLsizei aHeight)
{
#define threeDimension2OneIndex(A, B, C) (A * aWidth * 4 + B * 4 + C)
	const GLubyte colors[][4] =
	{
		{ 255, 255, 255, 0 },
		{ 196, 196, 0, 255 },
		{ 0, 196, 196, 0 },
		{ 0, 196, 0, 255 },
		{ 196, 0, 196, 0 },
		{ 196, 0, 0, 255 },
		{ 0, 0, 196, 0 },
		{ 0, 0, 0, 255 }
	};
	const GLsizei barWidth = static_cast<GLsizei>(static_cast<GLfloat>(aWidth) / 8);
	GLsizei offset = barWidth;
	GLsizei colorNumber = 0;

	for (GLsizei j = 0; j < aWidth; ++j)
	{
		if (j > offset)
		{
			colorNumber++;
			offset += barWidth;
		}

		for (GLsizei i = 0; i < aHeight; i++)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = (GLubyte)colors[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = (GLubyte)colors[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = (GLubyte)colors[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = (GLubyte)colors[colorNumber][3];
		}
	}
}

}
