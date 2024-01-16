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

#include "core/assets/importsettings.hpp"
#include "core/assets/assethandle.hpp"
#include "core/assets/assetimporter.hpp"

namespace fs = std::filesystem;
namespace rythe::core::assets
{
	template<typename AssetType>
	class AssetCache
	{
	public:
		using ImportSettings = import_settings<AssetType>;
	private:
		static std::unordered_map<rsl::id_type, std::unique_ptr<AssetImporter<AssetType>>> m_importers;
		static std::unordered_map<rsl::id_type, std::unique_ptr<AssetType>> m_assets;
		static std::unordered_map<rsl::id_type, std::string> m_names;
	public:

		template<AssetImporterType<AssetType> Importer>
		static void registerImporter()
		{
			auto id = rsl::typeHash<Importer>();
			if (m_importers.count(id))
			{
				log::warn("The importer you tried to register already exists");
				return;
			}

			m_importers.emplace(id, std::make_unique<Importer>());
		}
		static asset_handle<AssetType> createAsset(const std::string& name, fs::path filePath, ImportSettings settings, bool overrideExisting = false)
		{
			if (m_importers.size() < 1)
			{
				log::error("No importers where registered for this asset");
				return { 0, nullptr };
			}

			rsl::id_type id = rsl::nameHash(name);

			if (!overrideExisting)
				if (m_assets.contains(id))
				{
					log::warn("Asset[{}] \"{}\" already exists, returning existing handle",typeid(AssetType).name(), name);
					return { id, m_assets[id].get() };
				}

			std::unique_ptr<AssetType> data = std::make_unique<AssetType>();
			bool somethingLoaded = false;
			for (auto& [id, importer] : m_importers)
			{
				if (importer->canLoad(filePath))
				{
					importer->load(id, filePath, data.get(), settings);
					somethingLoaded = true;
					break;
				}
			}

			if (!somethingLoaded)
			{
				log::error("Something went wrong with loading this asset, do you have the appropriate importer registered?");
				return { 0,nullptr };
			}

			m_names.emplace(id, name);
			return { id, m_assets.emplace(id, std::move(data)).first->second.get() };
		}
		template<AssetImporterType<AssetType> Importer>
		static asset_handle<AssetType> createAsset(const std::string& name, fs::path filePath, ImportSettings settings, bool overrideExisting = false)
		{
			rsl::id_type id = rsl::nameHash(name);
			rsl::id_type importerId = rsl::typeHash<Importer>();
			if (!overrideExisting)
				if (m_assets.contains(id))
				{
					log::warn("Asset \"{}\" already exists, returning existing handle", name);
					return { id, m_assets[id].get() };
				}

			std::unique_ptr<AssetType> data = std::make_unique<AssetType>();
			m_importers[importerId]->load(id, filePath, data.get(), settings);

			if (!data.get())
			{
				log::error("Something whent wrong with loading this asset");
				return { 0, nullptr };
			}

			m_names.emplace(id, name);
			return { id, m_assets.emplace(id, std::move(data)).first->second.get() };
		}
		static void loadAssets(const std::string& directory, ImportSettings settings)
		{
			for (auto& d_entry : fs::directory_iterator(directory))
			{
				if (!d_entry.path().has_extension()) continue;
				auto fileName = d_entry.path().stem().string();
				auto path = d_entry.path().string();

				log::info("Loading asset \"{}\" at \"{}\"", fileName, path);
				createAsset(fileName, path, settings);
			}
		}
		static asset_handle<AssetType> getAsset(const std::string& name)
		{
			return getAsset(rsl::nameHash(name));
		}
		static asset_handle<AssetType> getAsset(rsl::id_type nameHash)
		{
			if (m_assets.count(nameHash))
			{
				return { nameHash, m_assets[nameHash].get() };
			}

			log::error("Asset \"{}\" does not exist", m_names[nameHash]);
			return { 0, nullptr };
		}
		static std::vector<asset_handle<AssetType>> getAssets()
		{
			std::vector<asset_handle<AssetType>> assets;
			for (auto& [id, data] : m_assets)
			{
				assets.emplace_back(id, *data.get());
			}
			return assets;
		}
		static void deleteAsset(asset_handle<AssetType> handle)
		{
			deleteAsset(handle.m_id);
		}
		static void deleteAsset(const std::string& name)
		{
			deleteAsset(rsl::nameHash(name));
		}
		static void deleteAsset(rsl::id_type nameHash)
		{
			if (m_assets.contains(nameHash))
			{
				m_assets.erase(nameHash);
				m_names.erase(nameHash);
			}
		}
	};
}