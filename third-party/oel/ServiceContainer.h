#ifndef _SERVICE_CONTAINER_H_
#define _SERVICE_CONTAINER_H_

#include <cstdint>
#include <map>

namespace Library
{
class ServiceContainer
{
public:
	ServiceContainer();
	~ServiceContainer();

public:
	ServiceContainer(const ServiceContainer& aRhs) = delete;
	ServiceContainer& operator = (const ServiceContainer& aRhs) = delete;

public:
	void AddService(uintptr_t aTypeId, void* aService);
	void RemoveService(uintptr_t aTypeId);
	void* GetService(uintptr_t aTypeId) const;

	std::map<uintptr_t, void*> mServices;
};
}

#endif
