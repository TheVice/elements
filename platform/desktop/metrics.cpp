
#include "metrics.h"

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
