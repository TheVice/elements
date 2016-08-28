#ifndef _UI_READER_H_
#define _UI_READER_H_

#include "assets/asset_xml.h"
#include <list>
#include <map>

namespace Desktop
{
struct UiReader : public eps::asset_xml
{
public:
	using eps::asset_xml::asset_xml;

public:
	std::list<std::pair<std::string, std::map<std::string, std::string>>> mControlsInfo;
	bool mIsEmpty;

private:
	void addControl(const pugi::xml_node& node, const std::string& parent);
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
