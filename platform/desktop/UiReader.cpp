
#include "UiReader.h"
#include <sstream>

namespace Desktop
{

void UiReader::addControl(const pugi::xml_node& node, const std::string& parent)
{
	std::map<std::string, std::string> attribAndValue;

	for (const auto& attrib : node.attributes())
	{
		attribAndValue[attrib.name()] = attrib.value();
	}

	if (!attribAndValue.empty())
	{
		auto info = std::make_pair(node.name(), attribAndValue);
		mControlsInfo.push_back(info);

		std::ostringstream controlName;

		if (!parent.empty())
		{
			mControlsInfo.back().second["parent"] = parent;
			controlName << parent;
			controlName << "/";
		}

		auto search = attribAndValue.find("control_name");

		if (search != attribAndValue.end())
		{
			controlName << search->second;
		}
		else
		{
			controlName << &mControlsInfo.back();
		}

		mControlsInfo.back().second["control_name"] = controlName.str();

		for (const auto& sub_node : node)
		{
			addControl(sub_node, controlName.str());
		}
	}
}

bool UiReader::read(const pugi::xml_document& doc)
{
	mControlsInfo.clear();
	mIsEmpty = true;
	//
	auto ui_node = doc.child("ui");

	if (ui_node.empty())
	{
		return !mIsEmpty;
	}

	auto controls_node = ui_node.child("controls");

	if (controls_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& control : controls_node)
	{
		addControl(control, "");
	}

	mIsEmpty = mControlsInfo.empty();
	return !mIsEmpty;
}

}
