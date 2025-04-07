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

namespace fs = std::filesystem;
namespace rythe::core::assets
{
	template<typename AssetType>
	struct import_settings { };

	template<typename AssetType>
	constexpr import_settings<AssetType> default_settings;
}