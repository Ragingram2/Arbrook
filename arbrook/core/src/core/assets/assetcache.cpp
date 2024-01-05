#include "core/assets/assetcache.hpp"

namespace rythe::core::assets
{
	template<typename AssetType>
	inline std::unordered_map<rsl::id_type, std::unique_ptr<AssetImporter<AssetType>>> AssetCache<AssetType>::m_importers;
	template<typename AssetType>
	inline std::unordered_map<rsl::id_type, std::unique_ptr<AssetType>> AssetCache<AssetType>::m_assets;
	template<typename AssetType>
	inline std::unordered_map<rsl::id_type, std::string> AssetCache<AssetType>::m_names;
}