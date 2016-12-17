
#include "UiReader.h"
#include <cstdio>

namespace Library
{

bool UiReader::addControl(const pugi::xml_node& node, const std::string& parent)
{
	std::map<std::string, std::string> attribAndValue;

	for (const auto& attrib : node.attributes())
	{
		attribAndValue[attrib.name()] = attrib.value();
	}

	if (attribAndValue.empty())
	{
		return false;
	}

	auto info = std::make_pair(node.name(), attribAndValue);

	if (!parent.empty())
	{
		info.second["parent"] = parent;
	}

	mControlsInfo.push_back(info);
	const auto& search = attribAndValue.find("control_name");
	std::string controlName;

	if (search != attribAndValue.end())
	{
		if (parent.empty())
		{
			controlName = search->second;
		}
		else
		{
			controlName = parent + "/" + search->second;
		}
	}
	else
	{
		const auto written = std::snprintf(nullptr, 0, "%p", &mControlsInfo.back());
		controlName.reserve(written);
		controlName.resize(written);
		std::sprintf(&controlName.front(), "%p", &mControlsInfo.back());
	}

	mControlsInfo.back().second["control_name"] = controlName;

	for (const auto& sub_node : node)
	{
		if (!addControl(sub_node, controlName))
		{
			return false;
		}
	}

	return true;
}

bool UiReader::read(const pugi::xml_document& doc)
{
	mControlsInfo.clear();
	mIsEmpty = true;
	//
	const auto settings_node = doc.child("settings");

	if (settings_node.empty())
	{
		return !mIsEmpty;
	}

	const auto controls_node = settings_node.child("controls");

	if (controls_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& control : controls_node)
	{
		if (!addControl(control, ""))
		{
			mControlsInfo.clear();
			break;
		}
	}

	mIsEmpty = mControlsInfo.empty();
	return !mIsEmpty;
}

}
