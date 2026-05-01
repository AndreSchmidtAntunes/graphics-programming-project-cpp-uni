#include "AssetCache.h"

#include <vector>
#include <map>
#include <typeindex>

namespace AssetCache {
	const static std::map<std::type_index, std::vector<void*>*> asset_cache_map {
	{ std::type_index(typeid(Texture2D)),	(new std::vector<void*>) }, // void* means Texture2D* here
	{ std::type_index(typeid(Mesh)),		(new std::vector<void*>) } // void* means Mesh* here
	};

	template <typename T> requires
		( std::common_type<T, Texture2D>::value ||
		std::common_type<T, Mesh>::value )
		static void RemoveFromAssetCache(const T* asset) {
		// cast cache pointer to cache vector pointer, to then get vector as reference
		std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);

		auto it = std::find(asset_cache.begin(), asset_cache.end(), asset);

		if (it != asset_cache.end()) {
			delete* it;
			asset_cache.erase(it);
		}
	}

	template <typename T> requires
		( std::common_type<T, Texture2D>::value ||
		std::common_type<T, Mesh>::value )
		static void RemoveFromAssetCache(const size_t& asset_cache_index) {
		std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);

		delete asset_cache[asset_cache_index];
		asset_cache.erase(asset_cache.begin() + asset_cache_index);
	}

	template <typename T> requires
		( std::common_type<T, Texture2D>::value ||
		std::common_type<T, Mesh>::value )
		static void AppendToAssetCache(const T* asset) {
		// Cast cache pointer to cache vector pointer, to then get vector as reference
		std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);

		asset_cache.push_back(asset);
	}

	template <typename T> requires
		( std::common_type<T, Texture2D>::value ||
		std::common_type<T, Mesh>::value )
		static void InsertIntoAssetCache(const size_t& asset_cache_index, const T* asset) {
		std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);

		asset_cache.insert(asset_cache.begin() + asset_cache_index, asset_cache_index);
	}
}