
#include "preferences.h"

namespace Desktop
{

preferences::preferences()
{
}

preferences::~preferences()
{
}

float preferences::get_float(const std::string& key, float default_value) const
{
	(void)key;
	return default_value;
}

void preferences::set_float(const std::string& key, float value)
{
	(void)key;
	(void)value;
}

}
