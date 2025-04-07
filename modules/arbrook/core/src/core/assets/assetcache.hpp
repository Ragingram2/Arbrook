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
#include <rsl/type_traits>

#include "../assets/importsettings.hpp"
#include "../assets/assethandle.hpp"
#include "../assets/assetimporter.hpp"

namespace fs = std::filesystem;

namespace rythe::core::assets
{
	namespace log = rsl::log;
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
			auto id = rsl::type_id<Importer>();
			if (m_importers.count(id))
			{
				log::warn("The importer you tried to register already exists");
				return;
			}

			m_importers.emplace(id, std::make_unique<Importer>());
		}
		static asset_handle<AssetType> createAssetFromMemory(const std::string& name, AssetType asset, [[maybe_unused]] ImportSettings settings)
		{
			log::info("Loading asset \"{}\" from memory", name);
			if (m_importers.size() < 1)
			{
				log::error("No importers where registered for this asset");
				return { 0, nullptr };
			}

			rsl::id_type id = rsl::hash_string(name);

			if (m_assets.contains(id))
			{
				//if (overrideExisting)
				//{
				//	m_assets[id].reset(asset);
				//}
				//else
				//{
				log::warn("Asset \"{}\" already exists, returning existing handle", name);
				return { id, m_assets[id].get() };
				//}
			}

			//for (auto& [id, importer] : m_importers)
			//{
			//	importer->loadFromMemory(id, asset, settings);
			//}

			auto assetPtr = std::make_unique<AssetType>(asset);
			m_names.emplace(id, name);
			//log::debug(id);
			return { id, m_assets.emplace(id,std::move(assetPtr)).first->second.get() };
		}

		static asset_handle<AssetType> createAsset(const std::string& name, fs::path filePath, ImportSettings settings, bool overrideExisting = false)
		{
			log::info("Loading asset \"{}\" at \"{}\"", name, filePath.string());
			if (m_importers.size() < 1)
			{
				log::error("No importers where registered for this asset");
				return { 0, nullptr };
			}

			rsl::id_type id = rsl::hash_string(name);

			AssetType* data = new AssetType();
			if (m_assets.contains(id))
			{
				if (overrideExisting)
				{
					data = m_assets[id].get();
				}
				else
				{
					log::warn("Asset \"{}\" already exists, returning existing handle", name);
					return { id, m_assets[id].get() };
				}
			}

			bool somethingLoaded = false;
			bool wrongExtension = false;
			for (auto& [id, importer] : m_importers)
			{
				if (importer->canLoad(filePath))
				{
					importer->load(id, filePath, data, settings);
					somethingLoaded = true;
					break;
				}
				else
					wrongExtension = true;
			}

			if (!somethingLoaded)
			{
				if (wrongExtension)
					return { 0,nullptr };

				log::error("Something went wrong with loading this asset, do you have the appropriate importer registered?");
				return { 0,nullptr };
			}

			m_names.emplace(id, name);
			return { id, m_assets.emplace(id, std::move(data)).first->second.get() };
		}
		template<AssetImporterType<AssetType> Importer>
		static asset_handle<AssetType> createAsset(const std::string& name, fs::path filePath, ImportSettings settings, bool overrideExisting = false)
		{
			rsl::id_type id = rsl::hash_string(name);
			rsl::id_type importerId = rsl::type_id<Importer>();

			AssetType* data = new AssetType();
			if (m_assets.contains(id))
			{
				if (overrideExisting)
				{
					data = m_assets[id].get();
				}
				else
				{
					log::warn("Asset \"{}\" already exists, returning existing handle", name);
					return { id, m_assets[id].get() };
				}
			}
			if (m_importers[importerId]->canLoad(filePath))
				m_importers[importerId]->load(id, filePath, data, settings);
			else
			{
				log::error("This importer does not support files with the given extension {}", filePath.extension());
				return { 0, nullptr };
			}

			if (data == nullptr)
			{
				log::error("Something went wrong with loading this asset");
				return { 0, nullptr };
			}

			m_names.emplace(id, name);
			return { id, m_assets.emplace(id, std::move(data)).first->second.get() };
		}
		static void loadAssets(const std::string& directory, ImportSettings settings = default_settings<AssetType>, bool overrideExisting = false)
		{
			for (auto& d_entry : fs::directory_iterator(directory))
			{
				if (!d_entry.path().has_extension()) continue;
				auto fileName = d_entry.path().stem().string();
				auto path = d_entry.path().string();
				createAsset(fileName, path, settings, overrideExisting);
			}
		}
		static asset_handle<AssetType> getAsset(const std::string& name)
		{
			return getAsset(rsl::hash_string(name));
		}
		static asset_handle<AssetType> getAsset(rsl::id_type hash_string)
		{
			if (m_assets.count(hash_string))
			{
				return { hash_string, m_assets[hash_string].get() };
			}

			log::error("Asset \"{}\" does not exist", m_names[hash_string]);
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
			deleteAsset(rsl::hash_string(name));
		}
		static void deleteAsset(rsl::id_type hash_string)
		{
			if (m_assets.contains(hash_string))
			{
				m_assets.erase(hash_string);
				m_names.erase(hash_string);
			}
		}
		static void deleteAssets()
		{
			for (auto& [id, data] : m_assets)
			{
				deleteAsset(id);
			}
		}
	};

	template<typename AssetType>
	inline std::unordered_map<rsl::id_type, std::unique_ptr<AssetImporter<AssetType>>> AssetCache<AssetType>::m_importers;
	template<typename AssetType>
	inline std::unordered_map<rsl::id_type, std::unique_ptr<AssetType>> AssetCache < AssetType>::m_assets;
	template<typename AssetType>
	inline std::unordered_map<rsl::id_type, std::string> AssetCache < AssetType>::m_names;
}