#include "cache.h"

#include "translation.h"

std::optional<PhysicalAddress> TranslationCache::translateAddress(VirtualAddress vaddr)
{
    auto cache_it = cache_.find(vaddr);
    if (cache_it != cache_.end())
    {
        latest_history_.erase(cache_it->second.history_it);
        latest_history_.push_front(vaddr);
        cache_it->second.history_it = latest_history_.begin();
        return cache_it->second.paddr;
    }

    auto paddr = translateAddress(vaddr);
    if (!paddr)
    {
        return paddr;
    }

    if (latest_history_.size() == cache_size_)
    {
        const auto vaddr_to_remove = latest_history_.back();
        cache_.erase(vaddr_to_remove);
        latest_history_.pop_back();
    }

    latest_history_.push_front(vaddr);
    cache_.emplace(vaddr, latest_history_.begin(), paddr);

    return paddr;
}
