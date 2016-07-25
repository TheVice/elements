
#include "ServiceContainer.h"

namespace Library
{

ServiceContainer::ServiceContainer() :
	mServices()
{
}

ServiceContainer::~ServiceContainer()
{
}

void ServiceContainer::AddService(uintptr_t aTypeId, void* aService)
{
	mServices.insert(std::pair<uintptr_t, void*>(aTypeId, aService));
}

void ServiceContainer::RemoveService(uintptr_t aTypeId)
{
	mServices.erase(aTypeId);
}

void* ServiceContainer::GetService(uintptr_t aTypeId) const
{
	std::map<uintptr_t, void*>::const_iterator it = mServices.find(aTypeId);
	return (it != mServices.end() ? it->second : nullptr);
}

}
