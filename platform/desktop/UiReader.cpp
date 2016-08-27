
#include "UiReader.h"

namespace Desktop
{

bool UiReader::read(const pugi::xml_document& doc)
{
	mControlsInfo.clear();
	mIsEmpty = true;
	//
	auto root_node = doc.child("ui");

	if (root_node.empty())
	{
		return false;
	}

	auto controls_node = root_node.child("controls");

	if (controls_node.empty())
	{
		return false;
	}

	for (auto control = controls_node.begin(); control != controls_node.end(); ++control)
	{
		std::map<std::string, std::string> attribAndValue;

		for (auto attrib = control->attributes_begin(); attrib != control->attributes_end(); ++attrib)
		{
			attribAndValue[attrib->name()] = attrib->value();
		}

		if (!attribAndValue.empty())
		{
			auto c = std::make_pair(control->name(), attribAndValue);
			mControlsInfo.push_back(c);
		}
	}

	if (mControlsInfo.empty())
	{
		return false;
	}

	mIsEmpty = false;
	return true;
}

}
