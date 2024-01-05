#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <type_traits>

#include <rsl/utilities>
#include <rsl/hash>
#include <rsl/logging>

namespace rythe::core::assets
{
	template<typename AssetType>
	struct asset_handle
	{
		rsl::id_type m_id;
		AssetType* m_data = nullptr;
		asset_handle() = default;
		asset_handle(rsl::id_type id, AssetType* data) : m_id(id), m_data(data) {}
		asset_handle(rsl::id_type id, AssetType& data) : m_id(id), m_data(&data) {}
		asset_handle(const asset_handle<AssetType>& handle) : m_id(handle.m_id), m_data(handle.m_data) {}

		AssetType* operator->() { return m_data; }
		operator AssetType& () const { return *m_data; }
		operator rsl::id_type() const { return m_id; }

		bool operator == (asset_handle handle) { return m_data == handle.m_data; }
		bool operator != (asset_handle handle) { return !operator==(handle); }

		bool operator == (AssetType* data) { return m_data == data; }
		bool operator !=(AssetType* data) { return !operator==(data); }
	};
}