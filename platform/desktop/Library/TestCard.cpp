
#include "TestCard.h"

namespace Library
{
namespace TestCard
{

#define threeDimension2OneIndex(A, B, C) (A * aWidth * 4 + B * 4 + C)

static const unsigned char sColors4Bars[][4] =
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

void MakeColorBars(unsigned char* aImage, int aWidth, int aHeight)
{
	const auto colors_count = static_cast<int>(sizeof(sColors4Bars) / sizeof(*sColors4Bars));
	const auto barWidth = static_cast<int>(static_cast<float>(aWidth) / colors_count);

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = 0; i < aHeight; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4Bars[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4Bars[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4Bars[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4Bars[colorNumber][3];
		}

		if (j > offset)
		{
			colorNumber++;
			offset += barWidth;
		}
	}
}

static const unsigned char sColors4Smpte_1[][4] =
{
	{ 192, 192, 192, 255 },
	{ 196, 196, 0, 0 },
	{ 0, 196, 196, 255 },
	{ 0, 196, 0, 0 },
	{ 196, 0, 196, 255 },
	{ 196, 0, 0, 0 },
	{ 0, 0, 196, 255 }
};

static const unsigned char sColors4Smpte_2[][4] =
{
	{ 0, 0, 196, 0 },
	{ 19, 19, 19, 255 },
	{ 196, 0, 196, 0 },
	{ 19, 19, 19, 255 },
	{ 0, 196, 196, 0 },
	{ 19, 19, 19, 255 },
	{ 192, 192, 192, 0 }
};

static const unsigned char sColors4Smpte_3[][4] =
{
	{ 0, 33, 76, 255 },
	{ 255, 255, 255, 0 },
	{ 50, 0, 106, 255 },
	{ 19, 19, 1, 0 },
	{ 9, 9, 9, 255 },
	{ 19, 19, 19, 0 },
	{ 29, 29, 29, 255 },
	{ 19, 19, 19, 0 }
};

void MakeSmpteColorBars(unsigned char* aImage, int aWidth, int aHeight)
{
	// fill first colors
	auto colors_count = static_cast<int>(sizeof(sColors4Smpte_1) / sizeof(*sColors4Smpte_1));
	const auto barWidth = static_cast<int>(static_cast<float>(aWidth) / colors_count);
	const auto firstLineEnd = aHeight - static_cast<int>(static_cast<float>(aHeight) * (static_cast<float>
							  (336) / 504));

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = firstLineEnd; i < aHeight; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4Smpte_1[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4Smpte_1[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4Smpte_1[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4Smpte_1[colorNumber][3];
		}

		if (j > offset)
		{
			colorNumber++;
			offset += barWidth;
		}
	}

	// fill second colors
	colors_count = static_cast<int>(sizeof(sColors4Smpte_2) / sizeof(*sColors4Smpte_2));
	const auto secondLineEnd = firstLineEnd - static_cast<int>(static_cast<float>(aHeight) * (static_cast<float>
							   (42) / 504));

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = secondLineEnd; i < firstLineEnd; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4Smpte_2[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4Smpte_2[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4Smpte_2[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4Smpte_2[colorNumber][3];
		}

		if (j > offset)
		{
			colorNumber++;
			offset += barWidth;
		}
	}

	// fill third colors
	colors_count = static_cast<int>(sizeof(sColors4Smpte_3) / sizeof(*sColors4Smpte_3));
	const auto thirdBarWidth = static_cast<int>(static_cast<float>(5 * barWidth) / 4);
	const auto thirdBarWidth2 = static_cast<int>(static_cast<float>(barWidth) / 3);

	for (auto j = 0, offset = thirdBarWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = 0; i < secondLineEnd; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4Smpte_3[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4Smpte_3[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4Smpte_3[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4Smpte_3[colorNumber][3];
		}

		if (j > offset && j < 4 * thirdBarWidth)
		{
			colorNumber++;
			offset += thirdBarWidth;
		}
		else if (j > 4 * thirdBarWidth && j < 4 * thirdBarWidth + barWidth)
		{
			if (j > offset)
			{
				colorNumber++;
				offset += thirdBarWidth2;
			}
		}
		else if (j > 4 * thirdBarWidth + barWidth)
		{
			if (j > offset)
			{
				colorNumber++;
				offset += thirdBarWidth;
			}
		}
	}
}

static const unsigned char sColors4SmpteHD_1[][4] =
{
	{ 102, 102, 102, 0 },
	{ 191, 191, 191, 255 },
	{ 191, 191, 0, 0 },
	{ 0, 191, 191, 255 },
	{ 0, 191, 0, 0 },
	{ 191, 0, 191, 255 },
	{ 191, 0, 0, 0 },
	{ 0, 0, 191, 255 },
	{ 102, 102, 102, 0 }
};

static const unsigned char sColors4SmpteHD_2[][4] =
{
	{ 0, 255, 255, 255 },
	{ 0, 33, 76, 0 },
	{ 191, 191, 191, 255 },
	{ 0, 0, 255, 0 }
};

static const unsigned char sColors4SmpteHD_3[][4] =
{
	{ 255, 255, 0, 255 },
	{ 50, 0, 106, 0 },
	{
		static_cast<unsigned char>(255 * (static_cast<float>(5) / 16)),
		static_cast<unsigned char>(255 * (static_cast<float>(5) / 16)),
		static_cast<unsigned char>(255 * (static_cast<float>(5) / 16)),
		255
	},
	{ 255, 255, 255, 0 },
	{ 255, 0, 0, 255 }
};

static const unsigned char sColors4SmpteHD_4[][4] =
{
	{ 38, 38, 38, 0 },
	{ 0, 0, 0, 255 },
	{ 255, 255, 255, 0 },
	{ 0, 0, 0, 255 },
	{ 5, 5, 5, 0 },
	{ 0, 0, 0, 255 },
	{ 10, 10, 10, 0 },
	{ 0, 0, 0, 255 },
	{ 38, 38, 38, 0 }
};

unsigned char MixValues(unsigned char value_a, unsigned char value_b, int location, int distance)
{
	unsigned char mixed_value = value_a;

	if (value_a < value_b)
	{
		const auto color_distance = value_b - value_a;
		const auto delta_value = static_cast<unsigned char>(static_cast<float>(color_distance * location) / distance);
		mixed_value += delta_value;
	}
	else
	{
		const auto color_distance = value_a - value_b;
		const auto delta_value = static_cast<unsigned char>(static_cast<float>(color_distance * location) / distance);
		mixed_value -= delta_value;
	}

	return mixed_value;
}

void MixColors(const unsigned char* color_a, const unsigned char* color_b, int location, int distance,
			   unsigned char* mixed_color)
{
	for (auto i = 0; i < 4; ++i)
	{
		mixed_color[i] = MixValues(color_a[i], color_b[i], location, distance);
	}
}

void MakeSmpteColorBarsHD(unsigned char* aImage, int aWidth, int aHeight)
{
	// fill first colors
	auto colors_count = static_cast<int>(sizeof(sColors4SmpteHD_1) / sizeof(*sColors4SmpteHD_1));
	const auto barWidth = static_cast<int>(static_cast<float>(aWidth) / colors_count);
	const auto firstLineEnd = static_cast<int>(static_cast<float>(aHeight) * (static_cast<float>(630) / 1920));

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = firstLineEnd; i < aHeight; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4SmpteHD_1[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4SmpteHD_1[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4SmpteHD_1[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4SmpteHD_1[colorNumber][3];
		}

		if (j > offset)
		{
			colorNumber++;
			offset += barWidth;
		}
	}

	// fill second colors
	colors_count = static_cast<int>(sizeof(sColors4SmpteHD_2) / sizeof(*sColors4SmpteHD_2));
	const auto secondLineEnd = firstLineEnd - static_cast<int>(static_cast<float>(aHeight) * (static_cast<float>
							   (90) / 1920));

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = secondLineEnd; i < firstLineEnd; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4SmpteHD_2[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4SmpteHD_2[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4SmpteHD_2[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4SmpteHD_2[colorNumber][3];
		}

		if (j > offset && j < 2 * barWidth)
		{
			colorNumber++;
			offset += barWidth;
		}
		else if (j > 2 * barWidth && j < 8 * barWidth)
		{
			if (j > offset)
			{
				colorNumber++;
				offset += 6 * barWidth;
			}
		}
		else if (j > 8 * barWidth)
		{
			if (j > offset)
			{
				colorNumber++;
				offset += barWidth;
			}
		}
	}

	// fill third colors
	colors_count = static_cast<int>(sizeof(sColors4SmpteHD_3) / sizeof(*sColors4SmpteHD_3));
	const auto thirdLineEnd = secondLineEnd - static_cast<int>(static_cast<float>(aHeight) * (static_cast<float>
							  (90) / 1920));

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = thirdLineEnd; i < secondLineEnd; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4SmpteHD_3[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4SmpteHD_3[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4SmpteHD_3[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4SmpteHD_3[colorNumber][3];
		}

		if (j > offset && j < 2 * barWidth)
		{
			colorNumber++;
			offset += barWidth;
		}
		else if (j > 2 * barWidth && j < 8 * barWidth)
		{
			const auto distance = 6 * barWidth;
			const auto location = j - 2 * barWidth;
			unsigned char mixed_color[4] = { 0, 0, 0, 0 };
			MixColors(sColors4SmpteHD_3[2], sColors4SmpteHD_3[3], location, distance, mixed_color);

			for (auto i = thirdLineEnd; i < secondLineEnd; ++i)
			{
				aImage[threeDimension2OneIndex(i, j, 0)] = mixed_color[0];
				aImage[threeDimension2OneIndex(i, j, 1)] = mixed_color[1];
				aImage[threeDimension2OneIndex(i, j, 2)] = mixed_color[2];
				aImage[threeDimension2OneIndex(i, j, 3)] = mixed_color[3];
			}

			colorNumber = 3;
			offset = 8 * barWidth;
			continue;
		}
		else if (j > 8 * barWidth)
		{
			if (j > offset)
			{
				colorNumber++;
				offset += barWidth;
			}
		}
	}

	// fill fourth line
	colors_count = static_cast<int>(sizeof(sColors4SmpteHD_4) / sizeof(*sColors4SmpteHD_4));
	const auto fourthLineEnd = thirdLineEnd;

	for (auto j = 0, offset = barWidth, colorNumber = 0; (j < aWidth && colorNumber < colors_count); ++j)
	{
		for (auto i = 0; i < fourthLineEnd; ++i)
		{
			aImage[threeDimension2OneIndex(i, j, 0)] = sColors4SmpteHD_4[colorNumber][0];
			aImage[threeDimension2OneIndex(i, j, 1)] = sColors4SmpteHD_4[colorNumber][1];
			aImage[threeDimension2OneIndex(i, j, 2)] = sColors4SmpteHD_4[colorNumber][2];
			aImage[threeDimension2OneIndex(i, j, 3)] = sColors4SmpteHD_4[colorNumber][3];
		}

		if (j > offset)
		{
			colorNumber++;

			if (j < 2 * barWidth + static_cast<int>(static_cast<float>(barWidth) / 2))
			{
				offset += barWidth + static_cast<int>(static_cast<float>(barWidth) / 2);
			}
			else if (j >= 2 * barWidth + static_cast<int>(static_cast<float>(barWidth) / 2) &&
					 j < 4 * barWidth + static_cast<int>(static_cast<float>(barWidth) / 2))
			{
				offset += 2 * barWidth;
			}
			else if (j >= 4 * barWidth + static_cast<int>(static_cast<float>(barWidth) / 2) && j < 6 * barWidth)
			{
				offset += barWidth + static_cast<int>(static_cast<float>(barWidth) / 2);
			}
			else if (j >= 6 * barWidth && j < 7 * barWidth)
			{
				offset += static_cast<int>(static_cast<float>(barWidth) / 3);
			}
			else if (j >= 7 * barWidth)
			{
				offset += barWidth;
			}
		}
	}
}

}
}
