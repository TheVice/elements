
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
	mServices.insert(std::make_pair(aTypeId, aService));
}

void ServiceContainer::RemoveService(uintptr_t aTypeId)
{
	mServices.erase(aTypeId);
}

void* ServiceContainer::GetService(uintptr_t aTypeId) const
{
	const auto search = mServices.find(aTypeId);
	return (search != mServices.end() ? search->second : nullptr);
}

}
