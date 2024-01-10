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

public:
    std::optional<PhysicalAddress> translateAddress(VirtualAddress vaddr);
};
