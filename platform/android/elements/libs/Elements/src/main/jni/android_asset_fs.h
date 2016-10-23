#ifndef _ASSET_FS_H_
#define _ASSET_FS_H_

#include "io/system.h"
#include <map>

struct asset_fs : public eps::io::system
{
	explicit asset_fs();

	eps::io::file* open(const std::string& file) final;
	bool exists(const std::string& file) final;
	void close(eps::io::file* file) final;

	static std::map<std::string, std::string> assets_;
};

#endif
