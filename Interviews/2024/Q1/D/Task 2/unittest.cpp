#include <gtest/gtest.h>

#include "cache.h"
#include "translation.h" // Assuming the walkPageTables is here

class TranslationCacheTest : public ::testing::Test
{
protected:
    std::unique_ptr<TranslationCache> cache;

    void SetUp() override
    {
        cache = std::make_unique<TranslationCache>(3); // Example cache size
    }

    // No TearDown needed as unique_ptr automatically cleans up
};

// Test for cache hit
TEST_F(TranslationCacheTest, CacheHit)
{
    VirtualAddress vaddr{4096}; // An address that's not offloaded
    auto firstTranslation = cache->translateAddress(vaddr);
    auto secondTranslation = cache->translateAddress(vaddr);

    EXPECT_TRUE(firstTranslation.has_value());
    EXPECT_EQ(firstTranslation, secondTranslation);
}

// Test for cache miss
TEST_F(TranslationCacheTest, CacheMiss)
{
    VirtualAddress vaddr{4096};
    auto firstTranslation = cache->translateAddress(vaddr);

    VirtualAddress newVaddr{8192}; // Different address
    auto newTranslation = cache->translateAddress(newVaddr);

    EXPECT_TRUE(newTranslation.has_value());
    EXPECT_NE(firstTranslation, newTranslation);
}

// Test for LRU eviction
TEST_F(TranslationCacheTest, LRUEviction)
{
    // Access three different pages
    cache->translateAddress(VirtualAddress{4096});
    cache->translateAddress(VirtualAddress{8192});
    cache->translateAddress(VirtualAddress{12288});

    // This should cause the first one (4096) to be evicted
    cache->translateAddress(VirtualAddress{16384});

    // 4096 should be a miss now
    auto result = cache->translateAddress(VirtualAddress{4096});
    EXPECT_TRUE(result.has_value());
}

// Test for handling offloaded pages
TEST_F(TranslationCacheTest, OffloadedPage)
{
    VirtualAddress offloadedAddr{0}; // Address that simulates an offloaded page
    auto result = cache->translateAddress(offloadedAddr);
    EXPECT_FALSE(result.has_value());
}

// Test the cache with an empty translation
TEST_F(TranslationCacheTest, EmptyCache)
{
    VirtualAddress vaddr{4096};
    auto result = cache->translateAddress(vaddr);
    EXPECT_TRUE(result.has_value());
}

// Test for cache misses
TEST_F(TranslationCacheTest, CacheMisses)
{
    // Access a unique address multiple times, each should be a miss
    cache->translateAddress(VirtualAddress{4096});
    cache->translateAddress(VirtualAddress{8192});
    cache->translateAddress(VirtualAddress{12288});

    EXPECT_EQ(cache->get_cache_misses(/* include_offloaded = */ false), 2);
    EXPECT_EQ(cache->get_cache_misses(/* include_offloaded = */ true), 3);
}

// Test for cache hit after a miss
TEST_F(TranslationCacheTest, CacheHitAfterMiss)
{
    // Access a unique address which is a miss, then access it again which should be a hit
    cache->translateAddress(VirtualAddress{4096});
    cache->translateAddress(VirtualAddress{4096});

    EXPECT_EQ(cache->get_cache_misses(/* include_offloaded = */ false), 1);
    EXPECT_EQ(cache->get_cache_misses(/* include_offloaded = */ true), 1);
}

// Test for cache hit ratio
TEST_F(TranslationCacheTest, CacheHitRatio)
{
    // Access a unique address twice
    cache->translateAddress(VirtualAddress{4096});
    cache->translateAddress(VirtualAddress{4096});

    // Access another unique address
    cache->translateAddress(VirtualAddress{8192});

    // Access an offloaded address
    cache->translateAddress(VirtualAddress{0});

    // Access the first address again
    cache->translateAddress(VirtualAddress{4096});

    float expectedHitRatio;

    // 2 hits (second and fifth access) and 2 misses (first and thirs access)
    expectedHitRatio = 2.0f / 4.0f;
    EXPECT_FLOAT_EQ(cache->get_hit_ratio(/* include_offloaded = */ false), expectedHitRatio);

    // 2 hits (second and fifth access), 2 misses (first and thirs access) and 1 offloaded page
    expectedHitRatio = 2.0f / 5.0f;
    EXPECT_FLOAT_EQ(cache->get_hit_ratio(/* include_offloaded = */ true), expectedHitRatio);
}
