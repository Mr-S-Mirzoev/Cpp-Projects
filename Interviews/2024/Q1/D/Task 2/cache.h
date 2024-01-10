#pragma once

#include "types.h"

#include <list>
#include <optional>
#include <unordered_map>

class TranslationCache
{
    struct CacheEntry
    {
        std::list<VirtualAddress>::iterator history_it;
        std::optional<PhysicalAddress> paddr;
    };

    std::unordered_map<VirtualAddress, CacheEntry> cache_;
    std::list<VirtualAddress> latest_history_;
    std::size_t cache_size_;

    std::uint32_t cache_misses_ = 0;
    std::uint32_t cache_hits_ = 0;
    std::uint32_t offloaded_pages_ = 0;

public:
    TranslationCache(std::size_t cache_size) : cache_size_(cache_size) {}

    float get_hit_ratio(bool include_offloaded = false) const;
    std::uint32_t get_cache_misses(bool include_offloaded = false) const;

    std::optional<PhysicalAddress> translateAddress(VirtualAddress vaddr);
};
