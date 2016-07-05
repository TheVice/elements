#ifndef _RTTI_H_
#define _RTTI_H_

#include <string>

namespace Library
{
class RTTI
{
public:
	virtual ~RTTI() = default;

	virtual const uintptr_t& TypeIdInstance() const = 0;

	virtual RTTI* QueryInterface(const uintptr_t aId) const
	{
		(void)aId;
		return nullptr;
	}

	virtual bool Is(const uintptr_t aId) const
	{
		(void)aId;
		return false;
	}

	virtual bool Is(const std::string& aName) const
	{
		(void)aName;
		return false;
	}

	template<typename T>
	T* As() const
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}

		return nullptr;
	}
};

#define RTTI_DECLARATIONS(Type, ParentType)														\
	public:																						\
	static std::string TypeName() { return std::string(#Type); }								\
	virtual const uintptr_t& TypeIdInstance() const override { return TypeIdClass(); }			\
	static const uintptr_t& TypeIdClass() { return sRunTimeTypeId; }							\
	virtual RTTI* QueryInterface(const uintptr_t aId) const override							\
	{																							\
		if (aId == sRunTimeTypeId)																\
		{ return (RTTI*)this; }																	\
		else																					\
		{ return ParentType::QueryInterface(aId); }												\
	}																							\
	virtual bool Is(const uintptr_t aId) const override											\
	{																							\
		if (aId == sRunTimeTypeId)																\
		{ return true; }																		\
		else																					\
		{ return ParentType::Is(aId); }															\
	}																							\
	virtual bool Is(const std::string& aName) const override									\
	{																							\
		if (aName == TypeName())																\
		{ return true; }																		\
		else																					\
		{ return ParentType::Is(aName); }														\
	}																							\
	private:																					\
	static uintptr_t sRunTimeTypeId;

#define RTTI_DEFINITIONS(Type) uintptr_t Type::sRunTimeTypeId = (uintptr_t)& Type::sRunTimeTypeId;

}

#endif
