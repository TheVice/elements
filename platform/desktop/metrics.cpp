
#include "metrics.h"
#ifdef WIN32
#include <unordered_map>
#endif

namespace Desktop
{

metrics::metrics(float density) :
	density_(density)
{
}

float metrics::density() const
{
	return density_;
}

metrics::~metrics()
{
}

#ifdef WIN32

static std::unordered_map<int, float> dpi_map =
{
	{  96, 1.00f },
	{ 120, 1.25f },
	{ 144, 1.50f },
	{ 192, 2.00f },
	{ 240, 2.50f },
	{ 288, 3.00f },
	{ 384, 4.00f },
	{ 480, 5.00f },
};

win32_metrics::win32_metrics(int dpi) :
	density_(dpi_map.count(dpi) ? dpi_map[dpi] : dpi_map[96])
{
}

float win32_metrics::density() const
{
	return density_;
}

win32_metrics::~win32_metrics()
{
}

#endif

}
