
#include "UiReader.h"

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
	int written = parent.size() + 1 + (search != attribAndValue.end() ? search->second.size() + 1 : 32);
	std::string controlName(written, '\0');

	if (search != attribAndValue.end())
	{
		if (parent.empty())
		{
			written = std::sprintf(&controlName.front(), "%s", search->second.c_str());
		}
		else
		{
			written = std::sprintf(&controlName.front(), "%s/%s", parent.c_str(), search->second.c_str());
		}
	}
	else
	{
		written = std::sprintf(&controlName.front(), "%p", &mControlsInfo.back());
	}

	controlName.resize(written);
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
	const auto ui_node = doc.child("ui");

	if (ui_node.empty())
	{
		return !mIsEmpty;
	}

	const auto controls_node = ui_node.child("controls");

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
