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

#include "../assets/importsettings.hpp"
#include "../assets/assethandle.hpp"

namespace fs = std::filesystem;
namespace rythe::core::assets
{
	template<typename AssetType>
	class AssetImporter
	{
	public:
		virtual bool canLoad(fs::path filePath) = 0;
		virtual asset_handle<AssetType> load(rsl::id_type id, fs::path filePath, AssetType* data, const import_settings<AssetType>& settings) = 0;
		virtual asset_handle<AssetType> loadFromMemory(rsl::id_type id, AssetType* data, const import_settings<AssetType>& settings) = 0;
		virtual void write(fs::path filePath, AssetType* data) = 0;
		virtual void free(AssetType& asset) = 0;
		virtual ~AssetImporter() = default;
	};

	template<typename T, typename AssetType>
	concept AssetImporterType = std::is_base_of<AssetImporter<AssetType>, T>::value;
}