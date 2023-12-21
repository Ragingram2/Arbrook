#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <rsl/utilities>

namespace rythe::core::assets
{
	//template<typename AssetType>
	//struct import_settings
	//{

	//};

	//template<typename AssetType>
	//struct asset_handle
	//{
	//private:
	//	rsl::id_type m_id;
	//	AssetType* m_data;
	//public:
	//	constexpr asset_handle(AssetType* p, rsl::id_type id) noexcept : m_data(p), m_id(id) {}

	//	constexpr bool operator ==(const asset_handle& other) const noexcept { return other.m_id == other.m_id && m_data == other.m_data; }
	//	constexpr bool operator!=(const asset_handle& other) const noexcept { return !operator=(other); }

	//	asset_handle() noexcept = default;
	//	asset_handle(const asset_handle&) noexcept = default;
	//	asset_handle(asset_handle&&) noexcept = default;
	//	asset_handle operator=(const asset_handle&) noexcept = default;
	//	asset_handle operator=(asset_handle&&) noexcept = default;
	//	~asset_handle() = default;

	//public:
	//	rsl::id_type id() const noexcept;
	//	const std::string& name() const;
	//	const std::string& path() const;
	//	void destroy();
	//	asset_handle copy(rsl::id_type id, const std::string& name) const;

	//};

	//template<typename AssetType>
	//constexpr static asset_handle<AssetType> invalid_asset = { nullptr, invalid_id };

	//template<typename AssetType>
	//class AssetImporter
	//{
	//protected:
	//	template<typename... Args>
	//	asset_handle<AssetType> create(rsl::id_type nameHash, Args&&... args) const;
	//public:
	//	virtual asset_handle<AssetType> load(rsl::id_type, const std::string& filePath, const import_settings<AssetType>& settings) = 0;
	//	virtual void free(AssetType& asset) = 0;
	//	virtual ~AssetImporter() = default;
	//};

	//template<typename AssetType>
	//class AssetCache
	//{
	//public:
	//	using ImportSettings = import_settings<AssetType>;
	//private:
	//	static std::unordered_map<rsl::id_type, std::unique_ptr<AssetType>> m_assets;
	//public:
	//	static asset_handle<AssetType> createAsset(const std::string& name, const std::string& filePath);
	//	static asset_handle<AssetType> createAsset(const std::string& name, const std::string& filePath, ImportSettings settings);
	//	static asset_handle<AssetType> getAsset(const::string& name);
	//	static void deleteAsset(const std::string& name);
	//	static void deleteAsset(asset_handle<AssetType> handle);
	//	static void loadAssets(const std::string& directory);
	//};
}