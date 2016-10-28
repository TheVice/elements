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

struct asset_fs2 : public eps::io::system
{
	explicit asset_fs2(const std::string& path_to_cache);

	eps::io::file* open(const std::string& file) final;
	bool exists(const std::string& file) final;
	void close(eps::io::file* file) final;

private:
	const std::string _path_to_cache;
};

#ifndef ANDROID

struct asset_fs3 : public eps::io::system
{
	explicit asset_fs3(const std::string& mount_point = "");

	eps::io::file* open(const std::string& file) final;
	bool exists(const std::string& file) final;
	void close(eps::io::file* file) final;

private:
	const std::string mount_point_;
	std::map<std::string, std::string> assets_;
};

#endif

#endif
