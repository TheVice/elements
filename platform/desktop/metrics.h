#ifndef _METRICS_H_
#define _METRICS_H_

#include "metrics/metrics.h"

struct metrics : public eps::metrics_interface
{
public:

	metrics(float density);
	~metrics();

	float density() const final;

private:

	float density_;
};

#endif
