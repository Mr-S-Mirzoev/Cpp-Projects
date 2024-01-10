#include "cache.h"

#include "translation.h"

float TranslationCache::get_hit_ratio(bool include_offloaded) const
{
    return static_cast<float>(cache_hits_) / (cache_hits_ + get_cache_misses(include_offloaded));
}

std::uint32_t TranslationCache::get_cache_misses(bool include_offloaded) const
{
    return cache_misses_ + (include_offloaded ? offloaded_pages_ : 0);
}

std::optional<PhysicalAddress> TranslationCache::translateAddress(VirtualAddress vaddr)
{
    auto cache_it = cache_.find(vaddr);
    if (cache_it != cache_.end())
    {
        latest_history_.erase(cache_it->second.history_it);
        latest_history_.push_front(vaddr);
        cache_it->second.history_it = latest_history_.begin();
        ++cache_hits_;
        return cache_it->second.paddr;
    }

    auto paddr = walkPageTables(vaddr);
    if (!paddr)
    {
        ++offloaded_pages_;
        return paddr;
    }

    // We deliberately don't cache offloaded pages as they could be reloaded and then the cache
    // entry would be invalid
    ++cache_misses_;

    if (latest_history_.size() == cache_size_)
    {
        const auto vaddr_to_remove = latest_history_.back();
        cache_.erase(vaddr_to_remove);
        latest_history_.pop_back();
    }

    latest_history_.push_front(vaddr);
    CacheEntry new_entry{latest_history_.begin(), paddr};
    cache_.emplace(vaddr, std::move(new_entry));

    return paddr;
}
