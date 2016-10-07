#ifndef _METRICS_H_
#define _METRICS_H_

#include "metrics/metrics.h"

namespace Desktop
{

struct metrics : public eps::metrics_interface
{
	metrics(float density);

	float density() const final;
	~metrics();

private:
	float density_;
};


#ifdef WIN32

struct win32_metrics : public eps::metrics_interface
{
	win32_metrics(int dpi);

	float density() const final;
	~win32_metrics();

private:
	float density_;
};

#endif

}

#endif
