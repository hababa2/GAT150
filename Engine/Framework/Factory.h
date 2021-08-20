#pragma once

#include "Singleton.h"
#include "Object\Object.h"

#include <memory>
#include <map>

namespace nh
{
	template<typename TBase>
	class CreatorBase
	{
	public:
		virtual std::unique_ptr<TBase> Create() const = 0;
	};

	template<typename T, typename TBase>
	class Creator : public CreatorBase<TBase>
	{
		std::unique_ptr<TBase> Create() const override
		{
			return std::make_unique<T>();
		}
	};

	template<typename TKey, typename TBase>
	class Factory
	{
	public:
		template<typename T = TBase>
		std::unique_ptr<T> Create(TKey key);

		template<typename T>
		void Register(TKey key);

	protected:
		std::map<TKey, std::unique_ptr<CreatorBase<TBase>>> registry;
	};

	template<typename TKey, typename TBase>
	template<typename T>
	inline std::unique_ptr<T> Factory<TKey, TBase>::Create(TKey key)
	{
		auto it = registry.find(key);
		if (it != registry.end())
		{
			return std::unique_ptr<T>(dynamic_cast<T*>(it->second->Create().release()));
		}

		return std::unique_ptr<T>();
	}

	template<typename TKey, typename TBase>
	template<typename T>
	inline void Factory<TKey, TBase>::Register(TKey key)
	{
		registry[key] = std::make_unique<Creator<T, TBase>>();
	}
}