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
	template<typename DataType, typename HandleType, typename ImportSettings>
	class AssetCache
	{
	private:
		static std::unordered_map<rsl::id_type, std::unique_ptr<DataType>> m_assets;
	public:
		static HandleType createAsset(const std::string& name, const std::string& filePath);
		static HandleType createAsset(const std::string& name, HandleType handle);
		static HandleType createAsset(const std::string& name, const std::string& filePath, ImportSettings settings);
		static HandleType createAsset(const std::string& name, HandleType handle, ImportSettings settings);
		static HandleType getAsset(const::string& name);
		static void deleteAsset(const std::string& name);
		static void deleteAsset(HandleType handle);
		static void loadAssets(const std::string& directory);
	};
}