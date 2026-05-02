#pragma once

#include "Mesh.h"
#include "Texture2D.h"

#define _AssetCacheMethodsTemplate template <typename T> requires( std::common_type<T, Texture2D>::value || std::common_type<T, Mesh>::value )
namespace AssetCache {

	_AssetCacheMethodsTemplate
	static void RemoveFromAssetCache(const T* asset);

	_AssetCacheMethodsTemplate
	static void RemoveFromAssetCache(const size_t& asset_cache_index);

	_AssetCacheMethodsTemplate
	static void AppendToAssetCache(const T* asset);

	_AssetCacheMethodsTemplate
	static void InsertIntoAssetCache(const size_t& asset_cache_index, const T* asset);
}

#undef _AssetCacheMethodsTemplate