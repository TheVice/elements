#ifndef _PREFERENCES_H_
#define _PREFERENCES_H_

#include "preferences/preferences.h"

namespace Desktop
{

struct preferences : public eps::preferences_interface
{
public:

	preferences();
	~preferences();

	float get_float(const std::string& key, float default_value) const final;
	void set_float(const std::string& key, float value) final;

private:

};

}

#endif
