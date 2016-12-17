
#include "TestCard.h"

namespace Library
{
namespace TestCard
{

static const unsigned char colors[][4] =
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

#define COLORS_COUNT static_cast<int>(sizeof(colors)/sizeof(*colors))
#define threeDimension2OneIndex(A, B, C) (A * aWidth * 4 + B * 4 + C)

void MakeColorBars(unsigned char* aImage, int aWidth, int aHeight)
{
	const auto barWidth = static_cast<int>(static_cast<float>(aWidth) / COLORS_COUNT);

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < COLORS_COUNT); ++j)
	{
		if (j > offset)
		{
			colorNumber++;
			offset += barWidth;
		}

		for (auto i = 0; i < aHeight; i++)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = colors[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = colors[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = colors[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = colors[colorNumber][3];
		}
	}
}

}
}
