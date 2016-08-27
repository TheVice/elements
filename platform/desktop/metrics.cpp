
#include "metrics.h"

namespace Desktop
{

metrics::metrics(float density) : density_(density)
{
}

metrics::~metrics()
{
}

float metrics::density() const
{
	return density_;
}

}
